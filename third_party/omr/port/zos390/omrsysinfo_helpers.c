/*******************************************************************************
 * Copyright (c) 1991, 2015 IBM Corp. and others
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
 * @file sysinfo_helpers.c
 * @ingroup Port
 * @brief Contains implementation of methods to retrieve memory and processor info details.
 */

#include <errno.h>
#include <sys/__wlm.h>

#include "atoe.h"
#include "omrport.h"
#include "omrsimap.h"
#include "omrzfs.h"
#include "omrsysinfo_helpers.h"
#include "ut_omrport.h"

/* Function retrieves and populates memory usage statistics on a z/OS platform. */
int32_t
retrieveZOSMemoryStats(struct OMRPortLibrary *portLibrary, struct J9MemoryInfo *memInfo)
{
	uint64_t userCacheUsed = 0;
	uint64_t bufferCacheSize = 0;
	int32_t rc = 0;
	/* CVT address should be obtained in the following way to avoid Zero-Address Detection (ZAD)
	 * event (see JTCJAZZ: 60569)
	 */
	J9CVT *__ptr32 cvtp = ((J9PSA * __ptr32)0)->flccvt;
	J9RCE *__ptr32 rcep = cvtp->cvtrcep;
	J9ASMVT *__ptr32 asmvtp = cvtp->cvtasmvt;

	Trc_PRT_retrieveZOSMemoryStats_Entered();
	Assert_PRT_true(NULL != memInfo);
	memInfo->totalPhysical = ((uint64_t)rcep->rcepool * J9BYTES_PER_PAGE);
	memInfo->availPhysical = ((uint64_t)rcep->rceafc * J9BYTES_PER_PAGE);
	memInfo->totalSwap = ((uint64_t)asmvtp->asmslots * J9BYTES_PER_PAGE);
	memInfo->availSwap = ((uint64_t)(asmvtp->asmslots - (asmvtp->asmvsc + asmvtp->asmnvsc
									 + asmvtp->asmerrs)) * J9BYTES_PER_PAGE);
	rc = getZFSUserCacheUsed(&userCacheUsed);
	if (0 == rc) {
		memInfo->cached = userCacheUsed;
	}

	rc = getZFSMetaCacheSize(&bufferCacheSize);
	if (0 == rc) {
		memInfo->buffered = bufferCacheSize;
	}

	memInfo->hostAvailPhysical = memInfo->availPhysical;
	memInfo->hostCached = memInfo->cached;
	memInfo->hostBuffered = memInfo->buffered;

	Trc_PRT_retrieveZOSMemoryStats_memUsageStats_v1(
		memInfo->totalPhysical,
		memInfo->availPhysical,
		memInfo->totalSwap,
		memInfo->availSwap,
		memInfo->cached,
		memInfo->buffered);

	Trc_PRT_retrieveZOSMemoryStats_Exit(0);
	return 0;
}

/* Function retrieves and populates processor usage statistics on a z/OS platform. */
int32_t
retrieveZOSProcessorStats(struct OMRPortLibrary *portLibrary, struct J9ProcessorInfos *procInfo)
{
	/* CVT address should be obtained in the following way to avoid Zero-Address Detection (ZAD)
	 * event (see JTCJAZZ: 60569)
	 */
	J9CVT *__ptr32 cvtp = ((J9PSA * __ptr32)0)->flccvt;
	J9RMCT *__ptr32 rmctp = cvtp->cvtopctp;
	J9CCT *__ptr32 cctp = rmctp->rmctcct;

	Trc_PRT_retrieveZOSProcessorStats_Entered();
	Assert_PRT_true(NULL != procInfo);
	/* The only valid processor times that z/OS exposes are the total Busy and Idle times. */
	procInfo->procInfoArray[0].idleTime = cctp->ccvrbswt;
	procInfo->procInfoArray[0].busyTime = (cctp->ccvrbstd * cctp->ccvcpuct) - cctp->ccvrbswt;

	Trc_PRT_retrieveZOSProcessorStats_cpuUsageStats_v1(procInfo->procInfoArray[0].idleTime, procInfo->procInfoArray[0].busyTime);

	Trc_PRT_retrieveZOSProcessorStats_Exit(0);
	return 0;
}
