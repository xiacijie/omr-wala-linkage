/*******************************************************************************
 * Copyright (c) 2015, 2015 IBM Corp. and others
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

#include <stdlib.h>
#include "omrport.h"
#include "omrgetasid.h"

#define ASID_STRING_LENGTH 5

/* Get the zOS address space ID (ASID) */
uintptr_t
omrget_asid(struct OMRPortLibrary *portLibrary, char *asid, uintptr_t length)
{
	/* See ASCB control block definition in z/OS MVS Data Areas Volume 1 */
	struct ascb {
		char _padding[36]; /* hex 0x24 */
		unsigned short ascbasid;
	};
	/* See PSA control block definition in z/OS MVS Data Areas Volume 5 */
	struct psa {
		char _padding[548]; /* hex 0x224 */
		struct ascb *__ptr32 psaaold;
	};

	/* Check that caller provided enough space for the string */
	if ((NULL == asid) || (length < ASID_STRING_LENGTH)) {
		return ASID_STRING_LENGTH;
	}
	asid[0] = '\0';

	/* z/OS PSA control block is at address zero */
	struct psa *psa_ptr = 0;
	/* Address of ASCB control block is PSAAOLD field in PSA control block */
	struct ascb *__ptr32 ascb_ptr = psa_ptr->psaaold;

	if (NULL != ascb_ptr) {
		/* ASID is 2-byte ASCBASID field in ASCB control block */
		portLibrary->str_printf(portLibrary, asid, length, "%.4X", ascb_ptr->ascbasid);
	}

	return 0;
}
