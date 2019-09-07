/*******************************************************************************
 * Copyright (c) 2006, 2016 IBM Corp. and others
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
 * @ingroup Thread
 * @brief Threading and synchronization support
 */

#include "omrthread.h"
#include "thrdsup.h"
#include "thread_internal.h"

uintptr_t
omrthread_map_native_priority(int nativePriority)
{
	int i;
	int mapPriority;
	int normal = omrthread_get_mapped_priority(J9THREAD_PRIORITY_NORMAL);
	int ascending = omrthread_get_mapped_priority(J9THREAD_PRIORITY_MIN)
					<= omrthread_get_mapped_priority(J9THREAD_PRIORITY_MAX);

	for (i = J9THREAD_PRIORITY_MIN; i <= J9THREAD_PRIORITY_MAX; i++) {
		/* find the closest priority that has higher priority than the given priority */
		mapPriority = omrthread_get_mapped_priority(i);
		if (ascending? (nativePriority <= mapPriority) : (nativePriority >= mapPriority)) {
			if (mapPriority == normal) {
				/* if the native priority of i is the same as the native priority of J9THREAD_PRIORITY_NORMAL
				* then we default to J9THREAD_PRIORITY_NORMAL
				*/
				return J9THREAD_PRIORITY_NORMAL;
			}
			return i;
		}
	}
	/* there is no omrthread priority that is higher than the given priority, so
	 * we return the highest omrthread priority available
	 */
	return J9THREAD_PRIORITY_MAX;
}


int
omrthread_get_mapped_priority(omrthread_prio_t omrthreadPriority)
{
	int priority = priority_map[omrthreadPriority];

	/* When realtime scheduling is used the upper 8 bits are used
	 * for the scheduling policy
	 */
	if (omrthread_lib_use_realtime_scheduling()) {
		priority = (0x00ffffff & priority);
	}

	return priority;
}
