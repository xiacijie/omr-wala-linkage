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

extern "C" void * getImpl_TypeDictionary(void * client) {
    return static_cast<TR::TypeDictionary *>(static_cast<TypeDictionary *>(client)->_impl);
}

TypeDictionary::TypeDictionary() {
    auto * impl = ::new TR::TypeDictionary();
    static_cast<TR::TypeDictionary *>(impl)->setClient(this);
    initializeFromImpl(static_cast<void *>(impl));
}

TypeDictionary::TypeDictionary(void * impl) {
    if (impl != NULL) {
        static_cast<TR::TypeDictionary *>(impl)->setClient(this);
        initializeFromImpl(impl);
    }
}

void TypeDictionary::initializeFromImpl(void * impl) {
    _impl = impl;
    GET_CLIENT_OBJECT(clientObj_NoType, IlType, static_cast<TR::TypeDictionary *>(_impl)->NoType);
    NoType = clientObj_NoType;
    GET_CLIENT_OBJECT(clientObj_Int8, IlType, static_cast<TR::TypeDictionary *>(_impl)->Int8);
    Int8 = clientObj_Int8;
    GET_CLIENT_OBJECT(clientObj_Int16, IlType, static_cast<TR::TypeDictionary *>(_impl)->Int16);
    Int16 = clientObj_Int16;
    GET_CLIENT_OBJECT(clientObj_Int32, IlType, static_cast<TR::TypeDictionary *>(_impl)->Int32);
    Int32 = clientObj_Int32;
    GET_CLIENT_OBJECT(clientObj_Int64, IlType, static_cast<TR::TypeDictionary *>(_impl)->Int64);
    Int64 = clientObj_Int64;
    GET_CLIENT_OBJECT(clientObj_Float, IlType, static_cast<TR::TypeDictionary *>(_impl)->Float);
    Float = clientObj_Float;
    GET_CLIENT_OBJECT(clientObj_Double, IlType, static_cast<TR::TypeDictionary *>(_impl)->Double);
    Double = clientObj_Double;
    GET_CLIENT_OBJECT(clientObj_Address, IlType, static_cast<TR::TypeDictionary *>(_impl)->Address);
    Address = clientObj_Address;
    GET_CLIENT_OBJECT(clientObj_VectorInt8, IlType, static_cast<TR::TypeDictionary *>(_impl)->VectorInt8);
    VectorInt8 = clientObj_VectorInt8;
    GET_CLIENT_OBJECT(clientObj_VectorInt16, IlType, static_cast<TR::TypeDictionary *>(_impl)->VectorInt16);
    VectorInt16 = clientObj_VectorInt16;
    GET_CLIENT_OBJECT(clientObj_VectorInt32, IlType, static_cast<TR::TypeDictionary *>(_impl)->VectorInt32);
    VectorInt32 = clientObj_VectorInt32;
    GET_CLIENT_OBJECT(clientObj_VectorInt64, IlType, static_cast<TR::TypeDictionary *>(_impl)->VectorInt64);
    VectorInt64 = clientObj_VectorInt64;
    GET_CLIENT_OBJECT(clientObj_VectorFloat, IlType, static_cast<TR::TypeDictionary *>(_impl)->VectorFloat);
    VectorFloat = clientObj_VectorFloat;
    GET_CLIENT_OBJECT(clientObj_VectorDouble, IlType, static_cast<TR::TypeDictionary *>(_impl)->VectorDouble);
    VectorDouble = clientObj_VectorDouble;
    GET_CLIENT_OBJECT(clientObj_Word, IlType, static_cast<TR::TypeDictionary *>(_impl)->Word);
    Word = clientObj_Word;
    GET_CLIENT_OBJECT(clientObj_pNoType, IlType, static_cast<TR::TypeDictionary *>(_impl)->pNoType);
    pNoType = clientObj_pNoType;
    GET_CLIENT_OBJECT(clientObj_pInt8, IlType, static_cast<TR::TypeDictionary *>(_impl)->pInt8);
    pInt8 = clientObj_pInt8;
    GET_CLIENT_OBJECT(clientObj_pInt16, IlType, static_cast<TR::TypeDictionary *>(_impl)->pInt16);
    pInt16 = clientObj_pInt16;
    GET_CLIENT_OBJECT(clientObj_pInt32, IlType, static_cast<TR::TypeDictionary *>(_impl)->pInt32);
    pInt32 = clientObj_pInt32;
    GET_CLIENT_OBJECT(clientObj_pInt64, IlType, static_cast<TR::TypeDictionary *>(_impl)->pInt64);
    pInt64 = clientObj_pInt64;
    GET_CLIENT_OBJECT(clientObj_pFloat, IlType, static_cast<TR::TypeDictionary *>(_impl)->pFloat);
    pFloat = clientObj_pFloat;
    GET_CLIENT_OBJECT(clientObj_pDouble, IlType, static_cast<TR::TypeDictionary *>(_impl)->pDouble);
    pDouble = clientObj_pDouble;
    GET_CLIENT_OBJECT(clientObj_pAddress, IlType, static_cast<TR::TypeDictionary *>(_impl)->pAddress);
    pAddress = clientObj_pAddress;
    GET_CLIENT_OBJECT(clientObj_pVectorInt8, IlType, static_cast<TR::TypeDictionary *>(_impl)->pVectorInt8);
    pVectorInt8 = clientObj_pVectorInt8;
    GET_CLIENT_OBJECT(clientObj_pVectorInt16, IlType, static_cast<TR::TypeDictionary *>(_impl)->pVectorInt16);
    pVectorInt16 = clientObj_pVectorInt16;
    GET_CLIENT_OBJECT(clientObj_pVectorInt32, IlType, static_cast<TR::TypeDictionary *>(_impl)->pVectorInt32);
    pVectorInt32 = clientObj_pVectorInt32;
    GET_CLIENT_OBJECT(clientObj_pVectorInt64, IlType, static_cast<TR::TypeDictionary *>(_impl)->pVectorInt64);
    pVectorInt64 = clientObj_pVectorInt64;
    GET_CLIENT_OBJECT(clientObj_pVectorFloat, IlType, static_cast<TR::TypeDictionary *>(_impl)->pVectorFloat);
    pVectorFloat = clientObj_pVectorFloat;
    GET_CLIENT_OBJECT(clientObj_pVectorDouble, IlType, static_cast<TR::TypeDictionary *>(_impl)->pVectorDouble);
    pVectorDouble = clientObj_pVectorDouble;
    GET_CLIENT_OBJECT(clientObj_pWord, IlType, static_cast<TR::TypeDictionary *>(_impl)->pWord);
    pWord = clientObj_pWord;
    static_cast<TR::TypeDictionary *>(_impl)->setGetImpl(&getImpl_TypeDictionary);
}

