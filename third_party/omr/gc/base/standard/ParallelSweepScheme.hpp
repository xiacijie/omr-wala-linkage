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

#if !defined(PARALLELSWEEPSCHEME_HPP_)
#define PARALLELSWEEPSCHEME_HPP_

#include "omrcfg.h"
#include "omrmodroncore.h"
#include "modronopt.h"
#include "modronbase.h"

#include "BaseVirtual.hpp"

#include "EnvironmentBase.hpp"
#include "GCExtensionsBase.hpp"
#include "MemoryPool.hpp"
#include "ParallelTask.hpp"

class MM_AllocateDescription;
class MM_Dispatcher;
class MM_MemoryPool;
class MM_MemorySubSpace;
class MM_ParallelSweepChunk;
class MM_ParallelSweepScheme;
class MM_SweepHeapSectioning;
class MM_SweepPoolManager;
class MM_SweepPoolState;
class MM_MarkMap;

/**
 * Task to perform sweep.
 * @ingroup GC_Modron_Standard
 */
class MM_ParallelSweepTask : public MM_ParallelTask
{
private:
protected:
	MM_ParallelSweepScheme *_sweepScheme;

public:
	virtual uintptr_t getVMStateID() { return OMRVMSTATE_GC_SWEEP; };
	
	virtual void run(MM_EnvironmentBase *env);
	virtual void setup(MM_EnvironmentBase *env);
	virtual void cleanup(MM_EnvironmentBase *env);
	
#if defined(J9MODRON_TGC_PARALLEL_STATISTICS)
	virtual void synchronizeGCThreads(MM_EnvironmentBase *env, const char *id);
	virtual bool synchronizeGCThreadsAndReleaseMaster(MM_EnvironmentBase *env, const char *id);
	virtual bool synchronizeGCThreadsAndReleaseSingleThread(MM_EnvironmentBase *env, const char *id);
#endif /* J9MODRON_TGC_PARALLEL_STATISTICS */

	/**
	 * Create a ParallelSweepTask object.
	 */
	MM_ParallelSweepTask(MM_EnvironmentBase *env, MM_Dispatcher *dispatcher, MM_ParallelSweepScheme *sweepScheme) :
		MM_ParallelTask(env, dispatcher),
		_sweepScheme(sweepScheme)
	{
		_typeId = __FUNCTION__;
	}
};

/**
 * @todo Provide class documentation
 * @ingroup GC_Modron_Standard
 */
class MM_ParallelSweepScheme : public MM_BaseVirtual
{
	/*
	 * Data members
	 */
private:
	uintptr_t _chunksPrepared; 

protected:
	MM_GCExtensionsBase *_extensions;
	MM_Dispatcher *_dispatcher;
	MM_MarkMap *_currentMarkMap;	/**< The MarkMap which the ParallelGlobalGC gave to us to use for this cycle */
	uint8_t *_currentSweepBits;	/*< The base address of the raw bits used by the _currentMarkMap (sweep knows about this in order to perform some optimized types of map walking) */

	void *_heapBase;

	MM_SweepHeapSectioning *_sweepHeapSectioning;	/**< pointer to Sweep Heap Sectioning */

	J9Pool *_poolSweepPoolState;				/**< Memory pools for SweepPoolState*/ 
	omrthread_monitor_t _mutexSweepPoolState;	/**< Monitor to protect memory pool operations for sweepPoolState*/

public:
	
	/*
	 * Function members
	 */
private:
protected:
	virtual bool initialize(MM_EnvironmentBase *env);
	virtual void tearDown(MM_EnvironmentBase *env);

	void initializeSweepChunkTable(MM_EnvironmentBase *env);

	void sweepMarkMapBody(uintptr_t * &markMapCurrent, uintptr_t * &markMapChunkTop, uintptr_t * &markMapFreeHead, uintptr_t &heapSlotFreeCount, uintptr_t * &heapSlotFreeCurrent, uintptr_t * &heapSlotFreeHead);
	void sweepMarkMapHead(uintptr_t *markMapFreeHead, uintptr_t *markMapChunkBase, uintptr_t * &heapSlotFreeHead, uintptr_t &heapSlotFreeCount);
	void sweepMarkMapTail(uintptr_t *markMapCurrent, uintptr_t *markMapChunkTop, uintptr_t &heapSlotFreeCount);

	bool sweepChunk(MM_EnvironmentBase *env, MM_ParallelSweepChunk *sweepChunk);
	void sweepAllChunks(MM_EnvironmentBase *env, uintptr_t totalChunkCount);
	uintptr_t prepareAllChunks(MM_EnvironmentBase *env);
	
	virtual void connectChunk(MM_EnvironmentBase *env, MM_ParallelSweepChunk *chunk);
	void connectAllChunks(MM_EnvironmentBase *env, uintptr_t totalChunkCount);

