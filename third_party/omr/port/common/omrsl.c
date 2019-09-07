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
 * @file
 * @ingroup Port
 * @brief shared library
 */
#include "omrport.h"



/**
 * Close a shared library.
 *
 * @param[in] portLibrary The port library.
 * @param[in] descriptor Shared library handle to close.
 *
 * @return 0 on success, any other value on failure.
 */
uintptr_t
omrsl_close_shared_library(struct OMRPortLibrary *portLibrary, uintptr_t descriptor)
{
	return 1;
}

/**
 * Search for a function named 'name' taking argCount in the shared library 'descriptor'.
 *
 * @param[in] portLibrary The port library.
 * @param[in] descriptor Shared library to search.
 * @param[in] name Function to look up.
 * @param[out] func Pointer to the function.
 * @param[in] argSignature Argument signature.
 *
 * @return 0 on success, any other value on failure.
 *
 * argSignature is a C (ie: NUL-terminated) string with the following possible values for each character:
 *
 *		V	- void
 *		Z	- boolean
 *		B	- byte
 *		C	- char (16 bits)
 *		I	- integer (32 bits)
 *		J	- long (64 bits)
 *		F	- float (32 bits)
 *		D	- double (64 bits)
 *		L	- object / pointer (32 or 64, depending on platform)
 *		P	- pointer-width platform data. (in J9 terms an intptr_t)
 *
 * Lower case signature characters imply unsigned value.
 * Upper case signature characters imply signed values.
 * If it doesn't make sense to be signed/unsigned (eg: V, L, F, D Z) the character is upper case.
 *
 * argList[0] is the return type from the function.
 * The argument list is as it appears in english: list is left (1) to right (argCount)
 *
 * @note contents of func are undefined on failure.
 */
uintptr_t
omrsl_lookup_name(struct OMRPortLibrary *portLibrary, uintptr_t descriptor, char *name, uintptr_t *func, const char *argSignature)
{
	return 1;
}

/**
 * Opens a shared library .
 *
 * @param[in] portLibrary The port library.
 * @param[in] name path Null-terminated string containing the shared library.
 * @param[out] descriptor Pointer to memory which is filled in with shared-library handle on success.
 * @param[in] flags bitfield comprised of OMRPORT_SLOPEN_* constants
 *
 * @return 0 on success, any other value on failure.
 *
 * @note contents of descriptor are undefined on failure.
 */
uintptr_t
omrsl_open_shared_library(struct OMRPortLibrary *portLibrary, char *name, uintptr_t *descriptor, uintptr_t flags)
{
	return 1;
}

/**
 * PortLibrary shutdown.
 *
 * This function is called during shutdown of the portLibrary.  Any resources that were created by @ref omrsl_startup
 * should be destroyed here.
 *
 * @param[in] portLibrary The port library.
 *
 * @note Most implementations will be empty.
 */
void
omrsl_shutdown(struct OMRPortLibrary *portLibrary)
{
}
/**
 * PortLibrary startup.
 *
 * This function is called during startup of the portLibrary.  Any resources that are required for
 * the shared library operations may be created here.  All resources created here should be destroyed
 * in @ref omrsl_shutdown.
 *
 * @param[in] portLibrary The port library.
 *
 * @return 0 on success, negative error code on failure.  Error code values returned are
 * \arg OMRPORT_ERROR_STARTUP_SL
 *
 * @note Most implementations will simply return success.
 */
int32_t
omrsl_startup(struct OMRPortLibrary *portLibrary)
{
	return 0;
}


