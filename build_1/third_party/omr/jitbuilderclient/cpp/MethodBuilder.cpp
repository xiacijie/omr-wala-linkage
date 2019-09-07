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

extern "C" bool MethodBuilderCallback_RequestFunction(void * clientObj, const char * name) {
    MethodBuilder * client = static_cast<MethodBuilder *>(clientObj);
    return client->RequestFunction(name);
}

extern "C" void * getImpl_MethodBuilder(void * client) {
    return static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(static_cast<MethodBuilder *>(client)->_impl));
}

MethodBuilder::MethodBuilder(TypeDictionary * dict): IlBuilder((void *)NULL) {
    auto * impl = ::new TR::MethodBuilder(static_cast<TR::TypeDictionary *>(dict != NULL ? dict->_impl : NULL));
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::IlBuilder *>(impl)));
}
MethodBuilder::MethodBuilder(TypeDictionary * dict, VirtualMachineState * vmState): IlBuilder((void *)NULL) {
    auto * impl = ::new TR::MethodBuilder(static_cast<TR::TypeDictionary *>(dict != NULL ? dict->_impl : NULL), static_cast<TR::VirtualMachineState *>(vmState != NULL ? vmState->_impl : NULL));
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::IlBuilder *>(impl)));
}
MethodBuilder::MethodBuilder(MethodBuilder * callerMB): IlBuilder((void *)NULL) {
    auto * impl = ::new TR::MethodBuilder(static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(callerMB != NULL ? callerMB->_impl : NULL)));
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::IlBuilder *>(impl)));
}
MethodBuilder::MethodBuilder(MethodBuilder * callerMB, VirtualMachineState * vmState): IlBuilder((void *)NULL) {
    auto * impl = ::new TR::MethodBuilder(static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(callerMB != NULL ? callerMB->_impl : NULL)), static_cast<TR::VirtualMachineState *>(vmState != NULL ? vmState->_impl : NULL));
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(impl))->setClient(this);
    initializeFromImpl(static_cast<void *>(static_cast<TR::IlBuilder *>(impl)));
}

MethodBuilder::MethodBuilder(void * impl): IlBuilder((void *)NULL) {
    if (impl != NULL) {
        static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(impl))->setClient(this);
        initializeFromImpl(static_cast<void *>(static_cast<TR::IlBuilder *>(static_cast<TR::MethodBuilder *>(impl))));
    }
}

void MethodBuilder::initializeFromImpl(void * impl) {
    IlBuilder::initializeFromImpl(impl);
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->setClientCallback_RequestFunction(reinterpret_cast<void*>(&MethodBuilderCallback_RequestFunction));
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->setGetImpl(&getImpl_MethodBuilder);
}

MethodBuilder::~MethodBuilder() {}

void MethodBuilder::AllLocalsHaveBeenDefined() {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->AllLocalsHaveBeenDefined();
}

void MethodBuilder::AppendBuilder(IlBuilder * b) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->AppendBuilder(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

void MethodBuilder::AppendBuilder(BytecodeBuilder * b) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->AppendBuilder(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL)));
}

void MethodBuilder::AppendBytecodeBuilder(BytecodeBuilder * b) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->AppendBytecodeBuilder(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL)));
}

void MethodBuilder::DefineFile(const char * fileName) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->DefineFile(fileName);
}

void MethodBuilder::DefineLine(const char * line) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->DefineLine(line);
}

void MethodBuilder::DefineLine(int32_t line) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->DefineLine(line);
}

void MethodBuilder::DefineName(const char * name) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->DefineName(name);
}

void MethodBuilder::DefineParameter(const char * name, IlType * type) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->DefineParameter(name, static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL));
}

void MethodBuilder::DefineArrayParameter(const char * name, IlType * type) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->DefineArrayParameter(name, static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL));
}

void MethodBuilder::DefineReturnType(IlType * type) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->DefineReturnType(static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL));
}

void MethodBuilder::DefineLocal(const char * name, IlType * type) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->DefineLocal(name, static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL));
}

void MethodBuilder::DefineMemory(const char * name, IlType * type, void * location) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->DefineMemory(name, static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL), location);
}

void MethodBuilder::DefineFunction(const char * name, const char * fileName, const char * lineNumber, void * entryPoint, IlType * returnType, int32_t numParms, IlType ** parmTypes) {
    ARRAY_ARG_SETUP(IlType, numParms, parmTypesArg, parmTypes);
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->DefineFunction(name, fileName, lineNumber, entryPoint, static_cast<TR::IlType *>(returnType != NULL ? returnType->_impl : NULL), numParms, parmTypesArg);
    ARRAY_ARG_RETURN(IlType, numParms, parmTypesArg, parmTypes);
}

void MethodBuilder::DefineFunction(const char * name, const char * fileName, const char * lineNumber, void * entryPoint, IlType * returnType, int32_t numParms, ...) {
    IlType ** parmTypes = new IlType *[numParms];
    va_list vararg;
    va_start(vararg, numParms);
    for (int i = 0; i < numParms; ++i) { parmTypes[i] = va_arg(vararg, IlType *); }
    va_end(vararg);
    DefineFunction(name, fileName, lineNumber, entryPoint, returnType, numParms, parmTypes);
    delete[] parmTypes;
}

const char * MethodBuilder::GetMethodName() {
    auto ret = static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->GetMethodName();
    return ret;
}

int32_t MethodBuilder::GetNextBytecodeFromWorklist() {
    auto ret = static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->GetNextBytecodeFromWorklist();
    return ret;
}

void MethodBuilder::setVMState(VirtualMachineState * vmState) {
    static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->setVMState(static_cast<TR::VirtualMachineState *>(vmState != NULL ? vmState->_impl : NULL));
}

bool MethodBuilder::RequestFunction(const char * name) {
    auto ret = static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(_impl))->RequestFunction(name);
    return ret;
}

extern "C" void * allocateMethodBuilder(void * impl) {
    return new MethodBuilder(impl);
}

} // JitBuilder
} // OMR
