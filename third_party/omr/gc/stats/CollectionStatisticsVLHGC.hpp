/*******************************************************************************
 * Copyright (c) 1991, 2016 IBM Corp. and others
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

#if !defined(COLLECTIONSTATISTICSVLHGC_HPP_)
#define COLLECTIONSTATISTICSVLHGC_HPP_

#include "omrcfg.h"
#include "omrcomp.h"

#include "Base.hpp"
#include "CollectionStatistics.hpp"
#include "EnvironmentBase.hpp"
#include "GCExtensions.hpp"
#include "Heap.hpp"

/**
 * A collection of interesting statistics for the Heap.
 * @ingroup GC_Stats
 */
class MM_CollectionStatisticsVLHGC : public MM_CollectionStatistics
{
private:
protected:
public:
	const char *_incrementDescription; /**< Current increment description.  Only non-null for increment start */
	uintptr_t _incrementCount; /**< Current increment count.  Only non-zero for increment start */

	uintptr_t _edenFreeHeapSize; /**< Eden free heap size in bytes */
	uintptr_t _edenHeapSize;	/**< Eden heap size in bytes */

	uintptr_t _arrayletReferenceObjects; /**< Count of non-contiguous reference arraylets */
	uintptr_t _arrayletReferenceLeaves;	/**< Count (total) of reference arraylet leaves */
	uintptr_t _largestReferenceArraylet;	/**< Count of reference arraylet leafs in largest arraylet */

	uintptr_t _arrayletPrimitiveObjects; /**< Count of non-contiguous primitive arraylets */
	uintptr_t _arrayletPrimitiveLeaves;	/**< Count (total) of primitive arraylet leaves */
	uintptr_t _largestPrimitiveArraylet;	/**< Count of primitive arraylet leafs in largest arraylet */

	uintptr_t _arrayletUnknownObjects; /**< Count of non-contiguous arraylets of unknown type (if class is unloaded)*/
	uintptr_t _arrayletUnknownLeaves; /**< Count (total) of arraylet leaves of unknown arraylet type (if class is unloaded) */

	uintptr_t _rememberedSetCount;					/**< Total count of remembered references (cards) */
	uintptr_t _rememberedSetBytesFree;				/**< Count of buffers in global free pool (represented in bytes). Buffers in thread local pools are not counted */
	uintptr_t _rememberedSetBytesTotal;				/**< Total count of buffers used or free (represented in bytes) */
	uintptr_t _rememberedSetOverflowedRegionCount;		/**< Count of overflowed regions due to full RSCL  */
	uintptr_t _rememberedSetStableRegionCount;			/**< Count of overflowed regions due to stable region */
	uintptr_t _rememberedSetBeingRebuiltRegionCount;	/**< Count of overflowed regions that are being rebuilt currently by GMP */

	uintptr_t _numaNodes;
	uintptr_t _commonNumaNodeBytes;
	uintptr_t _localNumaNodeBytes;
	uintptr_t _nonLocalNumaNodeBytes;


private:
protected:
public:

	static MM_CollectionStatisticsVLHGC *
	getCollectionStatistics(MM_CollectionStatistics *stats)
	{
		return (MM_CollectionStatisticsVLHGC *)stats;
	}

	MMINLINE void
	collectCollectionStatistics(MM_EnvironmentBase *env, MM_CollectionStatisticsVLHGC *stats)
	{
		MM_GCExtensions *extensions = MM_GCExtensions::getExtensions(env);

		stats->_totalHeapSize = extensions->heap->getActiveMemorySize();
		stats->_totalFreeHeapSize = extensions->heap->getApproximateFreeMemorySize();
	}

	/**
	 * Create a HeapStats object.
	 */
	MM_CollectionStatisticsVLHGC() :
		MM_CollectionStatistics()
		,_incrementDescription(0)
		,_incrementCount(0)
		,_edenFreeHeapSize(0)
		,_edenHeapSize(0)
		,_arrayletReferenceObjects(0)
		,_arrayletReferenceLeaves(0)
		,_largestReferenceArraylet(0)
		,_arrayletPrimitiveObjects(0)
		,_arrayletPrimitiveLeaves(0)
		,_largestPrimitiveArraylet(0)
		,_arrayletUnknownObjects(0)
		,_arrayletUnknownLeaves(0)
		,_rememberedSetCount(0)
		,_rememberedSetBytesFree(0)
		,_rememberedSetBytesTotal(0)
		,_rememberedSetOverflowedRegionCount(0)
		,_rememberedSetStableRegionCount(0)
		,_rememberedSetBeingRebuiltRegionCount(0)
		,_numaNodes(0)
		,_commonNumaNodeBytes(0)
		,_localNumaNodeBytes(0)
		,_nonLocalNumaNodeBytes(0)
	{}
};

#endif /* COLLECTIONSTATISTICSVLHGC_HPP_ */
