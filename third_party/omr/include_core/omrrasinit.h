/*******************************************************************************
 * Copyright (c) 2014, 2016 IBM Corp. and others
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

#ifndef omrrasinit_h
#define omrrasinit_h

#include "omr.h"
#include "omrtrace.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct OMR_Agent OMR_Agent;

/**
 * @brief Initialize port library memory categories.
 *
 * This should be done before any significant memory allocations are made.
 * This function cannot be called more than once in the lifetime of the port library.
 * Memory category definitions cannot be changed after they are initialized.
 *
 * @pre attached to omrthread
 *
 * @param[in] portLibrary The port library.
 *
 * @return an OMR error code
 */
omr_error_t omr_ras_initMemCategories(OMRPortLibrary *portLibrary);

/**
 * @brief Start the HealthCenter agent.
 *
 * Some functionality may be unavailable if the trace engine is not enabled.
 *
 * @pre omrVM is initialized
 * @pre attached to omrthread
 *
 * @param[in,out] omrVM The current OMR VM.
 * @param[out]    hc The healthcenter agent.
 * @param[in]     healthCenterOpt Option string passed to the agent's OMRAgent_OnLoad() function.
 * @return an OMR error code
 */
omr_error_t omr_ras_initHealthCenter(OMR_VM *omrVM, OMR_Agent **hc, const char *healthCenterOpt);

/**
 * @brief Shutdown and destroy the HealthCenter agent.
 *
 * @param[in,out] omrVM The current OMR VM.
 * @param[in,out] hc The healthcenter agent.
 * @return an OMR error code
 */
omr_error_t omr_ras_cleanupHealthCenter(OMR_VM *omrVM, OMR_Agent **hc);

/**
 * @internal
 * @brief Initialize data structures that support the OMR_TI API.
 *
 * This function is called by omr_ras_initHealthCenter().
 * It is public for the benefit of the FVT test framework.
 *
 * @param[in] vm the current OMR VM
 * @return OMR error code
 */
omr_error_t omr_ras_initTI(OMR_VM *vm);

/**
 * @internal
 * @brief Cleanup data structures that support the OMR_TI API.
 *
 * This function is called by omr_ras_cleanupHealthCenter().
 * It is public for the benefit of the FVT test framework.
 *
 * @param[in] vm the current OMR VM
 * @return an OMR error code. There is no error if TI was uninitialized.
 */
omr_error_t omr_ras_cleanupTI(OMR_VM *vm);

/**
 * @brief Initialize the trace engine.
 *
 * @pre omrVM is initialized
 * @pre attached to omrthread
 *
 * @param[in,out] omrVM The current OMR VM.
 * @param[in]     traceOptstring Trace options string. e.g. "maximal=all:buffers=1k"
 * @param[in]     datDir Path containing trace format files (*TraceFormat.dat).
 * @return an OMR error code
 */
omr_error_t omr_ras_initTraceEngine(OMR_VM *omrVM, const char *traceOptString, const char *datDir);

/**
 * @brief Shutdown and destroy the trace engine.
 *
 * @param[in]     currentThread The current OMR VMThread.
 * @return an OMR error code
 */
omr_error_t omr_ras_cleanupTraceEngine(OMR_VMThread *currentThread);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* omrrasinit_h */
