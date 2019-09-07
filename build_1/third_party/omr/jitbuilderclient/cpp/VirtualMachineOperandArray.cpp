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

extern "C" void VirtualMachineOperandArrayCallback_Commit(void * clientObj, void * b) {
    VirtualMachineOperandArray * client = static_cast<VirtualMachineOperandArray *>(clientObj);
    return client->Commit(static_cast<IlBuilder *>(b));
}

extern "C" void VirtualMachineOperandArrayCallback_Reload(void * clientObj, void * b) {
    VirtualMachineOperandArray * client = static_cast<VirtualMachineOperandArray *>(clientObj);
    return client->Reload(static_cast<IlBuilder *>(b));
}

extern "C" VirtualMachineState * VirtualMachineOperandArrayCallback_MakeCopy(void * clientObj) {
    VirtualMachineOperandArray * client = static_cast<VirtualMachineOperandArray *>(clientObj);
    return client->MakeCopy();
}

extern "C" void VirtualMachineOperandArrayCallback_MergeInto(void * clientObj, void * vmState, void * b) {
    VirtualMachineOperandArray * client = static_cast<VirtualMachineOperandArray *>(clientObj);
    return client->MergeInto(static_cast<VirtualMachineState *>(vmState), static_cast<IlBuilder *>(b));
}

extern "C" void * getImpl_VirtualMachineOperandArray(void * client) {
    return static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(static_cast<VirtualMachineOperandArray *>(client)->_impl));
}

VirtualMachineOperandArray::VirtualMachineOperandArray(MethodBuilder * mb, int32_t numOfElements, IlType * elementType, VirtualMachineRegister * arrayBase): VirtualMachineState((void *)NULL) {
    auto * impl = ::new TR::VirtualMachineOperandArray(static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(mb != NULL ? mb->_impl : NULL)), numOfElements, static_cast<TR::IlType *>(elementType != NULL ? elementType->_impl : NULL), static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(arrayBase != NULL ? arrayBase->_impl : NULL)));
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::VirtualMachineState *>(impl)));
}
VirtualMachineOperandArray::VirtualMachineOperandArray(VirtualMachineOperandArray * other): VirtualMachineState((void *)NULL) {
    auto * impl = ::new TR::VirtualMachineOperandArray(static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(other != NULL ? other->_impl : NULL)));
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::VirtualMachineState *>(impl)));
}

VirtualMachineOperandArray::VirtualMachineOperandArray(void * impl): VirtualMachineState((void *)NULL) {
    if (impl != NULL) {
        static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(impl))->setClient(this);
        initializeFromImpl(static_cast<void *>(static_cast<TR::VirtualMachineState *>(static_cast<TR::VirtualMachineOperandArray *>(impl))));
    }
}

void VirtualMachineOperandArray::initializeFromImpl(void * impl) {
    VirtualMachineState::initializeFromImpl(impl);
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_Commit(reinterpret_cast<void*>(&VirtualMachineOperandArrayCallback_Commit));
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_Reload(reinterpret_cast<void*>(&VirtualMachineOperandArrayCallback_Reload));
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_MakeCopy(reinterpret_cast<void*>(&VirtualMachineOperandArrayCallback_MakeCopy));
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_MergeInto(reinterpret_cast<void*>(&VirtualMachineOperandArrayCallback_MergeInto));
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->setGetImpl(&getImpl_VirtualMachineOperandArray);
}

VirtualMachineOperandArray::~VirtualMachineOperandArray() {}

IlValue * VirtualMachineOperandArray::Get(int32_t index) {
    TR::IlValue * implRet = static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->Get(index);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

void VirtualMachineOperandArray::Move(IlBuilder * b, int32_t dstIndex, int32_t srcIndex) {
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->Move(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL), dstIndex, srcIndex);
}

void VirtualMachineOperandArray::Set(int32_t index, IlValue * value) {
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->Set(index, static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
}

void VirtualMachineOperandArray::UpdateArray(IlBuilder * b, IlValue * array) {
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->UpdateArray(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL), static_cast<TR::IlValue *>(array != NULL ? array->_impl : NULL));
}

void VirtualMachineOperandArray::Commit(IlBuilder * b) {
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->Commit(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

void VirtualMachineOperandArray::Reload(IlBuilder * b) {
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->Reload(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

VirtualMachineState * VirtualMachineOperandArray::MakeCopy() {
    TR::VirtualMachineState * implRet = static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->MakeCopy();
    GET_CLIENT_OBJECT(clientObj, VirtualMachineState, implRet);
    return clientObj;
}

void VirtualMachineOperandArray::MergeInto(VirtualMachineState * vmState, IlBuilder * b) {
    static_cast<TR::VirtualMachineOperandArray *>(static_cast<TR::VirtualMachineState *>(_impl))->MergeInto(static_cast<TR::VirtualMachineState *>(vmState != NULL ? vmState->_impl : NULL), static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

extern "C" void * allocateVirtualMachineOperandArray(void * impl) {
    return new VirtualMachineOperandArray(impl);
}

} // JitBuilder
} // OMR
