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

/**
 * @file
 * @ingroup GC_Stats
 */

#if !defined(GLOBALVLHGCSTATS_HPP_)
#define GLOBALVLHGCSTATS_HPP_

#include "omrcfg.h"
#include "omrcomp.h"

#if defined(OMR_GC_VLHGC)

/**
 * Storage for statistics relevant to global garbage collections
 * @ingroup GC_Stats
 */
class MM_GlobalVLHGCStats
{
public:
	uintptr_t gcCount;  /**< Count of the number of GC cycles that have occurred */
	uintptr_t incrementCount;	/**< The number of incremental taxation entry point collection operations which have been completed since the VM started */

	MM_GlobalVLHGCStats() :
		gcCount(0)
		,incrementCount(0)
	{};
};

#endif /* OMR_GC_VLHGC */
#endif /* GLOBALVLHGCSTATS_HPP_ */
