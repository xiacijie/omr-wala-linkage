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

extern "C" void VirtualMachineRegisterInStructCallback_Commit(void * clientObj, void * b) {
    VirtualMachineRegisterInStruct * client = static_cast<VirtualMachineRegisterInStruct *>(clientObj);
    return client->Commit(static_cast<IlBuilder *>(b));
}

extern "C" void VirtualMachineRegisterInStructCallback_Reload(void * clientObj, void * b) {
    VirtualMachineRegisterInStruct * client = static_cast<VirtualMachineRegisterInStruct *>(clientObj);
    return client->Reload(static_cast<IlBuilder *>(b));
}

extern "C" VirtualMachineState * VirtualMachineRegisterInStructCallback_MakeCopy(void * clientObj) {
    VirtualMachineRegisterInStruct * client = static_cast<VirtualMachineRegisterInStruct *>(clientObj);
    return client->MakeCopy();
}

extern "C" void * getImpl_VirtualMachineRegisterInStruct(void * client) {
    return static_cast<TR::VirtualMachineRegisterInStruct *>(static_cast<TR::VirtualMachineState *>(static_cast<VirtualMachineRegisterInStruct *>(client)->_impl));
}

VirtualMachineRegisterInStruct::VirtualMachineRegisterInStruct(IlBuilder * b, const char * structName, const char * localNameHoldingStructAddress, const char * fieldName, const char * localName): VirtualMachineRegister((void *)NULL) {
    auto * impl = ::new TR::VirtualMachineRegisterInStruct(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL), structName, localNameHoldingStructAddress, fieldName, localName);
    static_cast<TR::VirtualMachineRegisterInStruct *>(static_cast<TR::VirtualMachineState *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::VirtualMachineState *>(impl)));
}

VirtualMachineRegisterInStruct::VirtualMachineRegisterInStruct(void * impl): VirtualMachineRegister((void *)NULL) {
    if (impl != NULL) {
        static_cast<TR::VirtualMachineRegisterInStruct *>(static_cast<TR::VirtualMachineState *>(impl))->setClient(this);
        initializeFromImpl(static_cast<void *>(static_cast<TR::VirtualMachineState *>(static_cast<TR::VirtualMachineRegisterInStruct *>(impl))));
    }
}

void VirtualMachineRegisterInStruct::initializeFromImpl(void * impl) {
    VirtualMachineRegister::initializeFromImpl(impl);
    static_cast<TR::VirtualMachineRegisterInStruct *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_Commit(reinterpret_cast<void*>(&VirtualMachineRegisterInStructCallback_Commit));
    static_cast<TR::VirtualMachineRegisterInStruct *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_Reload(reinterpret_cast<void*>(&VirtualMachineRegisterInStructCallback_Reload));
    static_cast<TR::VirtualMachineRegisterInStruct *>(static_cast<TR::VirtualMachineState *>(_impl))->setClientCallback_MakeCopy(reinterpret_cast<void*>(&VirtualMachineRegisterInStructCallback_MakeCopy));
    static_cast<TR::VirtualMachineRegisterInStruct *>(static_cast<TR::VirtualMachineState *>(_impl))->setGetImpl(&getImpl_VirtualMachineRegisterInStruct);
}

VirtualMachineRegisterInStruct::~VirtualMachineRegisterInStruct() {}

void VirtualMachineRegisterInStruct::Commit(IlBuilder * b) {
    static_cast<TR::VirtualMachineRegisterInStruct *>(static_cast<TR::VirtualMachineState *>(_impl))->Commit(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

void VirtualMachineRegisterInStruct::Reload(IlBuilder * b) {
    static_cast<TR::VirtualMachineRegisterInStruct *>(static_cast<TR::VirtualMachineState *>(_impl))->Reload(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

VirtualMachineState * VirtualMachineRegisterInStruct::MakeCopy() {
    TR::VirtualMachineState * implRet = static_cast<TR::VirtualMachineRegisterInStruct *>(static_cast<TR::VirtualMachineState *>(_impl))->MakeCopy();
    GET_CLIENT_OBJECT(clientObj, VirtualMachineState, implRet);
    return clientObj;
}

extern "C" void * allocateVirtualMachineRegisterInStruct(void * impl) {
    return new VirtualMachineRegisterInStruct(impl);
}

} // JitBuilder
} // OMR
