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


#include "omrcfg.h"
#include "omrmodroncore.h"
#include "omrport.h"
#include "modronopt.h"
#include "ut_j9mm.h"

#include "ParallelMarkTask.hpp"

#include "EnvironmentBase.hpp"
#include "MarkingScheme.hpp"
#include "WorkStack.hpp"


uintptr_t
MM_ParallelMarkTask::getVMStateID()
{
	return OMRVMSTATE_GC_MARK;
}

void
MM_ParallelMarkTask::run(MM_EnvironmentBase *env)
{
	env->_workStack.prepareForWork(env, (MM_WorkPackets *)(_markingScheme->getWorkPackets()));

	_markingScheme->markLiveObjectsInit(env, _initMarkMap);
	_markingScheme->markLiveObjectsRoots(env);
	_markingScheme->markLiveObjectsScan(env);
	_markingScheme->markLiveObjectsComplete(env);

	env->_workStack.flush(env);
}

void
MM_ParallelMarkTask::setup(MM_EnvironmentBase *env)
{
	if(env->isMasterThread()) {
		Assert_MM_true(_cycleState == env->_cycleState);
	} else {
		Assert_MM_true(NULL == env->_cycleState);
		env->_cycleState = _cycleState;
	}
}

void
MM_ParallelMarkTask::cleanup(MM_EnvironmentBase *env)
{
	_markingScheme->workerCleanupAfterGC(env);

	if (env->isMasterThread()) {
		Assert_MM_true(_cycleState == env->_cycleState);
	} else {
		env->_cycleState = NULL;
	}
	
	/* record the thread-specific parallelism stats in the trace buffer. This partially duplicates info in -Xtgc:parallel */
	OMRPORT_ACCESS_FROM_OMRPORT(env->getPortLibrary());
	Trc_MM_ParallelMarkTask_parallelStats(
		env->getLanguageVMThread(),
		(uint32_t)env->getSlaveID(),
		(uint32_t)omrtime_hires_delta(0, env->_workPacketStats._workStallTime, OMRPORT_TIME_DELTA_IN_MILLISECONDS),
		(uint32_t)omrtime_hires_delta(0, env->_workPacketStats._completeStallTime, OMRPORT_TIME_DELTA_IN_MILLISECONDS),
		(uint32_t)omrtime_hires_delta(0, env->_markStats._syncStallTime, OMRPORT_TIME_DELTA_IN_MILLISECONDS),
		(uint32_t)env->_workPacketStats._workStallCount,
		(uint32_t)env->_workPacketStats._completeStallCount,
		(uint32_t)env->_markStats._syncStallCount,
		env->_workPacketStats.workPacketsAcquired,
		env->_workPacketStats.workPacketsReleased,
		env->_workPacketStats.workPacketsExchanged,
		0/* TODO CRG figure out to get the array split size*/);
}

#if defined(J9MODRON_TGC_PARALLEL_STATISTICS)
void
MM_ParallelMarkTask::synchronizeGCThreads(MM_EnvironmentBase *env, const char *id)
{
	OMRPORT_ACCESS_FROM_OMRPORT(env->getPortLibrary());
	uint64_t startTime = omrtime_hires_clock();
	MM_ParallelTask::synchronizeGCThreads(env, id);
	uint64_t endTime = omrtime_hires_clock();
	env->_markStats.addToSyncStallTime(startTime, endTime);
}

bool
MM_ParallelMarkTask::synchronizeGCThreadsAndReleaseMaster(MM_EnvironmentBase *env, const char *id)
{
	OMRPORT_ACCESS_FROM_OMRPORT(env->getPortLibrary());
	uint64_t startTime = omrtime_hires_clock();
	bool result = MM_ParallelTask::synchronizeGCThreadsAndReleaseMaster(env, id);
	uint64_t endTime = omrtime_hires_clock();
	env->_markStats.addToSyncStallTime(startTime, endTime);
	
	return result;	
}

bool
MM_ParallelMarkTask::synchronizeGCThreadsAndReleaseSingleThread(MM_EnvironmentBase *env, const char *id)
{
	OMRPORT_ACCESS_FROM_OMRPORT(env->getPortLibrary());
	uint64_t startTime = omrtime_hires_clock();
	bool result = MM_ParallelTask::synchronizeGCThreadsAndReleaseSingleThread(env, id);
	uint64_t endTime = omrtime_hires_clock();
	env->_markStats.addToSyncStallTime(startTime, endTime);

	return result;
}

#endif /* J9MODRON_TGC_PARALLEL_STATISTICS */

