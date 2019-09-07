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

extern "C" void VirtualMachineOperandStackCallback_Commit(void * clientObj, void * b) {
    VirtualMachineOperandStack * client = static_cast<VirtualMachineOperandStack *>(clientObj);
    return client->Commit(static_cast<IlBuilder *>(b));
}

extern "C" void VirtualMachineOperandStackCallback_Reload(void * clientObj, void * b) {
    VirtualMachineOperandStack * client = static_cast<VirtualMachineOperandStack *>(clientObj);
    return client->Reload(static_cast<IlBuilder *>(b));
}

extern "C" VirtualMachineState * VirtualMachineOperandStackCallback_MakeCopy(void * clientObj) {
    VirtualMachineOperandStack * client = static_cast<VirtualMachineOperandStack *>(clientObj);
    return client->MakeCopy();
}

extern "C" void VirtualMachineOperandStackCallback_MergeInto(void * clientObj, void * vmState, void * b) {
    VirtualMachineOperandStack * client = static_cast<VirtualMachineOperandStack *>(clientObj);
    return client->MergeInto(static_cast<VirtualMachineState *>(vmState), static_cast<IlBuilder *>(b));
}

extern "C" void * getImpl_VirtualMachineOperandStack(void * client) {
    return static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(static_cast<VirtualMachineOperandStack *>(client)->_impl));
}

VirtualMachineOperandStack::VirtualMachineOperandStack(MethodBuilder * mb, int32_t sizeHint, IlType * elementType, VirtualMachineRegister * stackTopRegister): VirtualMachineState((void *)NULL) {
    auto * impl = ::new TR::VirtualMachineOperandStack(static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(mb != NULL ? mb->_impl : NULL)), sizeHint, static_cast<TR::IlType *>(elementType != NULL ? elementType->_impl : NULL), static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(stackTopRegister != NULL ? stackTopRegister->_impl : NULL)));
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::VirtualMachineState *>(impl)));
}
VirtualMachineOperandStack::VirtualMachineOperandStack(MethodBuilder * mb, int32_t sizeHint, IlType * elementType, VirtualMachineRegister * stackTopRegister, bool growsUp): VirtualMachineState((void *)NULL) {
    auto * impl = ::new TR::VirtualMachineOperandStack(static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(mb != NULL ? mb->_impl : NULL)), sizeHint, static_cast<TR::IlType *>(elementType != NULL ? elementType->_impl : NULL), static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(stackTopRegister != NULL ? stackTopRegister->_impl : NULL)), growsUp);
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::VirtualMachineState *>(impl)));
}
VirtualMachineOperandStack::VirtualMachineOperandStack(MethodBuilder * mb, int32_t sizeHint, IlType * elementType, VirtualMachineRegister * stackTopRegister, bool growsUp, int32_t stackInitialOffset): VirtualMachineState((void *)NULL) {
    auto * impl = ::new TR::VirtualMachineOperandStack(static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(mb != NULL ? mb->_impl : NULL)), sizeHint, static_cast<TR::IlType *>(elementType != NULL ? elementType->_impl : NULL), static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(stackTopRegister != NULL ? stackTopRegister->_impl : NULL)), growsUp, stackInitialOffset);
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::VirtualMachineState *>(impl)));
}

VirtualMachineOperandStack::VirtualMachineOperandStack(void * impl): VirtualMachineState((void *)NULL) {
    if (impl != NULL) {
        static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(impl))->setClient(this);
        initializeFromImpl(static_cast<void *>(static_cast<TR::VirtualMachineState *>(static_cast<TR::VirtualMachineOperandStack *>(impl))));
    }
}

void VirtualMachineOperandStack::initializeFromImpl(void * impl) {
    VirtualMachineState::initializeFromImpl(impl);
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_Commit(reinterpret_cast<void*>(&VirtualMachineOperandStackCallback_Commit));
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_Reload(reinterpret_cast<void*>(&VirtualMachineOperandStackCallback_Reload));
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_MakeCopy(reinterpret_cast<void*>(&VirtualMachineOperandStackCallback_MakeCopy));
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_MergeInto(reinterpret_cast<void*>(&VirtualMachineOperandStackCallback_MergeInto));
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->setGetImpl(&getImpl_VirtualMachineOperandStack);
}

VirtualMachineOperandStack::~VirtualMachineOperandStack() {}

void VirtualMachineOperandStack::Drop(IlBuilder * b, int32_t depth) {
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->Drop(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL), depth);
}

void VirtualMachineOperandStack::Dup(IlBuilder * b) {
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->Dup(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

IlValue * VirtualMachineOperandStack::Pick(int32_t depth) {
    TR::IlValue * implRet = static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->Pick(depth);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * VirtualMachineOperandStack::Pop(IlBuilder * b) {
    TR::IlValue * implRet = static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->Pop(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

void VirtualMachineOperandStack::Push(IlBuilder * b, IlValue * value) {
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->Push(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL), static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
}

IlValue * VirtualMachineOperandStack::Top() {
    TR::IlValue * implRet = static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->Top();
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

void VirtualMachineOperandStack::UpdateStack(IlBuilder * b, IlValue * array) {
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->UpdateStack(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL), static_cast<TR::IlValue *>(array != NULL ? array->_impl : NULL));
}

void VirtualMachineOperandStack::Commit(IlBuilder * b) {
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->Commit(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

void VirtualMachineOperandStack::Reload(IlBuilder * b) {
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->Reload(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

VirtualMachineState * VirtualMachineOperandStack::MakeCopy() {
    TR::VirtualMachineState * implRet = static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->MakeCopy();
    GET_CLIENT_OBJECT(clientObj, VirtualMachineState, implRet);
    return clientObj;
}

void VirtualMachineOperandStack::MergeInto(VirtualMachineState * vmState, IlBuilder * b) {
    static_cast<TR::VirtualMachineOperandStack *>(static_cast<TR::VirtualMachineState *>(_impl))->MergeInto(static_cast<TR::VirtualMachineState *>(vmState != NULL ? vmState->_impl : NULL), static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

extern "C" void * allocateVirtualMachineOperandStack(void * impl) {
    return new VirtualMachineOperandStack(impl);
}

} // JitBuilder
} // OMR
