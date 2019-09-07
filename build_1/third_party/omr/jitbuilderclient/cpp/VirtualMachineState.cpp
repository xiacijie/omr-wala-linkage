/*******************************************************************************
 * Copyright (c) 2019, 2019 IBM Corp. and others
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
        
#include "ilgen/BytecodeBuilder.hpp"
#include "ilgen/IlBuilder.hpp"
#include "ilgen/MethodBuilder.hpp"
#include "ilgen/IlType.hpp"
#include "ilgen/IlValue.hpp"
#include "ilgen/ThunkBuilder.hpp"
#include "ilgen/TypeDictionary.hpp"
#include "ilgen/VirtualMachineOperandArray.hpp"
#include "ilgen/VirtualMachineOperandStack.hpp"
#include "ilgen/VirtualMachineRegister.hpp"
#include "ilgen/VirtualMachineRegisterInStruct.hpp"
#include "ilgen/VirtualMachineState.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/Macros.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/BytecodeBuilder.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/IlBuilder.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/MethodBuilder.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/IlType.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/IlValue.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/ThunkBuilder.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/TypeDictionary.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/VirtualMachineOperandArray.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/VirtualMachineOperandStack.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/VirtualMachineRegister.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/VirtualMachineRegisterInStruct.hpp"
#include "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/release/cpp/include/VirtualMachineState.hpp"

namespace OMR {
namespace JitBuilder {

extern "C" void VirtualMachineStateCallback_Commit(void * clientObj, void * b) {
    VirtualMachineState * client = static_cast<VirtualMachineState *>(clientObj);
    return client->Commit(static_cast<IlBuilder *>(b));
}

extern "C" void VirtualMachineStateCallback_Reload(void * clientObj, void * b) {
    VirtualMachineState * client = static_cast<VirtualMachineState *>(clientObj);
    return client->Reload(static_cast<IlBuilder *>(b));
}

extern "C" VirtualMachineState * VirtualMachineStateCallback_MakeCopy(void * clientObj) {
    VirtualMachineState * client = static_cast<VirtualMachineState *>(clientObj);
    return client->MakeCopy();
}

extern "C" void VirtualMachineStateCallback_MergeInto(void * clientObj, void * vmState, void * b) {
    VirtualMachineState * client = static_cast<VirtualMachineState *>(clientObj);
    return client->MergeInto(static_cast<VirtualMachineState *>(vmState), static_cast<IlBuilder *>(b));
}

extern "C" void * getImpl_VirtualMachineState(void * client) {
    return static_cast<TR::VirtualMachineState *>(static_cast<VirtualMachineState *>(client)->_impl);
}

VirtualMachineState::VirtualMachineState() {
    auto * impl = ::new TR::VirtualMachineState();
    static_cast<TR::VirtualMachineState *>(impl)->setClient(this);
    initializeFromImpl(static_cast<void *>(impl));
}

VirtualMachineState::VirtualMachineState(void * impl) {
    if (impl != NULL) {
        static_cast<TR::VirtualMachineState *>(impl)->setClient(this);
        initializeFromImpl(impl);
    }
}

void VirtualMachineState::initializeFromImpl(void * impl) {
    _impl = impl;
    static_cast<TR::VirtualMachineState *>(_impl)->setClientCallback_Commit(reinterpret_cast<void*>(&VirtualMachineStateCallback_Commit));
    static_cast<TR::VirtualMachineState *>(_impl)->setClientCallback_Reload(reinterpret_cast<void*>(&VirtualMachineStateCallback_Reload));
    static_cast<TR::VirtualMachineState *>(_impl)->setClientCallback_MakeCopy(reinterpret_cast<void*>(&VirtualMachineStateCallback_MakeCopy));
    static_cast<TR::VirtualMachineState *>(_impl)->setClientCallback_MergeInto(reinterpret_cast<void*>(&VirtualMachineStateCallback_MergeInto));
    static_cast<TR::VirtualMachineState *>(_impl)->setGetImpl(&getImpl_VirtualMachineState);
}

VirtualMachineState::~VirtualMachineState() {}

void VirtualMachineState::Commit(IlBuilder * b) {
    static_cast<TR::VirtualMachineState *>(_impl)->Commit(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

void VirtualMachineState::Reload(IlBuilder * b) {
    static_cast<TR::VirtualMachineState *>(_impl)->Reload(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

VirtualMachineState * VirtualMachineState::MakeCopy() {
    TR::VirtualMachineState * implRet = static_cast<TR::VirtualMachineState *>(_impl)->MakeCopy();
    GET_CLIENT_OBJECT(clientObj, VirtualMachineState, implRet);
    return clientObj;
}

void VirtualMachineState::MergeInto(VirtualMachineState * vmState, IlBuilder * b) {
    static_cast<TR::VirtualMachineState *>(_impl)->MergeInto(static_cast<TR::VirtualMachineState *>(vmState != NULL ? vmState->_impl : NULL), static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

extern "C" void * allocateVirtualMachineState(void * impl) {
    return new VirtualMachineState(impl);
}

} // JitBuilder
} // OMR
