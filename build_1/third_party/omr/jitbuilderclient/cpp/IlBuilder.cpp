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

extern "C" void * getImpl_JBCase(void * client) {
    return static_cast<TR::IlBuilder::JBCase *>(static_cast<IlBuilder::JBCase *>(client)->_impl);
}

IlBuilder::JBCase::JBCase(int32_t caseValue, IlBuilder * caseBuilder, int32_t caseFallsThrough) {
    auto * impl = ::new TR::IlBuilder::JBCase(caseValue, static_cast<TR::IlBuilder *>(caseBuilder != NULL ? caseBuilder->_impl : NULL), caseFallsThrough);
    static_cast<TR::IlBuilder::JBCase *>(impl)->setClient(this);
    initializeFromImpl(static_cast<void *>(impl));
}

IlBuilder::JBCase::JBCase(void * impl) {
    if (impl != NULL) {
        static_cast<TR::IlBuilder::JBCase *>(impl)->setClient(this);
        initializeFromImpl(impl);
    }
}

void IlBuilder::JBCase::initializeFromImpl(void * impl) {
    _impl = impl;
    static_cast<TR::IlBuilder::JBCase *>(_impl)->setGetImpl(&getImpl_JBCase);
}

IlBuilder::JBCase::~JBCase() {}

extern "C" void * allocateIlBuilderJBCase(void * impl) {
    return new IlBuilder::JBCase(impl);
}

extern "C" void * getImpl_JBCondition(void * client) {
    return static_cast<TR::IlBuilder::JBCondition *>(static_cast<IlBuilder::JBCondition *>(client)->_impl);
}

IlBuilder::JBCondition::JBCondition(IlBuilder * conditionBuilder, IlValue * conditionValue) {
    auto * impl = ::new TR::IlBuilder::JBCondition(static_cast<TR::IlBuilder *>(conditionBuilder != NULL ? conditionBuilder->_impl : NULL), static_cast<TR::IlValue *>(conditionValue != NULL ? conditionValue->_impl : NULL));
    static_cast<TR::IlBuilder::JBCondition *>(impl)->setClient(this);
    initializeFromImpl(static_cast<void *>(impl));
}

IlBuilder::JBCondition::JBCondition(void * impl) {
    if (impl != NULL) {
        static_cast<TR::IlBuilder::JBCondition *>(impl)->setClient(this);
        initializeFromImpl(impl);
    }
}

void IlBuilder::JBCondition::initializeFromImpl(void * impl) {
    _impl = impl;
    static_cast<TR::IlBuilder::JBCondition *>(_impl)->setGetImpl(&getImpl_JBCondition);
}

IlBuilder::JBCondition::~JBCondition() {}

extern "C" void * allocateIlBuilderJBCondition(void * impl) {
    return new IlBuilder::JBCondition(impl);
}

extern "C" bool IlBuilderCallback_buildIL(void * clientObj) {
    IlBuilder * client = static_cast<IlBuilder *>(clientObj);
    return client->buildIL();
}

extern "C" void * getImpl_IlBuilder(void * client) {
    return static_cast<TR::IlBuilder *>(static_cast<IlBuilder *>(client)->_impl);
}


IlBuilder::IlBuilder(void * impl) {
    if (impl != NULL) {
        static_cast<TR::IlBuilder *>(impl)->setClient(this);
        initializeFromImpl(impl);
    }
}

