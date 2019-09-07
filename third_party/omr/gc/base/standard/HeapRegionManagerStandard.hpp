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

#if !defined(HEAPREGIONMANAGERSTANDARD_HPP_)
#define HEAPREGIONMANAGERSTANDARD_HPP_

#include "omrcfg.h"

#include "Base.hpp"
#include "EnvironmentBase.hpp"
#include "Heap.hpp"
#include "HeapRegionDescriptor.hpp"
#include "HeapRegionManager.hpp"
#include "HeapMemorySnapshot.hpp"

class MM_HeapRegionManagerStandard : public MM_HeapRegionManager
{
public:
protected:
private:
	void *_lowHeapAddress; /**< the first (lowest address) byte of heap which is addressable by the table */
	void *_highHeapAddress; /**< the first byte AFTER the heap range which is addressable by the table */

public:
	MMINLINE static MM_HeapRegionManagerStandard *getHeapRegionManager(MM_Heap *heap) { return (MM_HeapRegionManagerStandard *)heap->getHeapRegionManager(); }
	MMINLINE static MM_HeapRegionManagerStandard *getHeapRegionManager(MM_HeapRegionManager *manager) { return (MM_HeapRegionManagerStandard *)manager; }

	static MM_HeapRegionManagerStandard *newInstance(MM_EnvironmentBase *env, uintptr_t regionSize, uintptr_t tableDescriptorSize, MM_RegionDescriptorInitializer regionDescriptorInitializer, MM_RegionDescriptorDestructor regionDescriptorDestructor);

	MM_HeapRegionManagerStandard(MM_EnvironmentBase *env, uintptr_t regionSize, uintptr_t tableDescriptorSize, MM_RegionDescriptorInitializer regionDescriptorInitializer, MM_RegionDescriptorDestructor regionDescriptorDestructor);

	/**
	 * Called as soon as the bounds of the contiguous heap are known (in the case of split heaps, this would also include the "gap").
	 * Calls to this method have the side-effect of allocating internal data structures to manage the regions backing this contiguous heap
	 * so a boolean return value is provided to inform the caller if these internal data structures were successfully initialized.
	 *
	 * The is expected to be called exactly once on each HRM.
	 *
	 * @param env The environment
	 * @param lowHeapEdge the lowest byte addressable in the contiguous heap (note that this might not be presently committed)
	 * @param highHeapEdge the byte after the highest byte addressable in the contiguous heap
	 * @return true if this manager succeeded in initializing internal data structures to manage this heap or false if an error occurred (this is
	 * generally fatal)
	 */
	virtual bool setContiguousHeapRange(MM_EnvironmentBase *env, void *lowHeapEdge, void *highHeapEdge);

	 /**
	  * Provide destruction of Region Table if necessary
	  * Use in heap shutdown (correspondent call with setContiguousHeapRange)
	  * @param env The environment
	  */
	 virtual void destroyRegionTable(MM_EnvironmentBase *env);

	/**
	 * @see MM_HeapRegionManager::enableRegionsInTable
	 */
	virtual bool enableRegionsInTable(MM_EnvironmentBase *env, MM_MemoryHandle *handle);

	virtual MM_HeapMemorySnapshot* getHeapMemorySnapshot(MM_GCExtensionsBase *extensions, MM_HeapMemorySnapshot* snapshot, bool gcEnd);

protected:
	virtual bool initialize(MM_EnvironmentBase *env);
	virtual void tearDown(MM_EnvironmentBase *env);

private:
};


#endif /* HEAPREGIONMANAGERSTANDARD_HPP_ */
