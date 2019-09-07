/*******************************************************************************
 * Copyright (c) 2007, 2016 IBM Corp. and others
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

#include "threadTestLib.hpp"

CMonitor::CMonitor(uintptr_t flags, const char *pName)
{
	if (omrthread_monitor_init_with_name(&m_monitor, flags, (char *) pName)) {
	}
}

CMonitor::CMonitor(const char *pName)
{
	if (omrthread_monitor_init_with_name(&m_monitor, 0, (char *) pName)) {
	}
}

char const *
CMonitor::GetName(void) const
{
	return ((J9ThreadMonitor *) m_monitor)->name;
}

intptr_t
CMonitor::Enter(void)
{
	return omrthread_monitor_enter(m_monitor);
}

intptr_t
CMonitor::EnterUsingThreadId(CThread& self)
{
	return omrthread_monitor_enter_using_threadId(m_monitor, self.GetId());
}

intptr_t
CMonitor::TryEnter(void)
{
	return omrthread_monitor_try_enter(m_monitor);
}

intptr_t
CMonitor::TryEnterUsingThreadId(CThread& self)
{
	return omrthread_monitor_try_enter_using_threadId(m_monitor, self.GetId());
}

intptr_t
CMonitor::Exit(void)
{
	return omrthread_monitor_exit(m_monitor);
}

intptr_t
CMonitor::ExitUsingThreadId(CThread& self)
{
	return omrthread_monitor_exit_using_threadId(m_monitor, self.GetId());
}

intptr_t
CMonitor::Wait(void)
{
	return omrthread_monitor_wait(m_monitor);
}

intptr_t
CMonitor::Wait(int64_t millis)
{
	return omrthread_monitor_wait_timed(m_monitor, millis, 0);
}

intptr_t
CMonitor::Wait(int64_t millis, intptr_t nanos)
{
	return omrthread_monitor_wait_timed(m_monitor, millis, nanos);
}

intptr_t
CMonitor::WaitInterruptable(void)
{
	return omrthread_monitor_wait_interruptable(m_monitor, 0, 0);
}

intptr_t
CMonitor::WaitInterruptable(int64_t millis)
{
	return omrthread_monitor_wait_interruptable(m_monitor, millis, 0);
}

intptr_t
CMonitor::WaitInterruptable(int64_t millis, intptr_t nanos)
{
	return omrthread_monitor_wait_interruptable(m_monitor, millis, nanos);
}

void
CMonitor::NotifyAll(void)
{
	omrthread_monitor_notify_all(m_monitor);
}

void
CMonitor::Notify(void)
{
	omrthread_monitor_notify(m_monitor);
}

omrthread_monitor_t
CMonitor::GetMonitor(void) const
{
	return m_monitor;
}

CMonitor::~CMonitor(void)
{
	omrthread_monitor_destroy(m_monitor);
}

#if defined(OMR_THR_THREE_TIER_LOCKING)
/*
 * These functions inspect the internal state of the monitor.
 * They are extremely unsafe unless the test program is careful.
 */
unsigned int
CMonitor::numBlocking(void)
{
	J9ThreadMonitor *mon = (J9ThreadMonitor *) m_monitor;
	unsigned int count = 0;

	MONITOR_LOCK(m_monitor, 0);
	omrthread_t q = mon->blocking;
	while (q) {
		++count;
		q = q->next;
	}
	MONITOR_UNLOCK(m_monitor);
	return count;
}

bool
CMonitor::isThreadBlocking(CThread& thread)
{
	bool found = false;
	const omrthread_t jthread = thread.getThread();
	J9ThreadMonitor *mon = (J9ThreadMonitor *) m_monitor;

	MONITOR_LOCK(m_monitor, 0);
	omrthread_t q = mon->blocking;
	while (q) {
		if (q == jthread) {
			found = true;
			break;
		}
		q = q->next;
	}

	MONITOR_UNLOCK(m_monitor);
	return found;
}
#endif /* defined(OMR_THR_THREE_TIER_LOCKING) */

CRWMutex::CRWMutex(uintptr_t flags, const char *pName)
{
	if (omrthread_rwmutex_init(&m_monitor, flags, pName)) {
	}
}

void
CRWMutex::EnterRead(void)
{
	omrthread_rwmutex_enter_read(m_monitor);
}

void
CRWMutex::EnterWrite(void)
{
	omrthread_rwmutex_enter_write(m_monitor);
}

void
CRWMutex::ExitRead(void)
{
	omrthread_rwmutex_exit_read(m_monitor);
}

void
CRWMutex::ExitWrite(void)
{
	omrthread_rwmutex_exit_write(m_monitor);
}

CRWMutex::~CRWMutex(void)
{
	omrthread_rwmutex_destroy(m_monitor);
}