void IlBuilder::initializeFromImpl(void * impl) {
    _impl = impl;
    GET_CLIENT_OBJECT(clientObj_NoType, IlType, static_cast<TR::IlBuilder *>(_impl)->NoType);
    NoType = clientObj_NoType;
    GET_CLIENT_OBJECT(clientObj_Int8, IlType, static_cast<TR::IlBuilder *>(_impl)->Int8);
    Int8 = clientObj_Int8;
    GET_CLIENT_OBJECT(clientObj_Int16, IlType, static_cast<TR::IlBuilder *>(_impl)->Int16);
    Int16 = clientObj_Int16;
    GET_CLIENT_OBJECT(clientObj_Int32, IlType, static_cast<TR::IlBuilder *>(_impl)->Int32);
    Int32 = clientObj_Int32;
    GET_CLIENT_OBJECT(clientObj_Int64, IlType, static_cast<TR::IlBuilder *>(_impl)->Int64);
    Int64 = clientObj_Int64;
    GET_CLIENT_OBJECT(clientObj_Float, IlType, static_cast<TR::IlBuilder *>(_impl)->Float);
    Float = clientObj_Float;
    GET_CLIENT_OBJECT(clientObj_Double, IlType, static_cast<TR::IlBuilder *>(_impl)->Double);
    Double = clientObj_Double;
    GET_CLIENT_OBJECT(clientObj_Address, IlType, static_cast<TR::IlBuilder *>(_impl)->Address);
    Address = clientObj_Address;
    GET_CLIENT_OBJECT(clientObj_VectorInt8, IlType, static_cast<TR::IlBuilder *>(_impl)->VectorInt8);
    VectorInt8 = clientObj_VectorInt8;
    GET_CLIENT_OBJECT(clientObj_VectorInt16, IlType, static_cast<TR::IlBuilder *>(_impl)->VectorInt16);
    VectorInt16 = clientObj_VectorInt16;
    GET_CLIENT_OBJECT(clientObj_VectorInt32, IlType, static_cast<TR::IlBuilder *>(_impl)->VectorInt32);
    VectorInt32 = clientObj_VectorInt32;
    GET_CLIENT_OBJECT(clientObj_VectorInt64, IlType, static_cast<TR::IlBuilder *>(_impl)->VectorInt64);
    VectorInt64 = clientObj_VectorInt64;
    GET_CLIENT_OBJECT(clientObj_VectorFloat, IlType, static_cast<TR::IlBuilder *>(_impl)->VectorFloat);
    VectorFloat = clientObj_VectorFloat;
    GET_CLIENT_OBJECT(clientObj_VectorDouble, IlType, static_cast<TR::IlBuilder *>(_impl)->VectorDouble);
    VectorDouble = clientObj_VectorDouble;
    GET_CLIENT_OBJECT(clientObj_Word, IlType, static_cast<TR::IlBuilder *>(_impl)->Word);
    Word = clientObj_Word;
    static_cast<TR::IlBuilder *>(_impl)->setClientCallback_buildIL(reinterpret_cast<void*>(&IlBuilderCallback_buildIL));
    static_cast<TR::IlBuilder *>(_impl)->setGetImpl(&getImpl_IlBuilder);
}

IlBuilder::~IlBuilder() {}

IlBuilder * IlBuilder::OrphanBuilder() {
    TR::IlBuilder * implRet = static_cast<TR::IlBuilder *>(_impl)->OrphanBuilder();
    GET_CLIENT_OBJECT(clientObj, IlBuilder, implRet);
    return clientObj;
}

BytecodeBuilder * IlBuilder::OrphanBytecodeBuilder(int32_t bcIndex, char * name) {
    TR::BytecodeBuilder * implRet = static_cast<TR::IlBuilder *>(_impl)->OrphanBytecodeBuilder(bcIndex, name);
    GET_CLIENT_OBJECT(clientObj, BytecodeBuilder, implRet);
    return clientObj;
}

