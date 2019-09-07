/*******************************************************************************
 * Copyright (c) 2013, 2017 IBM Corp. and others
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

#if !defined(DDR_UNORDERED_MAP)
#define DDR_UNORDERED_MAP

#include "ddr/config.hpp"

#if defined(J9ZOS390)
#include <ctype.h>
#undef toupper
#undef tolower
#endif /* defined(J9ZOS390) */

#if defined(OMR_HAVE_CXX11)
#include <unordered_map>
using std::unordered_map;
#elif defined(OMR_HAVE_TR1)
#include <unordered_map>
using std::tr1::hash;
using std::tr1::unordered_map;
#else /* defined(OMR_HAVE_CXX11) */
#error "Need std::unordered_map defined in TR1 or C++11."
#endif /* defined(OMR_HAVE_CXX11) */

#if defined(J9ZOS390)
#define toupper(c)     (islower(c) ? (c & _XUPPER_ASCII) : c)
#define tolower(c)     (isupper(c) ? (c | _XLOWER_ASCII) : c)
#endif /* defined(J9ZOS390) */

#endif /* DDR_UNORDERED_MAP */
