/*******************************************************************************
 * Copyright (c) 1991, 2018 IBM Corp. and others
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

#if !defined(CARDCLEANERFORMARKING_HPP_)
#define CARDCLEANERFORMARKING_HPP_

#include "omrcfg.h"

#include "CardCleaner.hpp"
#include "CollectorLanguageInterface.hpp"
#include "EnvironmentStandard.hpp"
#include "HeapMapIterator.hpp"
#include "MarkingScheme.hpp"

/**
 * @todo Provide typedef documentation
 * @ingroup GC_Modron_Standard
 */

class MM_CardCleanerForMarking : public MM_CardCleaner
{
public:
protected:
private:
	MM_MarkingScheme *_markingScheme;
public:
protected:
	/**
	 * Clean a range of addresses (typically within a span of a card)
	 * The class specifically is used for Incremental-Update style of marking
	 *
	 * @param[in] env A thread (typically the thread initializing the GC)
	 * @param[in] lowAddress low address of the range to be cleaned
	 * @param[in] highAddress high address of the range to be cleaned
	 */
	virtual void clean(MM_EnvironmentBase *envModron, void *lowAddress, void *highAddress, Card *cardToClean)
	{
		MM_EnvironmentStandard *env = MM_EnvironmentStandard::getEnvironment(envModron);
		MM_GCExtensionsBase *extensions = env->getExtensions();

		/* card may be marked dirty in WP overflow, so it is important to mark it clean before any scan */
		*cardToClean = CARD_CLEAN;
		/* previous line value MUST be physically written to memory (relevant for concurrent cleaning) - force such write if necessary */
		MM_AtomicOperations::sync();

		MM_HeapMapIterator markedObjectIterator(extensions, _markingScheme->getMarkMap(), (uintptr_t *)lowAddress, (uintptr_t *)highAddress);
		omrobjectptr_t object = NULL;
		while (NULL != (object = markedObjectIterator.nextObject())) {
			_markingScheme->scanObject(env, object, SCAN_REASON_OVERFLOWED_OBJECT);
		}
	}

	/**
	 * @see MM_CardCleaner::getVMStateID()
	 */
	virtual uintptr_t getVMStateID() { return OMRVMSTATE_GC_CARD_CLEANER_FOR_MARKING; }
	
public:

	/**
	 * Create a CardCleaner object specific for Incremental-Update style of marking
	 */
	MM_CardCleanerForMarking(MM_MarkingScheme *markingScheme)
		: MM_CardCleaner()
		, _markingScheme(markingScheme)
	{
		_typeId = __FUNCTION__;
	}

private:
};

#endif /* CARDCLEANERFORMARKING_HPP_ */
