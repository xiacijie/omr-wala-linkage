/*******************************************************************************
 * Copyright (c) 1991, 2018 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

/**
 * @file
 * @ingroup GC_Modron_Standard
 */
 
#include "omrcfg.h"

#include "ConfigurationStandard.hpp"

#if defined(OMR_GC_MODRON_CONCURRENT_MARK)
#include "ConcurrentGCIncrementalUpdate.hpp"
#include "ConcurrentGCSATB.hpp"
#endif /* OMR_GC_MODRON_CONCURRENT_MARK */
#if defined(OMR_GC_CONCURRENT_SWEEP)
#include "ConcurrentSweepGC.hpp"
#endif /* OMR_GC_CONCURRENT_SWEEP */
#include "EnvironmentStandard.hpp"
#include "GlobalCollector.hpp"
#include "GCExtensionsBase.hpp"
#include "HeapRegionManagerStandard.hpp"
#include "HeapRegionDescriptorStandard.hpp"
#include "HeapVirtualMemory.hpp"
#include "MemoryPoolAddressOrderedList.hpp"
#include "MemoryPoolAddressOrderedListBase.hpp"
#include "MemoryPoolSplitAddressOrderedList.hpp"
#include "MemoryPoolHybrid.hpp"
#include "MemoryPoolLargeObjects.hpp"
#include "ParallelGlobalGC.hpp"
#include "SweepPoolManagerAddressOrderedList.hpp"
#include "SweepPoolManagerSplitAddressOrderedList.hpp"
#include "SweepPoolManagerHybrid.hpp"

/**
 * Tear down Standard Configuration
 */
void
MM_ConfigurationStandard::tearDown(MM_EnvironmentBase* env)
{
	MM_GCExtensionsBase* extensions = env->getExtensions();

	if (NULL != extensions->sweepPoolManagerAddressOrderedList) {
		extensions->sweepPoolManagerAddressOrderedList->kill(env);
		extensions->sweepPoolManagerAddressOrderedList = NULL;
	}

	if (NULL != extensions->sweepPoolManagerSmallObjectArea) {
		extensions->sweepPoolManagerSmallObjectArea->kill(env);
		extensions->sweepPoolManagerSmallObjectArea = NULL;
	}

	extensions->freeEntrySizeClassStatsSimulated.tearDown(env);

	MM_Configuration::tearDown(env);
}

bool
MM_ConfigurationStandard::initialize(MM_EnvironmentBase* env)
{
	MM_GCExtensionsBase* extensions = env->getExtensions();
	bool result = MM_Configuration::initialize(env);
	if (result) {
		extensions->payAllocationTax = extensions->isConcurrentMarkEnabled() || extensions->isConcurrentSweepEnabled();
		extensions->setStandardGC(true);
	}

	return result;
}


void
MM_ConfigurationStandard::initializeGCThreadCount(MM_EnvironmentBase* env)
{

	MM_Configuration::initializeGCThreadCount(env);

#if defined(OMR_GC_CONCURRENT_SCAVENGER)
	MM_GCExtensionsBase* extensions = env->getExtensions();

	/* If not explicitly set, concurrent phase of CS runs with approx 1/4 the thread count (relative to STW phases thread count */
	if (!extensions->concurrentScavengerBackgroundThreadsForced) {
		extensions->concurrentScavengerBackgroundThreads = OMR_MAX(1, (extensions->gcThreadCount + 1) / 4);
	} else if (extensions->concurrentScavengerBackgroundThreads > extensions->gcThreadCount) {
		extensions->concurrentScavengerBackgroundThreads = extensions->gcThreadCount;
	}
#endif
}


/**
 * Create the global collector for a Standard configuration
 */
MM_GlobalCollector*
MM_ConfigurationStandard::createGlobalCollector(MM_EnvironmentBase* env)
{
#if defined(OMR_GC_MODRON_CONCURRENT_MARK) || defined(OMR_GC_MODRON_CONCCURENT_SWEEP)
	MM_GCExtensionsBase *extensions = env->getExtensions();
#endif /* OMR_GC_MODRON_CONCURRENT_MARK || OMR_GC_CONCURRENT_SWEEP */

#if defined(OMR_GC_MODRON_CONCURRENT_MARK)
	if (extensions->concurrentMark) {
		if (isSnapshotAtTheBeginningBarrierEnabled()) {
			return MM_ConcurrentGCSATB::newInstance(env);
		} else {
			return MM_ConcurrentGCIncrementalUpdate::newInstance(env);
		}
	}
#endif /* OMR_GC_MODRON_CONCURRENT_MARK */
#if defined(OMR_GC_CONCURRENT_SWEEP)
	if (extensions->concurrentSweep) {
		return MM_ConcurrentSweepGC::newInstance(env);
	}
#endif /* OMR_GC_CONCURRENT_SWEEP */
	return MM_ParallelGlobalGC::newInstance(env);
}

