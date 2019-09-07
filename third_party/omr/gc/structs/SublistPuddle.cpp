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
 * @ingroup GC_Structs
 */

#include "omrcfg.h"
#include "omrcomp.h"
#include "omrport.h"

#include <string.h>

#include "SublistPuddle.hpp"

#include "AtomicOperations.hpp"
#include "EnvironmentBase.hpp"
#include "SublistFragment.hpp"

/**
 * Initialize the sublist puddle for use.
 * Given the size for element storage, initialize the default values to represent an empty puddle.
 * 
 * @return true if the initialization is successful, false otherwise.
 */
bool
MM_SublistPuddle::initialize(MM_EnvironmentBase *env, uintptr_t size, MM_SublistPool *parent)
{
	/* Clear all members and element backing store */
	memset(this, 0, sizeof(*this) + size);

	/* Record the size */
	_size = size;

	/* Reset the list pointers */
	_listBase = (uintptr_t *)(this + 1);
	_listCurrent = _listBase;
	_listTop = (uintptr_t *) (((uint8_t *)_listBase) + size);
	
	/* Remember the parent pool */
	_parent = parent;

	return true;
}

/**
 * Create a new instance of a sublist puddle.
 * Given the size of the element backing store, create and return a newly initialized sublist puddle.
 * 
 * @return An initialized instance of a sublist puddle with backing store
 */
MM_SublistPuddle *
MM_SublistPuddle::newInstance(MM_EnvironmentBase *env, uintptr_t size, MM_SublistPool *parent, OMR::GC::AllocationCategory::Enum category)
{
	MM_SublistPuddle *puddle = (MM_SublistPuddle *) env->getForge()->allocate(size + sizeof(MM_SublistPuddle), category, OMR_GET_CALLSITE());

	if(NULL == puddle) {
		return NULL;
	}
	puddle->initialize(env, size, parent);

	return puddle;
}

/**
 * Free a sublist puddle and clean up any internal structures
 */
void
MM_SublistPuddle::kill(MM_EnvironmentBase *env, MM_SublistPuddle *puddle)
{
	puddle->tearDown(env);
	env->getForge()->free(puddle);
}

/**
 * Allocate a sublist fragment from a puddle.
 * Update a fragment by allocating a subrange from the given puddle, and updating the fragment with
 * the details of the new range.  The allocate is a simple bump pointer allocate that is contended.
 * On failure, no recovery operations are run.
 * 
 * @return true if the fragment allocate was successfull, false otherwise.
 */
bool
MM_SublistPuddle::allocate(MM_SublistFragment *fragment)
{
	uintptr_t growSize;
	uintptr_t oldListCurrent, newListCurrent = 0;

	/* Loop on trying to allocate a fragment range from the puddle until successfull or there is no room */
	do {
		/* Record the old current pointer (required from proper bump pointer allocation) */
		oldListCurrent = (uintptr_t)_listCurrent;

		/* Validate the grow size */
		growSize = ((uintptr_t)_listTop) - oldListCurrent;
		if(0 == growSize) {
			/* There was no more room - fail to allocate */
			return false;
		}
		if(growSize > fragment->getFragmentSize()) {
			growSize = fragment->getFragmentSize();
		}

		/* Calculate the new pointer after a successful allocate */
		newListCurrent = oldListCurrent + growSize;

	} while(oldListCurrent != MM_AtomicOperations::lockCompareExchange((volatile uintptr_t *)&_listCurrent, oldListCurrent, newListCurrent));

	/* Allocate was successful.  Update the fragment and return */
	fragment->update((uintptr_t *)oldListCurrent, (uintptr_t *)newListCurrent);
	return true;
}

/**
 * Allocate a single element from the puddle.
 * 
 * @return An element slot allocated from the puddle on success, NULL otherwise.
 * 
 * @note Assumes no contention when allocating the element.
 */
uintptr_t *
MM_SublistPuddle::allocateElementNoContention()
{
	if(_listCurrent < _listTop) {
		return _listCurrent++;
	}
	return NULL;
}

/**
 * Reset the puddle for list and backing store for consumption.
 * Fragments have an expectation that when allocated, the entries are NULL.  The backing store of a
 * puddle (the range from the base to the top pointer) is cleared.
 */
void
MM_SublistPuddle::reset()
{
	memset((void *)_listBase, 0, _size);
	_listCurrent = _listBase;
}

/**
 * Merge a sublist puddle into the receiver.
 * Copy as many entries from the sourcePuddle into the receiver as can fit.  There is the possibility
 * that the sourcePuddle will not have all of its elements copied.  The routine guarantees that both
 * puddles will be in the correct state (with internal list pointers correctly adjusted) upon return.
 */
void
MM_SublistPuddle::merge(MM_SublistPuddle *sourcePuddle)
{
	uintptr_t availableSize, copySize;

	availableSize = freeSize();
	copySize = sourcePuddle->consumedSize();

	/* Determine the actual copy size */
	if(availableSize < copySize) {
		copySize = availableSize;
	}

	/* Copy the data from the tail of the source puddle */
	memcpy(_listCurrent, ((uint8_t *)sourcePuddle->_listCurrent) - copySize, copySize);
	/* And clear the data from the source puddle (fragments require preinitialized slots) */
	memset(((uint8_t *)sourcePuddle->_listCurrent) - copySize, 0, copySize);

	/* Adjust the receiver and source puddle list pointers */
	_listCurrent = (uintptr_t *) (((uint8_t *)_listCurrent) + copySize);
	sourcePuddle->_listCurrent = (uintptr_t *) (((uint8_t *)sourcePuddle->_listCurrent) - copySize);
}



