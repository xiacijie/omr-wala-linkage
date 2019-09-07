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

extern "C" void * getImpl_ThunkBuilder(void * client) {
    return static_cast<TR::ThunkBuilder *>(static_cast<TR::IlBuilder *>(static_cast<ThunkBuilder *>(client)->_impl));
}

ThunkBuilder::ThunkBuilder(TypeDictionary * dict, const char * name, IlType * returnType, uint32_t numCalleeParms, IlType ** calleeParms): MethodBuilder((void *)NULL) {
    ARRAY_ARG_SETUP(IlType, numCalleeParms, calleeParmsArg, calleeParms);
    auto * impl = ::new TR::ThunkBuilder(static_cast<TR::TypeDictionary *>(dict != NULL ? dict->_impl : NULL), name, static_cast<TR::IlType *>(returnType != NULL ? returnType->_impl : NULL), numCalleeParms, calleeParmsArg);
    ARRAY_ARG_RETURN(IlType, numCalleeParms, calleeParmsArg, calleeParms);
    static_cast<TR::ThunkBuilder *>(static_cast<TR::IlBuilder *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::IlBuilder *>(impl)));
}

ThunkBuilder::ThunkBuilder(void * impl): MethodBuilder((void *)NULL) {
    if (impl != NULL) {
        static_cast<TR::ThunkBuilder *>(static_cast<TR::IlBuilder *>(impl))->setClient(this);
        initializeFromImpl(static_cast<void *>(static_cast<TR::IlBuilder *>(static_cast<TR::ThunkBuilder *>(impl))));
    }
}

void ThunkBuilder::initializeFromImpl(void * impl) {
    MethodBuilder::initializeFromImpl(impl);
    static_cast<TR::ThunkBuilder *>(static_cast<TR::IlBuilder *>(_impl))->setGetImpl(&getImpl_ThunkBuilder);
}

ThunkBuilder::~ThunkBuilder() {}

extern "C" void * allocateThunkBuilder(void * impl) {
    return new ThunkBuilder(impl);
}

} // JitBuilder
} // OMR
