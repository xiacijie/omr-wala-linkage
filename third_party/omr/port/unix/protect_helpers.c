/*******************************************************************************
 * Copyright (c) 1991, 2017 IBM Corp. and others
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

#include "omrcomp.h"
#include "omrport.h"
#include "omrportpriv.h"
#include <errno.h>
#include <sys/mman.h>

struct {
	uint32_t portLibPermission;
	int unixPermission;
} permissionsMap[] = {
	{OMRPORT_PAGE_PROTECT_NONE, PROT_NONE},
	{OMRPORT_PAGE_PROTECT_READ, PROT_READ},
	{OMRPORT_PAGE_PROTECT_WRITE, PROT_WRITE},
	{OMRPORT_PAGE_PROTECT_EXEC, PROT_EXEC}
};

/**
 * @internal @file
 * @ingroup Port
 * @brief Helpers for protecting shared memory regions in the virtual address space (used by omrmmap and j9shmem).
 */

/* Helper for j9shmem and omrmmap.
 *
 * Adheres to the j9shmem_protect() and omrmmap() APIs
 */
intptr_t
protect_memory(struct OMRPortLibrary *portLibrary, void *address, uintptr_t length, uintptr_t flags)
{
#if defined(OMRZTPF)
	/* Return success, zTPF does not support mprotect. */
	IDATA rc = 0;

	return rc;
#else /* defined(OMRZTPF) */
	uintptr_t index;
	intptr_t unixFlags = 0;
	intptr_t rc = -1;

	/* convert the port library permissions to the UNIX equivalents */
	for (index = 0; index < sizeof(permissionsMap) / sizeof(permissionsMap[0]); index++) {
		if ((permissionsMap[index].portLibPermission & flags) != 0) {
			unixFlags |= permissionsMap[index].unixPermission;
		}
	}

	rc = mprotect(address, length, unixFlags);
	if (rc != 0) {
		portLibrary->error_set_last_error(portLibrary, errno, OMRPORT_PAGE_PROTECT_FAILED);
		/* TODO: set the actual error message as well */
	}

	return rc;
#endif /* defined(OMRZTPF) */
}

uintptr_t
protect_region_granularity(struct OMRPortLibrary *portLibrary, void *address)
{

	uintptr_t granularity = 0;

	granularity = omrvmem_supported_page_sizes(portLibrary)[0];

	return granularity;
}