	void initializeSweepStates(MM_EnvironmentBase *env);

	void flushFinalChunk(MM_EnvironmentBase *env, MM_MemoryPool *memoryPool);
	void flushAllFinalChunks(MM_EnvironmentBase *env);

	MMINLINE MM_Heap *getHeap() { return _extensions->heap; };

	void internalSweep(MM_EnvironmentBase *env);
	
	virtual void setupForSweep(MM_EnvironmentBase *env);

	virtual void allPoolsPostProcess(MM_EnvironmentBase *env);

	static void hookMemoryPoolNew(J9HookInterface** hook, uintptr_t eventNum, void* eventData, void* userData);
	static void hookMemoryPoolKill(J9HookInterface** hook, uintptr_t eventNum, void* eventData, void* userData);

public:
	static MM_ParallelSweepScheme *newInstance(MM_EnvironmentBase *env);
	virtual void kill(MM_EnvironmentBase *env);
	
	/**
	 * Sets the mark map to be used by the sweep scheme for this sweep operation.  Called by the ParallelGlobalGC to configure sweep and could
	 * be called again, if sweep is to change to operate on a new mark map.
	 * @param markMap[in] The mark map to sweep
	 */
	void setMarkMap(MM_MarkMap *markMap);
	
	/**
 	* Request to create sweepPoolState class for pool
 	* @param  memoryPool memory pool to attach sweep state to
 	* @return pointer to created class
 	*/
	virtual void *createSweepPoolState(MM_EnvironmentBase *env, MM_MemoryPool *memoryPool);

	/**
 	* Request to destroy sweepPoolState class for pool
 	* @param  sweepPoolState class to destroy
 	*/
	virtual void deleteSweepPoolState(MM_EnvironmentBase *env, void *sweepPoolState);

	virtual void sweep(MM_EnvironmentBase *env);
	virtual void completeSweep(MM_EnvironmentBase *env, SweepCompletionReason reason);
	virtual bool sweepForMinimumSize(MM_EnvironmentBase *env, MM_MemorySubSpace *baseMemorySubSpace, MM_AllocateDescription *allocateDescription);

	MM_SweepPoolState *getPoolState(MM_MemoryPool *memoryPool);

	bool heapAddRange(MM_EnvironmentBase *env, MM_MemorySubSpace *subspace, uintptr_t size, void *lowAddress, void *highAddress);
	bool heapRemoveRange(MM_EnvironmentBase *env, MM_MemorySubSpace *subspace, uintptr_t size, void *lowAddress, void *highAddress,	void *lowValidAddress, void *highValidAddress);
	/**
	 * Called after the heap geometry changes to allow any data structures dependent on this to be updated.
	 * This call could be triggered by memory ranges being added to or removed from the heap or memory being
	 * moved from one subspace to another.
	 * @param env[in] The thread which performed the change in heap geometry 
	 */
	void heapReconfigured(MM_EnvironmentBase *env);

#if defined(OMR_GC_CONCURRENT_SWEEP)
	virtual bool replenishPoolForAllocate(MM_EnvironmentBase *env, MM_MemoryPool *memoryPool, uintptr_t size);
#endif /* OMR_GC_CONCURRENT_SWEEP */

	/**
	 * Accurately measure the dark matter within the mark map uintptr_t beginning at heapSlotFreeCurrent.
	 * Leading dark matter (before the first marked object) is not included.
	 * Trailing dark matter (after the last marked object) is included, even if it falls outside of the
	 * mark map range.
	 *
	 * For each heap visit, collect information whether the object is scannable.
	 *
	 * @param sweepChunk[in] the sweepChunk to be measured
	 * @param markMapCurrent[in] the address of the mark map word to be measured
	 * @param heapSlotFreeCurrent[in] the first slot in the section of heap to be measured
	 *
	 * @return the dark matter, measured in bytes, in the range
	 */
	uintptr_t performSamplingCalculations(MM_ParallelSweepChunk *sweepChunk, uintptr_t* markMapCurrent, uintptr_t* heapSlotFreeCurrent);

	virtual bool isSweepCompleted(MM_EnvironmentBase* env) { return true; }

	/**
	 * Create a ParallelSweepScheme object.
	 */
	MM_ParallelSweepScheme(MM_EnvironmentBase *env)
		: MM_BaseVirtual()
		, _chunksPrepared(0)
		, _extensions(env->getExtensions())
		, _dispatcher(_extensions->dispatcher)
		, _currentMarkMap(NULL)
		, _currentSweepBits(NULL)
		, _heapBase(NULL)
		, _sweepHeapSectioning(NULL)
		, _poolSweepPoolState(NULL)
		, _mutexSweepPoolState(0)
	{
		_typeId = __FUNCTION__;
	}

	/*
	 * Friends
	 */
	friend class MM_ParallelSweepTask;
};

#endif /* PARALLELSWEEPSCHEME_HPP_ */
