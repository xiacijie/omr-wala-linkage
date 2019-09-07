/*******************************************************************************
 * Copyright (c) 2013, 2016 IBM Corp. and others
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

#include <string.h>

#include "OMR_Runtime.hpp"
#include "OMR_VM.hpp"
#include "OMR_VMThread.hpp"

#include "omrutil.h"
#include "ut_omrvm.h"

extern "C" {

OMR_VMThread *
omr_vmthread_getCurrent(OMR_VM *vm)
{
	OMR_VMThread *currentThread = NULL;
	omrthread_t self = omrthread_self();
	if (NULL != self) {
		if (vm->_vmThreadKey > 0) {
			currentThread = (OMR_VMThread *)omrthread_tls_get(self, vm->_vmThreadKey);
		}
	}
	return currentThread;
}

omr_error_t
omr_vmthread_alloc(OMR_VM *vm, OMR_VMThread **vmthread)
{
	omr_error_t rc = OMR_ERROR_NONE;

	OMRPORT_ACCESS_FROM_OMRVM(vm);
	*vmthread = (OMR_VMThread *)omrmem_allocate_memory(sizeof(OMR_VMThread), OMRMEM_CATEGORY_VM);
	if (NULL == *vmthread) {
		rc = OMR_ERROR_OUT_OF_NATIVE_MEMORY;
	}
	return rc;
}

omr_error_t
omr_vmthread_init(OMR_VMThread *vmthread)
{
	omr_error_t rc = OMR_ERROR_NONE;

	omrthread_monitor_init(&vmthread->threadNameMutex, 0);
	if (NULL == vmthread->threadNameMutex) {
		rc = OMR_ERROR_FAILED_TO_ALLOCATE_MONITOR;
	}
	return rc;
}

void
omr_vmthread_destroy(OMR_VMThread *vmthread)
{
	if (NULL != vmthread->threadNameMutex) {
		omrthread_monitor_destroy(vmthread->threadNameMutex);
		vmthread->threadNameMutex = NULL;
	}
}

omr_error_t
omr_attach_vmthread_to_vm(OMR_VMThread *vmthread)
{
	omr_error_t rc = OMR_ERROR_NONE;
	omrthread_t self = NULL;

	/* NOTE _attachCount must never be accessed concurrently! */
	if (vmthread->_attachCount > 0) {
		vmthread->_attachCount += 1;
	} else {
		if (0 == omrthread_attach_ex(&self, J9THREAD_ATTR_DEFAULT)) {
			rc = attachThread(vmthread->_vm, vmthread);
			omrthread_detach(self);
			vmthread->_attachCount += 1;
		} else {
			rc = OMR_ERROR_FAILED_TO_ATTACH_NATIVE_THREAD;
		}
	}
	return rc;
}

omr_error_t
omr_detach_vmthread_from_vm(OMR_VMThread *vmthread)
{
	omr_error_t rc = OMR_ERROR_NONE;

	/* NOTE _attachCount must never be accessed concurrently! */
	if (vmthread->_attachCount > 1) {
		vmthread->_attachCount -= 1;
	} else if (1 == vmthread->_attachCount) {
		omrthread_t self = NULL;
		if (0 == omrthread_attach_ex(&self, J9THREAD_ATTR_DEFAULT)) {
			rc = detachThread(vmthread->_vm, vmthread);
			omrthread_detach(self);
			vmthread->_attachCount -= 1;
		} else {
			rc = OMR_ERROR_FAILED_TO_ATTACH_NATIVE_THREAD;
		}
	} else {
		rc = OMR_THREAD_NOT_ATTACHED;
	}
	return rc;
}

/* vmThread must be the current thread, because of omrthread_self() usage */
omr_error_t
omr_vmthread_firstAttach(OMR_VM *vm, OMR_VMThread **vmThread)
{
	omr_error_t rc = OMR_ERROR_NONE;
	OMRPORT_ACCESS_FROM_OMRVM(vm);

	OMR_VMThread *tempThread = (OMR_VMThread *)omrmem_allocate_memory(sizeof(OMR_VMThread), OMRMEM_CATEGORY_VM);
	if (NULL != tempThread) {
		memset(tempThread, 0, sizeof(*tempThread));
		rc = omr_vmthread_init(tempThread);
		if (OMR_ERROR_NONE == rc) {
			/* OMRTODO this should go in omr_vmthread_init() */
			tempThread->_vm = vm;
			tempThread->_language_vmthread = NULL;
			tempThread->_os_thread = omrthread_self();
			tempThread->_internal = 1; /* unused by JVM */

			rc = attachThread(vm, tempThread);
			if (OMR_ERROR_NONE == rc) {
				tempThread->_attachCount = 1;
				*vmThread = tempThread;
			}
		}

		/* If an error occurred, free the newly allocated thread */
		if (OMR_ERROR_NONE != rc) {
			omrmem_free_memory(tempThread);
		}
	} else {
		rc = OMR_ERROR_OUT_OF_NATIVE_MEMORY;
	}
	return rc;
}

omr_error_t
omr_vmthread_lastDetach(OMR_VMThread *vmThread)
{
	omr_error_t rc = OMR_ERROR_NONE;
	OMR_VM *omrVM = vmThread->_vm;
	OMRPORT_ACCESS_FROM_OMRVM(omrVM);

	rc = detachThread(omrVM, vmThread);
	if (OMR_ERROR_NONE == rc) {
		omr_vmthread_destroy(vmThread);
		omrmem_free_memory(vmThread);
	}
	return rc;
}

void
omr_vmthread_reattach(OMR_VMThread *currentThread, const char *threadName)
{
	Assert_OMRVM_true(0 < currentThread->_attachCount);
	currentThread->_attachCount += 1;
	if (NULL != threadName) {
		setOMRVMThreadNameWithFlag(currentThread, currentThread, (char *)threadName, TRUE);
	}
}

void
omr_vmthread_redetach(OMR_VMThread *currentThread)
{
	Assert_OMRVM_true(0 < currentThread->_attachCount);
	currentThread->_attachCount -= 1;
}

}
