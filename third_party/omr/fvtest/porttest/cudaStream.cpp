/*******************************************************************************
 * Copyright (c) 2015, 2015 IBM Corp. and others
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

#include "cudaTests.hpp"

static void
streamCallback(J9CudaStream stream, int32_t error, uintptr_t userData)
{
	*(J9CudaStream *)userData = stream;
}

/**
 * Verify streams API.
 */
TEST_F(CudaDeviceTest, streams)
{
	OMRPORT_ACCESS_FROM_OMRPORT(getPortLibrary());

	for (uint32_t deviceId = 0; deviceId < deviceCount; ++deviceId) {
		J9CudaStream callbackData = NULL;
		J9CudaEvent event = NULL;
		int32_t rc = 0;
		J9CudaStream stream1 = NULL;
		J9CudaStream stream2 = NULL;
		uint32_t streamFlags = 0;
		int32_t streamPriority = 0;

		rc = omrcuda_streamCreate(deviceId, &stream1);

		ASSERT_EQ(0, rc) << "omrcuda_streamCreate failed";
		ASSERT_NOT_NULL(stream1) << "created null stream";

		rc = omrcuda_streamCreateWithPriority(deviceId, -1, J9CUDA_STREAM_FLAG_NON_BLOCKING, &stream2);

		ASSERT_EQ(0, rc) << "omrcuda_streamCreateWithPriority failed";
		ASSERT_NOT_NULL(stream2) << "created null stream";

		rc = omrcuda_eventCreate(deviceId, J9CUDA_EVENT_FLAG_DEFAULT, &event);

		ASSERT_EQ(0, rc) << "omrcuda_eventCreate failed";
		ASSERT_NOT_NULL(event) << "created null event";

		rc = omrcuda_eventRecord(deviceId, event, stream1);

		ASSERT_EQ(0, rc) << "omrcuda_eventRecord failed";

		rc = omrcuda_streamWaitEvent(deviceId, stream2, event);

		ASSERT_EQ(0, rc) << "omrcuda_streamWaitEvent failed";

		rc = omrcuda_streamAddCallback(deviceId, stream2, streamCallback, (uintptr_t)&callbackData);

		ASSERT_EQ(0, rc) << "omrcuda_streamAddCallback failed";

		rc = omrcuda_streamGetFlags(deviceId, stream2, &streamFlags);

		ASSERT_EQ(0, rc) << "omrcuda_streamGetFlags failed";

		rc = omrcuda_streamGetPriority(deviceId, stream2, &streamPriority);

		ASSERT_EQ(0, rc) << "omrcuda_streamGetPriority failed";

		rc = omrcuda_streamSynchronize(deviceId, stream2);

		ASSERT_EQ(0, rc) << "omrcuda_streamSynchronize failed";

		rc = omrcuda_streamQuery(deviceId, stream2);

		ASSERT_EQ(0, rc) << "omrcuda_streamQuery failed";

		ASSERT_EQ(stream2, callbackData) << "callback did not execute correctly";

		if (NULL != stream1) {
			rc = omrcuda_streamDestroy(deviceId, stream1);

			ASSERT_EQ(0, rc) << "omrcuda_streamDestroy failed";
		}

		if (NULL != stream2) {
			rc = omrcuda_streamDestroy(deviceId, stream2);

			ASSERT_EQ(0, rc) << "omrcuda_streamDestroy failed";
		}

		if (NULL != event) {
			rc = omrcuda_eventDestroy(deviceId, event);

			ASSERT_EQ(0, rc) << "omrcuda_eventDestroy failed";
		}
	}
}