/**
 * Create the heap for a Standard configuration
 */
MM_Heap*
MM_ConfigurationStandard::createHeapWithManager(MM_EnvironmentBase* env, uintptr_t heapBytesRequested, MM_HeapRegionManager* regionManager)
{
	return MM_HeapVirtualMemory::newInstance(env, env->getExtensions()->heapAlignment, heapBytesRequested, regionManager);
}

/**
 * Create the type of memorypool that corresponds to this Standard configuration.
 * In a generational mode this corresponds to the "old" area.
 * This is abstracted away into a superclass to avoid code duplication between all the Standard configurations.
 * 
 * @return the appropriate memoryPool
 */
MM_MemoryPool*
MM_ConfigurationStandard::createMemoryPool(MM_EnvironmentBase* env, bool appendCollectorLargeAllocateStats)
{
	MM_GCExtensionsBase* extensions = env->getExtensions();
	uintptr_t minimumFreeEntrySize = extensions->tlhMinimumSize;

	bool doSplit = 1 < extensions->splitFreeListSplitAmount;
	bool doHybrid = extensions->enableHybridMemoryPool;

#if defined(OMR_GC_CONCURRENT_SWEEP)
	if (extensions->concurrentSweep) {
		doSplit = false;
		/* TODO: enable processLargeAllocateStats in concurrentSweep case, currently can not collect correct FreeEntry Stats in concurrentSweep case*/
		extensions->processLargeAllocateStats = false;
		extensions->estimateFragmentation = NO_ESTIMATE_FRAGMENTATION;
	}
#endif /* OMR_GC_CONCURRENT_SWEEP */

	if ((UDATA_MAX == extensions->largeObjectAllocationProfilingVeryLargeObjectThreshold) && extensions->processLargeAllocateStats) {
		extensions->largeObjectAllocationProfilingVeryLargeObjectThreshold = OMR_MAX(10*1024*1024, extensions->memoryMax/100);
	}

	/* Create Sweep Pool Manager for Tenure */
	if (doSplit) {
		if (doHybrid) {
			if (!createSweepPoolManagerHybrid(env)) {
				return NULL;
			}
		}
		else {
			if (!createSweepPoolManagerSplitAddressOrderedList(env)) {
				return NULL;
			}
		}
		if (extensions->largeObjectArea) {
			/* need non-split version for loa as well */
			if (!createSweepPoolManagerAddressOrderedList(env)) {
				return NULL;
			}
		}
	} else {
		if (!createSweepPoolManagerAddressOrderedList(env)) {
			return NULL;
		}
	}

	if (extensions->largeObjectArea) {
		MM_MemoryPoolAddressOrderedListBase* memoryPoolLargeObjects = NULL;
		MM_MemoryPoolAddressOrderedListBase* memoryPoolSmallObjects = NULL;

		/* create memory pools for SOA and LOA */
		if (doSplit) {
			memoryPoolSmallObjects = MM_MemoryPoolSplitAddressOrderedList::newInstance(env, minimumFreeEntrySize, extensions->splitFreeListSplitAmount, "SOA");
		} else {
			memoryPoolSmallObjects = MM_MemoryPoolAddressOrderedList::newInstance(env, minimumFreeEntrySize, "SOA");
		}

		if (NULL == memoryPoolSmallObjects) {
			return NULL;
		}

		memoryPoolLargeObjects = MM_MemoryPoolAddressOrderedList::newInstance(env, extensions->largeObjectMinimumSize, "LOA");
		if (NULL == memoryPoolLargeObjects) {
			memoryPoolSmallObjects->kill(env);
			return NULL;
		}

		if (appendCollectorLargeAllocateStats) {
			memoryPoolLargeObjects->appendCollectorLargeAllocateStats();
			memoryPoolSmallObjects->appendCollectorLargeAllocateStats();
		}

		if (!extensions->freeEntrySizeClassStatsSimulated.initialize(env, (uint16_t)extensions->largeObjectAllocationProfilingTopK, extensions->freeMemoryProfileMaxSizeClasses, extensions->largeObjectAllocationProfilingVeryLargeObjectThreshold, 1, true)) {
			memoryPoolSmallObjects->kill(env);
			memoryPoolLargeObjects->kill(env);
			return NULL;
		}

		return MM_MemoryPoolLargeObjects::newInstance(env, memoryPoolLargeObjects, memoryPoolSmallObjects);

	} else {
		MM_MemoryPool* memoryPool = NULL;

		if (doSplit) {
			memoryPool = MM_MemoryPoolSplitAddressOrderedList::newInstance(env, minimumFreeEntrySize, extensions->splitFreeListSplitAmount, "Tenure");
		} else {
			memoryPool = MM_MemoryPoolAddressOrderedList::newInstance(env, minimumFreeEntrySize, "Tenure");
		}

		if (NULL == memoryPool) {
			return NULL;
		}

		if (appendCollectorLargeAllocateStats) {
			memoryPool->appendCollectorLargeAllocateStats();
		}

		if (!extensions->freeEntrySizeClassStatsSimulated.initialize(env, (uint16_t)extensions->largeObjectAllocationProfilingTopK, extensions->freeMemoryProfileMaxSizeClasses, extensions->largeObjectAllocationProfilingVeryLargeObjectThreshold, 1, true)) {
			memoryPool->kill(env);
			return NULL;
		}

		return memoryPool;
	}
}

