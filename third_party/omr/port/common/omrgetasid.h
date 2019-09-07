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

#ifndef omrgetasid_h
#define omrgetasid_h

#include "omrcomp.h"

/**
 * Get the zOS address space ID (ASID). The ASID is a 2-byte number, usually
 * displayed as 4 hex digits.
 *
 * @param[in] portLibrary The port library.
 * @param[in/out] asid Pointer to string to populate with the ASID.
 * 		an empty string is returned if the ASID is not available
 * @param[in] length The length of the data area addressed by asid.
 *
 * @return 0 on success, size of required buffer on failure.
 */
uintptr_t omrget_asid(struct OMRPortLibrary *portLibrary, char *asid, uintptr_t length);

#endif     /* omrgetasid_h */
