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
  * @brief TTY output
  *
  * All VM output goes to stderr by default.  These routines provide the helpers for such output.
  */
#include "omrport.h"



/**
 * Determine the number of characters remaining to be read from stdin.
 *
 * @param[in] portLibrary The port library.
 *
 * @return number of characters remaining to be read.
 */
intptr_t
omrtty_available(struct OMRPortLibrary *portLibrary)
{
	return 0;
}

/**
 * Output message to stderr.
 *
 * @param[in] portLibrary The port library.
 * @param[in] format The format String.
 * @param[in] ... argument list.
 *
 * @deprecated All output goes to stderr, use omrtty_printf()
 *
 * @internal @note Supported, portable format specifiers are described in the document entitled "PortLibrary printf"
 * in the "Inside J9" Lotus Notes database.
 */
void
omrtty_err_printf(struct OMRPortLibrary *portLibrary, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	portLibrary->tty_err_vprintf(portLibrary, format, args);
	va_end(args);
}



/**
 * Output message to stderr.
 *
 * @param[in] portLibrary The port library.
 * @param[in] format The format String.
 * @param[in] args Variable argument list.
 *
 * @deprecated All output goes to stderr, use omrtty_vprintf()
 *
 * @internal @note Supported, portable format specifiers are described in the document entitled "PortLibrary printf"
 * in the "Inside J9" Lotus Notes database.
 */
void
omrtty_err_vprintf(struct OMRPortLibrary *portLibrary, const char *format, va_list args)
{
	portLibrary->file_vprintf(portLibrary, OMRPORT_TTY_ERR, format, args);
}



/**
 * Read characters from stdin into buffer.
 *
 * @param[in] portLibrary The port library.
 * @param[out] s Buffer.
 * @param[in] length Size of buffer (s).
 *
 * @return The number of characters read, -1 on error.
 */
intptr_t
omrtty_get_chars(struct OMRPortLibrary *portLibrary, char *s, uintptr_t length)
{
	return -1;
}



/**
 * Write characters to stderr.
 *
 * @param[in] portLibrary The port library.
 * @param[in] format The format string to be output.
 * @param[in] ... arguments for format.
 *
 * @note Use omrfile_printf for stdout output.
 *
 * @internal @note Supported, portable format specifiers are described in the document entitled "PortLibrary printf"
 * in the "Inside J9" Lotus Notes database.
 */
void
omrtty_printf(struct OMRPortLibrary *portLibrary, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	portLibrary->tty_vprintf(portLibrary, format, args);
	va_end(args);
}



/**
 * PortLibrary shutdown.
 *
 * This function is called during shutdown of the portLibrary.  Any resources that were created by @ref omrtty_startup
 * should be destroyed here.
 *
 * @param[in] portLibrary The port library.
 *
 * @note Most implementations will be empty.
 */
void
omrtty_shutdown(struct OMRPortLibrary *portLibrary)
{
}
/**
 * PortLibrary startup.
 *
 * This function is called during startup of the portLibrary.  Any resources that are required for
 * the TTY library operations may be created here.  All resources created here should be destroyed
 * in @ref omrtty_shutdown.
 *
 * @param[in] portLibrary The port library.
 *
 * @return 0 on success, negative error code on failure.  Error code values returned are
 * \arg OMRPORT_ERROR_STARTUP_TTY
 * \arg OMRPORT_ERROR_STARTUP_TTY_HANDLE
 * \arg OMRPORT_ERROR_STARTUP_TTY_CONSOLE
 *
 * @note Most implementations will simply return success.
 */
int32_t
omrtty_startup(struct OMRPortLibrary *portLibrary)
{
	return 0;
}
/**
 * Output message to stderr.
 *
 * @param[in] portLibrary The port library.
 * @param[in] format The format String.
 * @param[in] args Variable argument list.
 *
 * @note Use omrfile_vprintf for stdout output.
 *
 * @internal @note Supported, portable format specifiers are described in the document entitled "PortLibrary printf"
 * in the "Inside J9" Lotus Notes database.
 */
void
omrtty_vprintf(struct OMRPortLibrary *portLibrary, const char *format, va_list args)
{
	portLibrary->file_vprintf(portLibrary, OMRPORT_TTY_ERR, format, args);
}

/**
 * This method allows the caller to "daemonize" the current process by closing handles
 * used by the port library
 *
 * @param[in] portLibrary The port library.
 *
 */
void
omrtty_daemonize(struct OMRPortLibrary *portLibrary)
{
}


