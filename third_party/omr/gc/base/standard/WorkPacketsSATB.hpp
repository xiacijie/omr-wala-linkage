
/*******************************************************************************
 * Copyright (c) 2018, 2018 IBM Corp. and others
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

#if !defined(WORKPACKETSSATB_HPP_)
#define WORKPACKETSSATB_HPP_

#if defined(OMR_GC_REALTIME)

#include "EnvironmentBase.hpp"
#include "WorkPackets.hpp"

class MM_IncrementalOverflow;

class MM_WorkPacketsSATB : public MM_WorkPackets
{
protected:
	MM_PacketList _inUseBarrierPacketList;  /**< List for packets currently being used for the remembered set*/

public:
	static MM_WorkPacketsSATB *newInstance(MM_EnvironmentBase *env);
	
	virtual bool initialize(MM_EnvironmentBase *env);
	virtual void tearDown(MM_EnvironmentBase *env);
	
	MM_IncrementalOverflow *getIncrementalOverflowHandler() const { return (MM_IncrementalOverflow*)_overflowHandler; }
	

	MMINLINE bool inUsePacketsAvailable(MM_EnvironmentBase *env) { return !_inUseBarrierPacketList.isEmpty();}

	virtual MM_Packet *getBarrierPacket(MM_EnvironmentBase *env);
	virtual void putInUsePacket(MM_EnvironmentBase *env, MM_Packet *packet);
	virtual void removePacketFromInUseList(MM_EnvironmentBase *env, MM_Packet *packet);
	virtual void putFullPacket(MM_EnvironmentBase *env, MM_Packet *packet);

	void moveInUseToNonEmpty(MM_EnvironmentBase *env);

	/**
	 * Create a MM_WorkPacketsRealtime object.
	 */
	MM_WorkPacketsSATB(MM_EnvironmentBase *env) :
		MM_WorkPackets(env)
		, _inUseBarrierPacketList(NULL)
	{
		_typeId = __FUNCTION__;
	};

protected:
	virtual MM_WorkPacketOverflow *createOverflowHandler(MM_EnvironmentBase *env, MM_WorkPackets *workPackets);
	virtual MM_Packet *getPacketByOverflowing(MM_EnvironmentBase *env);
	virtual float getHeapCapacityFactor(MM_EnvironmentBase *env);
	virtual MM_Packet *getInputPacketFromOverflow(MM_EnvironmentBase *env);

private:
};
#endif /* OMR_GC_REALTIME */
#endif /* WORKPACKETSSATB_HPP_ */

