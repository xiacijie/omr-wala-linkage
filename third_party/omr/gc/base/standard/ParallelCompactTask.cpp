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

#include "omrcfg.h"
#include "omrmodroncore.h"
#include "modronopt.h"

#if defined(OMR_GC_MODRON_COMPACTION)

#include "CompactScheme.hpp"
#include "EnvironmentBase.hpp"
#include "GCExtensionsBase.hpp"
#include "GlobalGCStats.hpp"

#include "ParallelCompactTask.hpp"

uintptr_t
MM_ParallelCompactTask::getVMStateID()
{
	return OMRVMSTATE_GC_COMPACT;
}

void
MM_ParallelCompactTask::run(MM_EnvironmentBase *env)
{
	_compactScheme->compact(env, _rebuildMarkBits, _aggressive);
}

void
MM_ParallelCompactTask::setup(MM_EnvironmentBase *env)
{
	env->_compactStats.clear();
}

void
MM_ParallelCompactTask::cleanup(MM_EnvironmentBase *env)
{
	MM_GlobalGCStats *finalGCStats;

	finalGCStats = &MM_GCExtensionsBase::getExtensions(env->getOmrVM())->globalGCStats;
	finalGCStats->compactStats.merge(&env->_compactStats);
}

#endif /* OMR_GC_MODRON_COMPACTION */


