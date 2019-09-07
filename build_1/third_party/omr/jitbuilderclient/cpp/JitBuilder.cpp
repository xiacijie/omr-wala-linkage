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

extern bool internal_initializeJit();
extern bool internal_initializeJitWithOptions(char * options);
extern int32_t internal_compileMethodBuilder(TR::MethodBuilder * methodBuilder, void ** entryPoint);
extern void internal_shutdownJit();

static void setAllocators() {
    TR::BytecodeBuilder::setClientAllocator(OMR::JitBuilder::allocateBytecodeBuilder);
    TR::IlBuilder::JBCase::setClientAllocator(OMR::JitBuilder::allocateIlBuilderJBCase);
    TR::IlBuilder::JBCondition::setClientAllocator(OMR::JitBuilder::allocateIlBuilderJBCondition);
    TR::IlBuilder::setClientAllocator(OMR::JitBuilder::allocateIlBuilder);
    TR::MethodBuilder::setClientAllocator(OMR::JitBuilder::allocateMethodBuilder);
    TR::IlType::setClientAllocator(OMR::JitBuilder::allocateIlType);
    TR::IlValue::setClientAllocator(OMR::JitBuilder::allocateIlValue);
    TR::ThunkBuilder::setClientAllocator(OMR::JitBuilder::allocateThunkBuilder);
    TR::TypeDictionary::setClientAllocator(OMR::JitBuilder::allocateTypeDictionary);
    TR::VirtualMachineOperandArray::setClientAllocator(OMR::JitBuilder::allocateVirtualMachineOperandArray);
    TR::VirtualMachineOperandStack::setClientAllocator(OMR::JitBuilder::allocateVirtualMachineOperandStack);
    TR::VirtualMachineRegister::setClientAllocator(OMR::JitBuilder::allocateVirtualMachineRegister);
    TR::VirtualMachineRegisterInStruct::setClientAllocator(OMR::JitBuilder::allocateVirtualMachineRegisterInStruct);
    TR::VirtualMachineState::setClientAllocator(OMR::JitBuilder::allocateVirtualMachineState);
}

bool initializeJit() {
    setAllocators();
    auto ret = internal_initializeJit();
    return ret;
}

bool initializeJitWithOptions(char * options) {
    setAllocators();
    auto ret = internal_initializeJitWithOptions(options);
    return ret;
}

int32_t compileMethodBuilder(OMR::JitBuilder::MethodBuilder * methodBuilder, void ** entryPoint) {
    auto ret = internal_compileMethodBuilder(static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(methodBuilder != NULL ? methodBuilder->_impl : NULL)), entryPoint);
    return ret;
}

void shutdownJit() {
    internal_shutdownJit();
}