TypeDictionary::~TypeDictionary() {}

void TypeDictionary::CloseStruct(const char * structName) {
    static_cast<TR::TypeDictionary *>(_impl)->CloseStruct(structName);
}

void TypeDictionary::CloseStruct(const char * structName, size_t size) {
    static_cast<TR::TypeDictionary *>(_impl)->CloseStruct(structName, size);
}

void TypeDictionary::CloseUnion(const char * unionName) {
    static_cast<TR::TypeDictionary *>(_impl)->CloseUnion(unionName);
}

void TypeDictionary::DefineField(const char * structName, const char * fieldName, IlType * type) {
    static_cast<TR::TypeDictionary *>(_impl)->DefineField(structName, fieldName, static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL));
}

void TypeDictionary::DefineField(const char * structName, const char * fieldName, IlType * type, size_t offset) {
    static_cast<TR::TypeDictionary *>(_impl)->DefineField(structName, fieldName, static_cast<TR::IlType *>(type != NULL ? type->_impl : NULL), offset);
}

IlType * TypeDictionary::DefineStruct(const char * structName) {
    TR::IlType * implRet = static_cast<TR::TypeDictionary *>(_impl)->DefineStruct(structName);
    GET_CLIENT_OBJECT(clientObj, IlType, implRet);
    return clientObj;
}

IlType * TypeDictionary::DefineUnion(const char * unionName) {
    TR::IlType * implRet = static_cast<TR::TypeDictionary *>(_impl)->DefineUnion(unionName);
    GET_CLIENT_OBJECT(clientObj, IlType, implRet);
    return clientObj;
}

IlType * TypeDictionary::GetFieldType(const char * structName, const char * fieldName) {
    TR::IlType * implRet = static_cast<TR::TypeDictionary *>(_impl)->GetFieldType(structName, fieldName);
    GET_CLIENT_OBJECT(clientObj, IlType, implRet);
    return clientObj;
}

IlType * TypeDictionary::LookupStruct(const char * structName) {
    TR::IlType * implRet = static_cast<TR::TypeDictionary *>(_impl)->LookupStruct(structName);
    GET_CLIENT_OBJECT(clientObj, IlType, implRet);
    return clientObj;
}

IlType * TypeDictionary::LookupUnion(const char * unionName) {
    TR::IlType * implRet = static_cast<TR::TypeDictionary *>(_impl)->LookupUnion(unionName);
    GET_CLIENT_OBJECT(clientObj, IlType, implRet);
    return clientObj;
}

size_t TypeDictionary::OffsetOf(const char * structName, const char * fieldName) {
    auto ret = static_cast<TR::TypeDictionary *>(_impl)->OffsetOf(structName, fieldName);
    return ret;
}

IlType * TypeDictionary::PointerTo(IlType * baseType) {
    TR::IlType * implRet = static_cast<TR::TypeDictionary *>(_impl)->PointerTo(static_cast<TR::IlType *>(baseType != NULL ? baseType->_impl : NULL));
    GET_CLIENT_OBJECT(clientObj, IlType, implRet);
    return clientObj;
}

IlType * TypeDictionary::PointerTo(const char * structName) {
    TR::IlType * implRet = static_cast<TR::TypeDictionary *>(_impl)->PointerTo(structName);
    GET_CLIENT_OBJECT(clientObj, IlType, implRet);
    return clientObj;
}

void TypeDictionary::UnionField(const char * unionName, const char * fieldName, IlType * fieldType) {
    static_cast<TR::TypeDictionary *>(_impl)->UnionField(unionName, fieldName, static_cast<TR::IlType *>(fieldType != NULL ? fieldType->_impl : NULL));
}

IlType * TypeDictionary::UnionFieldType(const char * unionName, const char * fieldName) {
    TR::IlType * implRet = static_cast<TR::TypeDictionary *>(_impl)->UnionFieldType(unionName, fieldName);
    GET_CLIENT_OBJECT(clientObj, IlType, implRet);
    return clientObj;
}

extern "C" void * allocateTypeDictionary(void * impl) {
    return new TypeDictionary(impl);
}

} // JitBuilder
} // OMR
