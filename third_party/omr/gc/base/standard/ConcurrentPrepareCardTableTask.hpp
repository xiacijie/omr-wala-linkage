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

/**
 * @file
 * @ingroup GC_Modron_Standard
 */

#if !defined(CONCURRENTPREPARECARDTABLETASK_HPP_)
#define CONCURRENTPREPARECARDTABLETASK_HPP_

#include "omrcfg.h"
#include "omrmodroncore.h"

#include "ParallelTask.hpp"
#include "ConcurrentCardTableForWC.hpp"

class MM_Dispatcher;
class MM_EnvironmentBase;

/**
 * Task used to prepare the card-table in parallel on weakly-ordered platforms.
 * @ingroup GC_Modron_Standard
 */
class MM_ConcurrentPrepareCardTableTask : public MM_ParallelTask
{
private:
	MM_ConcurrentCardTableForWC *_cardTable;
	Card *_firstCard;
	Card *_lastCard;
	CardAction _action;

public:
	virtual UDATA getVMStateID() { return OMRVMSTATE_GC_CONCURRENT_MARK_PREPARE_CARD_TABLE; }
	
	virtual void run(MM_EnvironmentBase *env);

	MM_ConcurrentPrepareCardTableTask(MM_EnvironmentBase *env, MM_Dispatcher *dispatcher, MM_ConcurrentCardTableForWC *cardTable, Card *firstCard, Card *lastCard, CardAction action) :
		MM_ParallelTask(env, dispatcher),
		_cardTable(cardTable),
		_firstCard(firstCard),
		_lastCard(lastCard),
		_action(action)
	{
		_typeId = __FUNCTION__;
	}
};

#endif /* CONCURRENTPREPARECARDTABLETASK_HPP_ */
