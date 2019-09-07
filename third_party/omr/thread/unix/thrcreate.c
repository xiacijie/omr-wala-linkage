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

#include <pthread.h>
#include "threaddef.h"
#include "unix/unixthreadattr.h"

intptr_t
osthread_create(struct J9Thread *self, OSTHREAD *handle, const omrthread_attr_t attr,
				WRAPPER_FUNC entrypoint, WRAPPER_ARG entryarg)
{
	intptr_t retCode;
	unixthread_attr_t ux;

	ASSERT(self);
	ASSERT(handle);
	ASSERT(attr);
	ASSERT(entrypoint);

	ux = (unixthread_attr_t)attr;

	retCode = DEBUG_SYSCALL(pthread_create(handle, &ux->pattr, entrypoint, entryarg));
	if (retCode != 0) {
		if (self) {
#if defined(J9ZOS390)
			/* z stores the error code in errno and errno2, not in the return value from pthread_create() */
			self->os_errno = errno;
			self->os_errno2 = __errno2();
#else /* J9ZOS390 */
			self->os_errno = (omrthread_os_errno_t)retCode;
#endif /* J9ZOS390 */
		}
		return J9THREAD_ERR_THREAD_CREATE_FAILED | J9THREAD_ERR_OS_ERRNO_SET;
	}
	return J9THREAD_SUCCESS;
}
