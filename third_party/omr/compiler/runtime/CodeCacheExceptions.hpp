/*******************************************************************************
 * Copyright (c) 2016, 2017 IBM Corp. and others
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

#ifndef CODECACHEEXCEPTIONS_HPP
#define CODECACHEEXCEPTIONS_HPP

#pragma once

#include <exception>
#include <new>

namespace TR {

/**
 * Code Cache Allocation Failure exception type.
 *
 * Thrown when the compiler fails to allocate a code cache.
 */
struct CodeCacheError : public virtual std::bad_alloc
   {
   virtual const char* what() const throw() { return "Code Cache Error"; }
   };

/**
 * Recoverable Code Cache Allocation Failure exception type.
 *
 * Thrown on a Code Cache Allocation Failure condition which the
 * compiler can recover from, allowing compilation to proceed.
 */
struct RecoverableCodeCacheError : public virtual std::bad_alloc
   {
   virtual const char* what() const throw() { return "Recoverable Code Cache Error"; }
   };

/**
 * TrampolineError exception type.
 *
 * Thrown for an unrecoverable trampoline reservation or allocation error.
 */
struct TrampolineError : public virtual std::bad_alloc
   {
   virtual const char* what() const throw() { return "Trampoline Error"; }
   };

/**
 * RecoverableTrampolineError exception type.
 *
 * Thrown for any trampoline error situations that the compiler can
 * recover from, allowing compilation to proceed.
 */
struct RecoverableTrampolineError : public virtual std::bad_alloc
   {
   virtual const char* what() const throw() { return "Recoverable Trampoline Error"; }
   };

}

#endif // CODECACHEEXCEPTIONS_HPP