MM_EnvironmentBase*
MM_ConfigurationStandard::allocateNewEnvironment(MM_GCExtensionsBase* extensions, OMR_VMThread* omrVMThread)
{
	return MM_EnvironmentStandard::newInstance(extensions, omrVMThread);
}

J9Pool*
MM_ConfigurationStandard::createEnvironmentPool(MM_EnvironmentBase* env)
{
	OMRPORT_ACCESS_FROM_OMRPORT(env->getPortLibrary());

	uintptr_t numberOfElements = getConfigurationDelegate()->getInitialNumberOfPooledEnvironments(env);
	/* number of elements, pool flags = 0, 0 selects default pool configuration (at least 1 element, puddle size rounded to OS page size) */
	return pool_new(sizeof(MM_EnvironmentStandard), numberOfElements, sizeof(uint64_t), 0, OMR_GET_CALLSITE(), OMRMEM_CATEGORY_MM, POOL_FOR_PORT(OMRPORTLIB));
}

/**
 * Create Sweep Pool Manager for Memory Pool Address Ordered List
 */
bool
MM_ConfigurationStandard::createSweepPoolManagerAddressOrderedList(MM_EnvironmentBase* env)
{
	MM_GCExtensionsBase* extensions = env->getExtensions();

	/* Create Sweep Pool Manager for MPAOL if it is not created yet */
	if (NULL == extensions->sweepPoolManagerAddressOrderedList) {
		extensions->sweepPoolManagerAddressOrderedList = MM_SweepPoolManagerAddressOrderedList::newInstance(env);
		if (NULL == extensions->sweepPoolManagerAddressOrderedList) {
			return false;
		}
	}

	return true;
}

/**
 * Create Sweep Pool Manager for Memory Pool Split Address Ordered List
 */
bool
MM_ConfigurationStandard::createSweepPoolManagerSplitAddressOrderedList(MM_EnvironmentBase* env)
{
	MM_GCExtensionsBase* extensions = env->getExtensions();

	/* Create Sweep Pool Manager for MPSAOL if it is not created yet */
	if (NULL == extensions->sweepPoolManagerSmallObjectArea) {
		extensions->sweepPoolManagerSmallObjectArea = MM_SweepPoolManagerSplitAddressOrderedList::newInstance(env);
		if (NULL == extensions->sweepPoolManagerSmallObjectArea) {
			return false;
		}
	}

	return true;
}

/**
 * Create Sweep Pool Manager for Memory Pool Split Address Ordered List
 */
bool
MM_ConfigurationStandard::createSweepPoolManagerHybrid(MM_EnvironmentBase* env)
{
	MM_GCExtensionsBase* extensions = env->getExtensions();

	/* Create Sweep Pool Manager for MPSAOL if it is not created yet */
	if (NULL == extensions->sweepPoolManagerSmallObjectArea) {
		extensions->sweepPoolManagerSmallObjectArea = MM_SweepPoolManagerHybrid::newInstance(env);
		if (NULL == extensions->sweepPoolManagerSmallObjectArea) {
			return false;
		}
	}

	return true;
}

MM_HeapRegionManager*
MM_ConfigurationStandard::createHeapRegionManager(MM_EnvironmentBase* env)
{
	MM_GCExtensionsBase* extensions = env->getExtensions();
	MM_HeapRegionManager* heapRegionManager = MM_HeapRegionManagerStandard::newInstance(env, extensions->regionSize, sizeof(MM_HeapRegionDescriptorStandard), MM_HeapRegionDescriptorStandard::initializer, MM_HeapRegionDescriptorStandard::destructor);

	return heapRegionManager;
}
