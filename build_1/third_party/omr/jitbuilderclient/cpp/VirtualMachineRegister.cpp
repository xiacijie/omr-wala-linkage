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

extern "C" void VirtualMachineRegisterCallback_Commit(void * clientObj, void * b) {
    VirtualMachineRegister * client = static_cast<VirtualMachineRegister *>(clientObj);
    return client->Commit(static_cast<IlBuilder *>(b));
}

extern "C" void VirtualMachineRegisterCallback_Reload(void * clientObj, void * b) {
    VirtualMachineRegister * client = static_cast<VirtualMachineRegister *>(clientObj);
    return client->Reload(static_cast<IlBuilder *>(b));
}

extern "C" VirtualMachineState * VirtualMachineRegisterCallback_MakeCopy(void * clientObj) {
    VirtualMachineRegister * client = static_cast<VirtualMachineRegister *>(clientObj);
    return client->MakeCopy();
}

extern "C" void * getImpl_VirtualMachineRegister(void * client) {
    return static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(static_cast<VirtualMachineRegister *>(client)->_impl));
}

VirtualMachineRegister::VirtualMachineRegister(IlBuilder * b, const char * localName, IlType * pointerToRegisterType, uint32_t adjustByStep, IlValue * addressOfRegister): VirtualMachineState((void *)NULL) {
    auto * impl = ::new TR::VirtualMachineRegister(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL), localName, static_cast<TR::IlType *>(pointerToRegisterType != NULL ? pointerToRegisterType->_impl : NULL), adjustByStep, static_cast<TR::IlValue *>(addressOfRegister != NULL ? addressOfRegister->_impl : NULL));
    static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::VirtualMachineState *>(impl)));
}

VirtualMachineRegister::VirtualMachineRegister(void * impl): VirtualMachineState((void *)NULL) {
    if (impl != NULL) {
        static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(impl))->setClient(this);
        initializeFromImpl(static_cast<void *>(static_cast<TR::VirtualMachineState *>(static_cast<TR::VirtualMachineRegister *>(impl))));
    }
}

void VirtualMachineRegister::initializeFromImpl(void * impl) {
    VirtualMachineState::initializeFromImpl(impl);
    static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_Commit(reinterpret_cast<void*>(&VirtualMachineRegisterCallback_Commit));
    static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_Reload(reinterpret_cast<void*>(&VirtualMachineRegisterCallback_Reload));
    static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_MakeCopy(reinterpret_cast<void*>(&VirtualMachineRegisterCallback_MakeCopy));
    static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(_impl))->setGetImpl(&getImpl_VirtualMachineRegister);
}

VirtualMachineRegister::~VirtualMachineRegister() {}

void VirtualMachineRegister::Adjust(IlBuilder * b, IlValue * amount) {
    static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(_impl))->Adjust(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL), static_cast<TR::IlValue *>(amount != NULL ? amount->_impl : NULL));
}

void VirtualMachineRegister::Adjust(IlBuilder * b, size_t amount) {
    static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(_impl))->Adjust(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL), amount);
}

IlValue * VirtualMachineRegister::Load(IlBuilder * b) {
    TR::IlValue * implRet = static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(_impl))->Load(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

void VirtualMachineRegister::Store(IlBuilder * b, IlValue * value) {
    static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(_impl))->Store(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL), static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
}

void VirtualMachineRegister::Commit(IlBuilder * b) {
    static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(_impl))->Commit(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

void VirtualMachineRegister::Reload(IlBuilder * b) {
    static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(_impl))->Reload(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

VirtualMachineState * VirtualMachineRegister::MakeCopy() {
    TR::VirtualMachineState * implRet = static_cast<TR::VirtualMachineRegister *>(static_cast<TR::VirtualMachineState *>(_impl))->MakeCopy();
    GET_CLIENT_OBJECT(clientObj, VirtualMachineState, implRet);
    return clientObj;
}

extern "C" void * allocateVirtualMachineRegister(void * impl) {
    return new VirtualMachineRegister(impl);
}

} // JitBuilder
} // OMR
