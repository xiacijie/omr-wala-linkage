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

#include "omrportptb.h"


/**
 * @internal
 * @brief  Per Thread Buffer Support
 *
 * Free all memory associated with a per thread buffer, including any memory it may
 * have allocated.
 *
 * @param[in] portLibrary The port library.
 * @param[in] ptBuffers pointer to the PortlibPTBuffers struct that contains the buffers
 */
void
omrport_free_ptBuffer(struct OMRPortLibrary *portLibrary, PortlibPTBuffers_t ptBuffer)
{
#if defined(J9VM_PROVIDE_ICONV)
	int i;
#endif /* J9VM_PROVIDE_ICONV  */

	if (NULL != ptBuffer) {
		if (NULL != ptBuffer->errorMessageBuffer) {
			portLibrary->mem_free_memory(portLibrary, ptBuffer->errorMessageBuffer);
			ptBuffer->errorMessageBufferSize = 0;
		}
		if (NULL != ptBuffer->reportedMessageBuffer) {
			portLibrary->mem_free_memory(portLibrary, ptBuffer->reportedMessageBuffer);
			ptBuffer->reportedMessageBufferSize = 0;
		}

#if defined(J9VM_PROVIDE_ICONV)
		for (i = 0; i < UNCACHED_ICONV_DESCRIPTOR; i++) {
			if (J9VM_INVALID_ICONV_DESCRIPTOR != ptBuffer->converterCache[i]) {
				iconv_close(ptBuffer->converterCache[i]);
			}
		}
#endif /* J9VM_PROVIDE_ICONV */

		portLibrary->mem_free_memory(portLibrary, ptBuffer);
	}
}

