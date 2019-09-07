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

#include "omr.h"

#include "GCExtensionsBase.hpp"
#include "LightweightNonReentrantLock.hpp"
#include "Packet.hpp"
#include "PacketList.hpp"

bool 
MM_PacketList::initialize(MM_EnvironmentBase *env)
{
	MM_GCExtensionsBase *extensions = env->getExtensions();
	bool result = true;
	
	_sublistCount = extensions->packetListSplit;
	Assert_MM_true(0 < _sublistCount);

	_sublists = (struct PacketSublist *)extensions->getForge()->allocate(sizeof(struct PacketSublist) * _sublistCount, OMR::GC::AllocationCategory::FIXED, OMR_GET_CALLSITE());
	if (NULL == _sublists) {
		result = false;
	} else {
		for (uintptr_t i = 0; i < _sublistCount; i++) {
			_sublists[i] = PacketSublist();
			if (!_sublists[i].initialize(env)) {
				result = false;
				break;
			}
		}
	}

	return result;
}

void
MM_PacketList::tearDown(MM_EnvironmentBase *env)
{
	MM_GCExtensionsBase *extensions = env->getExtensions();

	if (NULL != _sublists) {
		for (uintptr_t i = 0; i < _sublistCount; i++) {
			_sublists[i]._lock.tearDown();
		}
		extensions->getForge()->free(_sublists);
		_sublists = NULL;
	}
}

void 
MM_PacketList::pushList(MM_Packet *head, MM_Packet *tail, uintptr_t count)
{
	/* just push everything on the first list */
	PacketSublist *list = &_sublists[0];
	MM_Packet *current = head;
	uintptr_t i;
	
	list->_lock.acquire();
	
	if (NULL == list->_head) {
		list->_tail = tail;
	} else {
		list->_head->_previous = tail;
	}
	tail->_next = list->_head;
	list->_head = head;
	incrementCount(count);
	
	for (i = 0; i < count; ++i) {
		current->setSublistIndex(0);
		current = current->_next;
	}

	list->_lock.release();
}

bool
MM_PacketList::popList(MM_Packet **head, MM_Packet **tail, uintptr_t *count)
{
	bool didPop = false;
	
	*head = NULL;
	*tail = NULL;
	*count = 0;
	
	/* acquire all of our locks */
	for (uintptr_t i = 0; i < _sublistCount; i++) {
		PacketSublist *list = &_sublists[i];
		list->_lock.acquire();
	}

	/* accumulate all of the packets into a single list */
	for (uintptr_t i = 0; i < _sublistCount; i++) {
		PacketSublist *list = &_sublists[i];
	
		if (NULL != list->_head) {
			didPop = true;

			if (NULL == *head) {
				*head = list->_head;
			} else {
				(*tail)->_next = list->_head;
			}
			Assert_MM_true(NULL != list->_tail);
			*tail = list->_tail;
	
			list->_head = NULL;
			list->_tail = NULL;
		}
	}
	
	*count = _count;
	_count = 0;
	
	/* release all of our locks */
	for (uintptr_t i = 0; i < _sublistCount; i++) {
		PacketSublist *list = &_sublists[i];
		list->_lock.release();
	}
	
	return didPop;
}

void
MM_PacketList::remove(MM_Packet *packetToRemove)
{
	PacketSublist *list = &_sublists[packetToRemove->getSublistIndex()];
	MM_Packet *previous = NULL;
	MM_Packet *next = NULL;
	
	list->_lock.acquire();
	
	previous = packetToRemove->_previous;
	next = packetToRemove->_next;
	
	if (NULL == previous) {
		list->_head = next;
	} else {
		previous->_next = next;
	}
	
	if (NULL == next) {
		list->_tail = previous;
	} else {
		next->_previous = previous;
	}
	
	decrementCount(1);

	list->_lock.release();
}

/**
 * Return the first element in the list.
 * This should be avoided as it combines all sublists in to one
 * single list which is a big hit to performance.
 *
 * @return head The first entry in the list
 */
MM_Packet *
MM_PacketList::getHead() 
{
	MM_Packet *result = NULL;
	
	/* consolidate all lists onto the first list and return its head */
	MM_Packet *head = NULL;
	MM_Packet *tail = NULL;
	uintptr_t count = 0;
	
	if (popList(&head, &tail, &count)) {
		pushList(head, tail, count);
		result = _sublists[0]._head;
	}

	return result;
}