IlValue * IlBuilder::Copy(IlValue * value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Copy(static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

TypeDictionary * IlBuilder::typeDictionary() {
    TR::TypeDictionary * implRet = static_cast<TR::IlBuilder *>(_impl)->typeDictionary();
    GET_CLIENT_OBJECT(clientObj, TypeDictionary, implRet);
    return clientObj;
}

IlValue * IlBuilder::ConstInteger(IlType * type, int64_t value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ConstInteger(static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL), value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ConstAddress(void * value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ConstAddress(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ConstDouble(double value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ConstDouble(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ConstFloat(float value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ConstFloat(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ConstInt8(int8_t value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ConstInt8(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ConstInt16(int16_t value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ConstInt16(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ConstInt32(int32_t value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ConstInt32(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ConstInt64(int64_t value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ConstInt64(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ConstString(char * value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ConstString(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Const(void * value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Const(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Const(double value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Const(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Const(float value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Const(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Const(int8_t value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Const(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Const(int16_t value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Const(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Const(int32_t value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Const(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Const(int64_t value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Const(value);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::NullAddress() {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->NullAddress();
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Add(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Add(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::AddWithOverflow(IlBuilder ** overflowHandler, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, overflowHandlerImpl, overflowHandlerArg, overflowHandler);
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->AddWithOverflow(overflowHandlerArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, overflowHandlerImpl, overflowHandler);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::AddWithUnsignedOverflow(IlBuilder ** overflowHandler, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, overflowHandlerImpl, overflowHandlerArg, overflowHandler);
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->AddWithUnsignedOverflow(overflowHandlerArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, overflowHandlerImpl, overflowHandler);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::And(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->And(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Div(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Div(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::UnsignedDiv(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->UnsignedDiv(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::IndexAt(IlType * dt, IlValue * base, IlValue * index) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->IndexAt(static_cast<TR::IlType *>(dt != NULL ? dt->_impl : NULL), static_cast<TR::IlValue *>(base != NULL ? base->_impl : NULL), static_cast<TR::IlValue *>(index != NULL ? index->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Mul(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Mul(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::MulWithOverflow(IlBuilder ** overflowHandler, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, overflowHandlerImpl, overflowHandlerArg, overflowHandler);
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->MulWithOverflow(overflowHandlerArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, overflowHandlerImpl, overflowHandler);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Negate(IlValue * v) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Negate(static_cast<TR::IlValue *>(v != NULL ? v->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Or(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Or(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Rem(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Rem(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::UnsignedRem(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->UnsignedRem(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ShiftL(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ShiftL(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ShiftR(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ShiftR(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Sub(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Sub(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::SubWithOverflow(IlBuilder ** overflowHandler, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, overflowHandlerImpl, overflowHandlerArg, overflowHandler);
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->SubWithOverflow(overflowHandlerArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, overflowHandlerImpl, overflowHandler);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::SubWithUnsignedOverflow(IlBuilder ** overflowHandler, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, overflowHandlerImpl, overflowHandlerArg, overflowHandler);
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->SubWithUnsignedOverflow(overflowHandlerArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, overflowHandlerImpl, overflowHandler);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::UnsignedShiftR(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->UnsignedShiftR(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Xor(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Xor(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::EqualTo(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->EqualTo(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::LessOrEqualTo(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->LessOrEqualTo(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::LessThan(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->LessThan(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::GreaterOrEqualTo(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->GreaterOrEqualTo(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::GreaterThan(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->GreaterThan(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::NotEqualTo(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->NotEqualTo(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::UnsignedLessOrEqualTo(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->UnsignedLessOrEqualTo(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::UnsignedLessThan(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->UnsignedLessThan(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::UnsignedGreaterOrEqualTo(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->UnsignedGreaterOrEqualTo(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::UnsignedGreaterThan(IlValue * left, IlValue * right) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->UnsignedGreaterThan(static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ConvertBitsTo(IlType * type, IlValue * value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ConvertBitsTo(static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL), static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ConvertTo(IlType * type, IlValue * value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ConvertTo(static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL), static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::UnsignedConvertTo(IlType * type, IlValue * value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->UnsignedConvertTo(static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL), static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::AtomicAdd(IlValue * baseAddress, IlValue * value) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->AtomicAdd(static_cast<TR::IlValue *>(baseAddress != NULL ? baseAddress->_impl : NULL), static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::CreateLocalArray(int32_t numElements, IlType * elementType) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->CreateLocalArray(numElements, static_cast<TR::IlType *>(elementType != NULL ? elementType->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::CreateLocalStruct(IlType * structType) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->CreateLocalStruct(static_cast<TR::IlType *>(structType != NULL ? structType->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Load(const char * name) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Load(name);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::LoadAt(IlType * type, IlValue * address) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->LoadAt(static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL), static_cast<TR::IlValue *>(address != NULL ? address->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::LoadIndirect(const char * type, const char * field, IlValue * object) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->LoadIndirect(type, field, static_cast<TR::IlValue *>(object != NULL ? object->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

void IlBuilder::Store(const char * name, IlValue * value) {
    static_cast<TR::IlBuilder *>(_impl)->Store(name, static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
}

void IlBuilder::StoreAt(IlValue * address, IlValue * value) {
    static_cast<TR::IlBuilder *>(_impl)->StoreAt(static_cast<TR::IlValue *>(address != NULL ? address->_impl : NULL), static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
}

void IlBuilder::StoreIndirect(const char * type, const char * field, IlValue * object, IlValue * value) {
    static_cast<TR::IlBuilder *>(_impl)->StoreIndirect(type, field, static_cast<TR::IlValue *>(object != NULL ? object->_impl : NULL), static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
}

void IlBuilder::StoreOver(IlValue * dest, IlValue * value) {
    static_cast<TR::IlBuilder *>(_impl)->StoreOver(static_cast<TR::IlValue *>(dest != NULL ? dest->_impl : NULL), static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
}

void IlBuilder::Transaction(IlBuilder ** persistentFailureBuilder, IlBuilder ** transientFailureBuilder, IlBuilder ** transactionBuilder) {
    ARG_SETUP(IlBuilder, persistentFailureBuilderImpl, persistentFailureBuilderArg, persistentFailureBuilder);
    ARG_SETUP(IlBuilder, transientFailureBuilderImpl, transientFailureBuilderArg, transientFailureBuilder);
    ARG_SETUP(IlBuilder, transactionBuilderImpl, transactionBuilderArg, transactionBuilder);
    static_cast<TR::IlBuilder *>(_impl)->Transaction(persistentFailureBuilderArg, transientFailureBuilderArg, transactionBuilderArg);
    ARG_RETURN(IlBuilder, persistentFailureBuilderImpl, persistentFailureBuilder);
    ARG_RETURN(IlBuilder, transientFailureBuilderImpl, transientFailureBuilder);
    ARG_RETURN(IlBuilder, transactionBuilderImpl, transactionBuilder);
}

void IlBuilder::TransactionAbort() {
    static_cast<TR::IlBuilder *>(_impl)->TransactionAbort();
}

IlValue * IlBuilder::StructFieldInstanceAddress(const char * structName, const char * fieldName, IlValue * obj) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->StructFieldInstanceAddress(structName, fieldName, static_cast<TR::IlValue *>(obj != NULL ? obj->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::UnionFieldInstanceAddress(const char * unionName, const char * fieldName, IlValue * obj) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->UnionFieldInstanceAddress(unionName, fieldName, static_cast<TR::IlValue *>(obj != NULL ? obj->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::VectorLoad(char * name) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->VectorLoad(name);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::VectorLoadAt(IlType * type, IlValue * address) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->VectorLoadAt(static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL), static_cast<TR::IlValue *>(address != NULL ? address->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

void IlBuilder::VectorStore(char * name, IlValue * value) {
    static_cast<TR::IlBuilder *>(_impl)->VectorStore(name, static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
}

void IlBuilder::VectorStoreAt(IlValue * address, IlValue * value) {
    static_cast<TR::IlBuilder *>(_impl)->VectorStoreAt(static_cast<TR::IlValue *>(address != NULL ? address->_impl : NULL), static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
}

void IlBuilder::AppendBuilder(IlBuilder * b) {
    static_cast<TR::IlBuilder *>(_impl)->AppendBuilder(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

IlValue * IlBuilder::Call(const char * name, int32_t numArgs, IlValue ** arguments) {
    ARRAY_ARG_SETUP(IlValue, numArgs, argumentsArg, arguments);
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Call(name, numArgs, argumentsArg);
    ARRAY_ARG_RETURN(IlValue, numArgs, argumentsArg, arguments);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Call(const char * name, int32_t numArgs, ...) {
    IlValue ** arguments = new IlValue *[numArgs];
    va_list vararg;
    va_start(vararg, numArgs);
    for (int i = 0; i < numArgs; ++i) { arguments[i] = va_arg(vararg, IlValue *); }
    va_end(vararg);
    IlValue * ret = Call(name, numArgs, arguments);
    delete[] arguments;
    return ret;
}

IlValue * IlBuilder::Call(MethodBuilder * name, int32_t numArgs, IlValue ** arguments) {
    ARRAY_ARG_SETUP(IlValue, numArgs, argumentsArg, arguments);
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Call(static_cast<TR::MethodBuilder *>(static_cast<TR::IlBuilder *>(name != NULL ? name->_impl : NULL)), numArgs, argumentsArg);
    ARRAY_ARG_RETURN(IlValue, numArgs, argumentsArg, arguments);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::Call(MethodBuilder * name, int32_t numArgs, ...) {
    IlValue ** arguments = new IlValue *[numArgs];
    va_list vararg;
    va_start(vararg, numArgs);
    for (int i = 0; i < numArgs; ++i) { arguments[i] = va_arg(vararg, IlValue *); }
    va_end(vararg);
    IlValue * ret = Call(name, numArgs, arguments);
    delete[] arguments;
    return ret;
}

IlValue * IlBuilder::ComputedCall(char * name, int32_t numArgs, IlValue ** arguments) {
    ARRAY_ARG_SETUP(IlValue, numArgs, argumentsArg, arguments);
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->ComputedCall(name, numArgs, argumentsArg);
    ARRAY_ARG_RETURN(IlValue, numArgs, argumentsArg, arguments);
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

IlValue * IlBuilder::ComputedCall(char * name, int32_t numArgs, ...) {
    IlValue ** arguments = new IlValue *[numArgs];
    va_list vararg;
    va_start(vararg, numArgs);
    for (int i = 0; i < numArgs; ++i) { arguments[i] = va_arg(vararg, IlValue *); }
    va_end(vararg);
    IlValue * ret = ComputedCall(name, numArgs, arguments);
    delete[] arguments;
    return ret;
}

void IlBuilder::DoWhileLoop(char * exitCondition, IlBuilder ** body) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    static_cast<TR::IlBuilder *>(_impl)->DoWhileLoop(exitCondition, bodyArg);
    ARG_RETURN(IlBuilder, bodyImpl, body);
}

void IlBuilder::DoWhileLoop(char * exitCondition, IlBuilder ** body, IlBuilder ** breakBuilder, IlBuilder ** continueBuilder) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    ARG_SETUP(IlBuilder, breakBuilderImpl, breakBuilderArg, breakBuilder);
    ARG_SETUP(IlBuilder, continueBuilderImpl, continueBuilderArg, continueBuilder);
    static_cast<TR::IlBuilder *>(_impl)->DoWhileLoop(exitCondition, bodyArg, breakBuilderArg, continueBuilderArg);
    ARG_RETURN(IlBuilder, bodyImpl, body);
    ARG_RETURN(IlBuilder, breakBuilderImpl, breakBuilder);
    ARG_RETURN(IlBuilder, continueBuilderImpl, continueBuilder);
}

void IlBuilder::DoWhileLoopWithBreak(char * exitCondition, IlBuilder ** body, IlBuilder ** breakBuilder) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    ARG_SETUP(IlBuilder, breakBuilderImpl, breakBuilderArg, breakBuilder);
    static_cast<TR::IlBuilder *>(_impl)->DoWhileLoopWithBreak(exitCondition, bodyArg, breakBuilderArg);
    ARG_RETURN(IlBuilder, bodyImpl, body);
    ARG_RETURN(IlBuilder, breakBuilderImpl, breakBuilder);
}

void IlBuilder::DoWhileLoopWithContinue(char * exitCondition, IlBuilder ** body, IlBuilder ** continueBuilder) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    ARG_SETUP(IlBuilder, continueBuilderImpl, continueBuilderArg, continueBuilder);
    static_cast<TR::IlBuilder *>(_impl)->DoWhileLoopWithContinue(exitCondition, bodyArg, continueBuilderArg);
    ARG_RETURN(IlBuilder, bodyImpl, body);
    ARG_RETURN(IlBuilder, continueBuilderImpl, continueBuilder);
}

void IlBuilder::Goto(IlBuilder * b) {
    static_cast<TR::IlBuilder *>(_impl)->Goto(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL));
}

void IlBuilder::Goto(IlBuilder ** b) {
    ARG_SETUP(IlBuilder, bImpl, bArg, b);
    static_cast<TR::IlBuilder *>(_impl)->Goto(bArg);
    ARG_RETURN(IlBuilder, bImpl, b);
}

IlBuilder::JBCondition * IlBuilder::MakeCondition(IlBuilder * conditionBuilder, IlValue * conditionValue) {
    TR::IlBuilder::JBCondition * implRet = static_cast<TR::IlBuilder *>(_impl)->MakeCondition(static_cast<TR::IlBuilder *>(conditionBuilder != NULL ? conditionBuilder->_impl : NULL), static_cast<TR::IlValue *>(conditionValue != NULL ? conditionValue->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, JBCondition, implRet);
    return clientObj;
}

void IlBuilder::IfAnd(IlBuilder ** allTrueBuilder, IlBuilder ** anyFalseBuilder, int32_t numTerms, IlBuilder::JBCondition ** terms) {
    ARG_SETUP(IlBuilder, allTrueBuilderImpl, allTrueBuilderArg, allTrueBuilder);
    ARG_SETUP(IlBuilder, anyFalseBuilderImpl, anyFalseBuilderArg, anyFalseBuilder);
    ARRAY_ARG_SETUP(IlBuilder::JBCondition, numTerms, termsArg, terms);
    static_cast<TR::IlBuilder *>(_impl)->IfAnd(allTrueBuilderArg, anyFalseBuilderArg, numTerms, termsArg);
    ARG_RETURN(IlBuilder, allTrueBuilderImpl, allTrueBuilder);
    ARG_RETURN(IlBuilder, anyFalseBuilderImpl, anyFalseBuilder);
    ARRAY_ARG_RETURN(IlBuilder::JBCondition, numTerms, termsArg, terms);
}

void IlBuilder::IfAnd(IlBuilder ** allTrueBuilder, IlBuilder ** anyFalseBuilder, int32_t numTerms, ...) {
    IlBuilder::JBCondition ** terms = new IlBuilder::JBCondition *[numTerms];
    va_list vararg;
    va_start(vararg, numTerms);
    for (int i = 0; i < numTerms; ++i) { terms[i] = va_arg(vararg, IlBuilder::JBCondition *); }
    va_end(vararg);
    IfAnd(allTrueBuilder, anyFalseBuilder, numTerms, terms);
    delete[] terms;
}

void IlBuilder::IfCmpEqual(IlBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpEqual(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void IlBuilder::IfCmpEqual(IlBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfCmpLessOrEqual(IlBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpLessOrEqual(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void IlBuilder::IfCmpLessOrEqual(IlBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpLessOrEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfCmpLessThan(IlBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpLessThan(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void IlBuilder::IfCmpLessThan(IlBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpLessThan(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfCmpGreaterOrEqual(IlBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpGreaterOrEqual(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void IlBuilder::IfCmpGreaterOrEqual(IlBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpGreaterOrEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfCmpGreaterThan(IlBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpGreaterThan(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void IlBuilder::IfCmpGreaterThan(IlBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpGreaterThan(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfCmpNotEqual(IlBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpNotEqual(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void IlBuilder::IfCmpNotEqual(IlBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpNotEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfCmpUnsignedLessOrEqual(IlBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpUnsignedLessOrEqual(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void IlBuilder::IfCmpUnsignedLessOrEqual(IlBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpUnsignedLessOrEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfCmpUnsignedLessThan(IlBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpUnsignedLessThan(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void IlBuilder::IfCmpUnsignedLessThan(IlBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpUnsignedLessThan(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfCmpUnsignedGreaterOrEqual(IlBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpUnsignedGreaterOrEqual(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void IlBuilder::IfCmpUnsignedGreaterOrEqual(IlBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpUnsignedGreaterOrEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfCmpUnsignedGreaterThan(IlBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpUnsignedGreaterThan(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void IlBuilder::IfCmpUnsignedGreaterThan(IlBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpUnsignedGreaterThan(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfCmpEqualZero(IlBuilder * target, IlValue * condition) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpEqualZero(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(condition != NULL ? condition->_impl : NULL));
}

void IlBuilder::IfCmpEqualZero(IlBuilder ** target, IlValue * condition) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpEqualZero(targetArg, static_cast<TR::IlValue *>(condition != NULL ? condition->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfCmpNotEqualZero(IlBuilder * target, IlValue * condition) {
    static_cast<TR::IlBuilder *>(_impl)->IfCmpNotEqualZero(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL), static_cast<TR::IlValue *>(condition != NULL ? condition->_impl : NULL));
}

void IlBuilder::IfCmpNotEqualZero(IlBuilder ** target, IlValue * condition) {
    ARG_SETUP(IlBuilder, targetImpl, targetArg, target);
    static_cast<TR::IlBuilder *>(_impl)->IfCmpNotEqualZero(targetArg, static_cast<TR::IlValue *>(condition != NULL ? condition->_impl : NULL));
    ARG_RETURN(IlBuilder, targetImpl, target);
}

void IlBuilder::IfOr(IlBuilder ** anyTrueBuilder, IlBuilder ** allFalseBuilder, int32_t numTerms, IlBuilder::JBCondition ** terms) {
    ARG_SETUP(IlBuilder, anyTrueBuilderImpl, anyTrueBuilderArg, anyTrueBuilder);
    ARG_SETUP(IlBuilder, allFalseBuilderImpl, allFalseBuilderArg, allFalseBuilder);
    ARRAY_ARG_SETUP(IlBuilder::JBCondition, numTerms, termsArg, terms);
    static_cast<TR::IlBuilder *>(_impl)->IfOr(anyTrueBuilderArg, allFalseBuilderArg, numTerms, termsArg);
    ARG_RETURN(IlBuilder, anyTrueBuilderImpl, anyTrueBuilder);
    ARG_RETURN(IlBuilder, allFalseBuilderImpl, allFalseBuilder);
    ARRAY_ARG_RETURN(IlBuilder::JBCondition, numTerms, termsArg, terms);
}

void IlBuilder::IfOr(IlBuilder ** anyTrueBuilder, IlBuilder ** allFalseBuilder, int32_t numTerms, ...) {
    IlBuilder::JBCondition ** terms = new IlBuilder::JBCondition *[numTerms];
    va_list vararg;
    va_start(vararg, numTerms);
    for (int i = 0; i < numTerms; ++i) { terms[i] = va_arg(vararg, IlBuilder::JBCondition *); }
    va_end(vararg);
    IfOr(anyTrueBuilder, allFalseBuilder, numTerms, terms);
    delete[] terms;
}

void IlBuilder::IfThen(IlBuilder ** thenPath, IlValue * condition) {
    ARG_SETUP(IlBuilder, thenPathImpl, thenPathArg, thenPath);
    static_cast<TR::IlBuilder *>(_impl)->IfThen(thenPathArg, static_cast<TR::IlValue *>(condition != NULL ? condition->_impl : NULL));
    ARG_RETURN(IlBuilder, thenPathImpl, thenPath);
}

void IlBuilder::IfThenElse(IlBuilder ** thenPath, IlBuilder ** elsePath, IlValue * condition) {
    ARG_SETUP(IlBuilder, thenPathImpl, thenPathArg, thenPath);
    ARG_SETUP(IlBuilder, elsePathImpl, elsePathArg, elsePath);
    static_cast<TR::IlBuilder *>(_impl)->IfThenElse(thenPathArg, elsePathArg, static_cast<TR::IlValue *>(condition != NULL ? condition->_impl : NULL));
    ARG_RETURN(IlBuilder, thenPathImpl, thenPath);
    ARG_RETURN(IlBuilder, elsePathImpl, elsePath);
}

IlValue * IlBuilder::Select(IlValue * condition, IlValue * trueValue, IlValue * falseValue) {
    TR::IlValue * implRet = static_cast<TR::IlBuilder *>(_impl)->Select(static_cast<TR::IlValue *>(condition != NULL ? condition->_impl : NULL), static_cast<TR::IlValue *>(trueValue != NULL ? trueValue->_impl : NULL), static_cast<TR::IlValue *>(falseValue != NULL ? falseValue->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlValue, implRet);
    return clientObj;
}

void IlBuilder::ForLoop(bool countsUp, char * indVar, IlBuilder ** body, IlBuilder ** breakBuilder, IlBuilder ** continueBuilder, IlValue * initial, IlValue * iterateWhile, IlValue * increment) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    ARG_SETUP(IlBuilder, breakBuilderImpl, breakBuilderArg, breakBuilder);
    ARG_SETUP(IlBuilder, continueBuilderImpl, continueBuilderArg, continueBuilder);
    static_cast<TR::IlBuilder *>(_impl)->ForLoop(countsUp, indVar, bodyArg, breakBuilderArg, continueBuilderArg, static_cast<TR::IlValue *>(initial != NULL ? initial->_impl : NULL), static_cast<TR::IlValue *>(iterateWhile != NULL ? iterateWhile->_impl : NULL), static_cast<TR::IlValue *>(increment != NULL ? increment->_impl : NULL));
    ARG_RETURN(IlBuilder, bodyImpl, body);
    ARG_RETURN(IlBuilder, breakBuilderImpl, breakBuilder);
    ARG_RETURN(IlBuilder, continueBuilderImpl, continueBuilder);
}

void IlBuilder::ForLoopDown(char * indVar, IlBuilder ** body, IlValue * initial, IlValue * iterateWhile, IlValue * increment) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    static_cast<TR::IlBuilder *>(_impl)->ForLoopDown(indVar, bodyArg, static_cast<TR::IlValue *>(initial != NULL ? initial->_impl : NULL), static_cast<TR::IlValue *>(iterateWhile != NULL ? iterateWhile->_impl : NULL), static_cast<TR::IlValue *>(increment != NULL ? increment->_impl : NULL));
    ARG_RETURN(IlBuilder, bodyImpl, body);
}

void IlBuilder::ForLoopUp(char * indVar, IlBuilder ** body, IlValue * initial, IlValue * iterateWhile, IlValue * increment) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    static_cast<TR::IlBuilder *>(_impl)->ForLoopUp(indVar, bodyArg, static_cast<TR::IlValue *>(initial != NULL ? initial->_impl : NULL), static_cast<TR::IlValue *>(iterateWhile != NULL ? iterateWhile->_impl : NULL), static_cast<TR::IlValue *>(increment != NULL ? increment->_impl : NULL));
    ARG_RETURN(IlBuilder, bodyImpl, body);
}

void IlBuilder::ForLoopWithBreak(bool countsUp, char * indVar, IlBuilder ** body, IlBuilder ** breakBuilder, IlValue * initial, IlValue * iterateWhile, IlValue * increment) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    ARG_SETUP(IlBuilder, breakBuilderImpl, breakBuilderArg, breakBuilder);
    static_cast<TR::IlBuilder *>(_impl)->ForLoopWithBreak(countsUp, indVar, bodyArg, breakBuilderArg, static_cast<TR::IlValue *>(initial != NULL ? initial->_impl : NULL), static_cast<TR::IlValue *>(iterateWhile != NULL ? iterateWhile->_impl : NULL), static_cast<TR::IlValue *>(increment != NULL ? increment->_impl : NULL));
    ARG_RETURN(IlBuilder, bodyImpl, body);
    ARG_RETURN(IlBuilder, breakBuilderImpl, breakBuilder);
}

void IlBuilder::ForLoopWithContinue(bool countsUp, char * indVar, IlBuilder ** body, IlBuilder ** continueBuilder, IlValue * initial, IlValue * iterateWhile, IlValue * increment) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    ARG_SETUP(IlBuilder, continueBuilderImpl, continueBuilderArg, continueBuilder);
    static_cast<TR::IlBuilder *>(_impl)->ForLoopWithContinue(countsUp, indVar, bodyArg, continueBuilderArg, static_cast<TR::IlValue *>(initial != NULL ? initial->_impl : NULL), static_cast<TR::IlValue *>(iterateWhile != NULL ? iterateWhile->_impl : NULL), static_cast<TR::IlValue *>(increment != NULL ? increment->_impl : NULL));
    ARG_RETURN(IlBuilder, bodyImpl, body);
    ARG_RETURN(IlBuilder, continueBuilderImpl, continueBuilder);
}

void IlBuilder::Return() {
    static_cast<TR::IlBuilder *>(_impl)->Return();
}

void IlBuilder::Return(IlValue * value) {
    static_cast<TR::IlBuilder *>(_impl)->Return(static_cast<TR::IlValue *>(value != NULL ? value->_impl : NULL));
}

void IlBuilder::Switch(const char * selectionVar, IlBuilder ** defaultBuilder, int32_t numCases, IlBuilder::JBCase ** cases) {
    ARG_SETUP(IlBuilder, defaultBuilderImpl, defaultBuilderArg, defaultBuilder);
    ARRAY_ARG_SETUP(IlBuilder::JBCase, numCases, casesArg, cases);
    static_cast<TR::IlBuilder *>(_impl)->Switch(selectionVar, defaultBuilderArg, numCases, casesArg);
    ARG_RETURN(IlBuilder, defaultBuilderImpl, defaultBuilder);
    ARRAY_ARG_RETURN(IlBuilder::JBCase, numCases, casesArg, cases);
}

void IlBuilder::Switch(const char * selectionVar, IlBuilder ** defaultBuilder, int32_t numCases, ...) {
    IlBuilder::JBCase ** cases = new IlBuilder::JBCase *[numCases];
    va_list vararg;
    va_start(vararg, numCases);
    for (int i = 0; i < numCases; ++i) { cases[i] = va_arg(vararg, IlBuilder::JBCase *); }
    va_end(vararg);
    Switch(selectionVar, defaultBuilder, numCases, cases);
    delete[] cases;
}

void IlBuilder::TableSwitch(const char * selectionVar, IlBuilder ** defaultBuilder, bool generateBoundsCheck, int32_t numCases, IlBuilder::JBCase ** cases) {
    ARG_SETUP(IlBuilder, defaultBuilderImpl, defaultBuilderArg, defaultBuilder);
    ARRAY_ARG_SETUP(IlBuilder::JBCase, numCases, casesArg, cases);
    static_cast<TR::IlBuilder *>(_impl)->TableSwitch(selectionVar, defaultBuilderArg, generateBoundsCheck, numCases, casesArg);
    ARG_RETURN(IlBuilder, defaultBuilderImpl, defaultBuilder);
    ARRAY_ARG_RETURN(IlBuilder::JBCase, numCases, casesArg, cases);
}

void IlBuilder::TableSwitch(const char * selectionVar, IlBuilder ** defaultBuilder, bool generateBoundsCheck, int32_t numCases, ...) {
    IlBuilder::JBCase ** cases = new IlBuilder::JBCase *[numCases];
    va_list vararg;
    va_start(vararg, numCases);
    for (int i = 0; i < numCases; ++i) { cases[i] = va_arg(vararg, IlBuilder::JBCase *); }
    va_end(vararg);
    TableSwitch(selectionVar, defaultBuilder, generateBoundsCheck, numCases, cases);
    delete[] cases;
}

IlBuilder::JBCase * IlBuilder::MakeCase(int32_t value, IlBuilder ** builder, int32_t fallsThrough) {
    ARG_SETUP(IlBuilder, builderImpl, builderArg, builder);
    TR::IlBuilder::JBCase * implRet = static_cast<TR::IlBuilder *>(_impl)->MakeCase(value, builderArg, fallsThrough);
    ARG_RETURN(IlBuilder, builderImpl, builder);
    GET_CLIENT_OBJECT(clientObj, JBCase, implRet);
    return clientObj;
}

void IlBuilder::WhileDoLoop(char * exitCondition, IlBuilder ** body) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    static_cast<TR::IlBuilder *>(_impl)->WhileDoLoop(exitCondition, bodyArg);
    ARG_RETURN(IlBuilder, bodyImpl, body);
}

void IlBuilder::WhileDoLoopWithBreak(char * exitCondition, IlBuilder ** body, IlBuilder ** breakBuilder) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    ARG_SETUP(IlBuilder, breakBuilderImpl, breakBuilderArg, breakBuilder);
    static_cast<TR::IlBuilder *>(_impl)->WhileDoLoopWithBreak(exitCondition, bodyArg, breakBuilderArg);
    ARG_RETURN(IlBuilder, bodyImpl, body);
    ARG_RETURN(IlBuilder, breakBuilderImpl, breakBuilder);
}

void IlBuilder::WhileDoLoopWithContinue(char * exitCondition, IlBuilder ** body, IlBuilder ** continueBuilder) {
    ARG_SETUP(IlBuilder, bodyImpl, bodyArg, body);
    ARG_SETUP(IlBuilder, continueBuilderImpl, continueBuilderArg, continueBuilder);
    static_cast<TR::IlBuilder *>(_impl)->WhileDoLoopWithContinue(exitCondition, bodyArg, continueBuilderArg);
    ARG_RETURN(IlBuilder, bodyImpl, body);
    ARG_RETURN(IlBuilder, continueBuilderImpl, continueBuilder);
}

bool IlBuilder::buildIL() {
    return 0;
}

extern "C" void * allocateIlBuilder(void * impl) {
    return new IlBuilder(impl);
}

} // JitBuilder
} // OMR
