/*******************************************************************************
 * Copyright (c) 2014, 2018 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at http://eclipse.org/legal/epl-2.0
 * or the Apache License, Version 2.0 which accompanies this distribution
 * and is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following Secondary
 * Licenses when the conditions for such availability set forth in the
 * Eclipse Public License, v. 2.0 are satisfied: GNU General Public License,
 * version 2 with the GNU Classpath Exception [1] and GNU General Public
 * License, version 2 with the OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

#include <string.h>

#include "omrport.h"
#include "omr.h"
#include "omrrasinit.h"
#include "omrTest.h"
#include "omrTestHelpers.h"
#include "omrtrace.h"
#include "omrvm.h"
#include "ut_omr_test.h"

#include "rasTestHelpers.hpp"

/*
 * The executable for this test is omrtraceoptiontest (not omrrastest)
 */

TEST(RASTraceOptionTest, TraceOptionAgent)
{
	/* OMR VM data structures */
	OMRTestVM testVM;
	OMR_VMThread *vmthread = NULL;

	/* OMR Trace data structures */
	const char *trcOpts = "print=all";

	struct OMR_Agent *agent = NULL;
	OMRPORT_ACCESS_FROM_OMRPORT(rasTestEnv->getPortLibrary());
	char *datDir = NULL;

	OMRTEST_ASSERT_ERROR_NONE(omrTestVMInit(&testVM, OMRPORTLIB));

	OMRTEST_ASSERT_ERROR_NONE(OMR_Thread_Init(&testVM.omrVM, NULL, &vmthread, "traceOptionTest"));

	datDir = getTraceDatDir(rasTestEnv->_argc, (const char **)rasTestEnv->_argv);

	OMRTEST_ASSERT_ERROR_NONE(omr_ras_initTraceEngine(&testVM.omrVM, trcOpts, datDir));
	OMRTEST_ASSERT_ERROR_NONE(omr_trc_startThreadTrace(vmthread, "initialization thread"));

	/* load agent */
	agent = omr_agent_create(&testVM.omrVM, "traceOptionAgent");
	ASSERT_FALSE(NULL == agent) << "testAgent: createAgent() traceOptionAgent failed";

	OMRTEST_ASSERT_ERROR_NONE(omr_agent_openLibrary(agent));

	OMRTEST_ASSERT_ERROR_NONE(omr_agent_callOnLoad(agent));

	/* Initialize the omr_test module for tracing */
	UT_OMR_TEST_MODULE_LOADED(testVM.omrVM._trcEngine->utIntf);

	/* Fire some trace points! */
	Trc_OMR_Test_Init();
	Trc_OMR_Test_Ptr(vmthread, vmthread);
	Trc_OMR_Test_Int(vmthread, 10);
	Trc_OMR_Test_Int(vmthread, 99);
	Trc_OMR_Test_ManyParms(vmthread, "Hello again!", vmthread, 10);

	UT_OMR_TEST_MODULE_UNLOADED(testVM.omrVM._trcEngine->utIntf);

	/* Unload the agent */
	OMRTEST_ASSERT_ERROR_NONE(omr_agent_callOnUnload(agent));
	omr_agent_destroy(agent);

	Trc_OMR_Test_String(vmthread, "This tracepoint should be ignored.");

	OMRTEST_ASSERT_ERROR_NONE(omr_ras_cleanupTraceEngine(vmthread));

	OMRTEST_ASSERT_ERROR_NONE(OMR_Thread_Free(vmthread));

	/* Now clear up the VM we started for this test case. */
	OMRTEST_ASSERT_ERROR_NONE(omrTestVMFini(&testVM));
}
