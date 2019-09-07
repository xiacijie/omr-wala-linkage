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

extern "C" void * getImpl_BytecodeBuilder(void * client) {
    return static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(static_cast<BytecodeBuilder *>(client)->_impl));
}


BytecodeBuilder::BytecodeBuilder(void * impl): IlBuilder((void *)NULL) {
    if (impl != NULL) {
        static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(impl))->setClient(this);
        initializeFromImpl(static_cast<void *>(static_cast<TR::IlBuilder *>(static_cast<TR::BytecodeBuilder *>(impl))));
    }
}

void BytecodeBuilder::initializeFromImpl(void * impl) {
    IlBuilder::initializeFromImpl(impl);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->setGetImpl(&getImpl_BytecodeBuilder);
}

BytecodeBuilder::~BytecodeBuilder() {}

int32_t BytecodeBuilder::bcIndex() {
    auto ret = static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->bcIndex();
    return ret;
}

char * BytecodeBuilder::name() {
    auto ret = static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->name();
    return ret;
}

VirtualMachineState * BytecodeBuilder::vmState() {
    TR::VirtualMachineState * implRet = static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->vmState();
    GET_CLIENT_OBJECT(clientObj, VirtualMachineState, implRet);
    return clientObj;
}

void BytecodeBuilder::AddFallThroughBuilder(BytecodeBuilder * ftb) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->AddFallThroughBuilder(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(ftb != NULL ? ftb->_impl : NULL)));
}

void BytecodeBuilder::AddSuccessorBuilders(uint32_t numBuilders, BytecodeBuilder ** builders) {
    ARRAY_ARG_SETUP(BytecodeBuilder, numBuilders, buildersArg, builders);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->AddSuccessorBuilders(numBuilders, buildersArg);
    ARRAY_ARG_RETURN(BytecodeBuilder, numBuilders, buildersArg, builders);
}

void BytecodeBuilder::AddSuccessorBuilders(uint32_t numBuilders, ...) {
    BytecodeBuilder ** builders = new BytecodeBuilder *[numBuilders];
    va_list vararg;
    va_start(vararg, numBuilders);
    for (int i = 0; i < numBuilders; ++i) { builders[i] = va_arg(vararg, BytecodeBuilder *); }
    va_end(vararg);
    AddSuccessorBuilders(numBuilders, builders);
    delete[] builders;
}

void BytecodeBuilder::AddSuccessorBuilder(BytecodeBuilder ** b) {
    ARG_SETUP(BytecodeBuilder, bImpl, bArg, b);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->AddSuccessorBuilder(bArg);
    ARG_RETURN(BytecodeBuilder, bImpl, b);
}

void BytecodeBuilder::Goto(BytecodeBuilder * b) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->Goto(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(b != NULL ? b->_impl : NULL)));
}

void BytecodeBuilder::Goto(BytecodeBuilder ** b) {
    ARG_SETUP(BytecodeBuilder, bImpl, bArg, b);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->Goto(bArg);
    ARG_RETURN(BytecodeBuilder, bImpl, b);
}

void BytecodeBuilder::IfCmpEqual(BytecodeBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpEqual(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void BytecodeBuilder::IfCmpEqual(BytecodeBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

void BytecodeBuilder::IfCmpLessOrEqual(BytecodeBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpLessOrEqual(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void BytecodeBuilder::IfCmpLessOrEqual(BytecodeBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpLessOrEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

void BytecodeBuilder::IfCmpLessThan(BytecodeBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpLessThan(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void BytecodeBuilder::IfCmpLessThan(BytecodeBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpLessThan(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

void BytecodeBuilder::IfCmpGreaterOrEqual(BytecodeBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpGreaterOrEqual(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void BytecodeBuilder::IfCmpGreaterOrEqual(BytecodeBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpGreaterOrEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

void BytecodeBuilder::IfCmpGreaterThan(BytecodeBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpGreaterThan(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void BytecodeBuilder::IfCmpGreaterThan(BytecodeBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpGreaterThan(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

void BytecodeBuilder::IfCmpNotEqual(BytecodeBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpNotEqual(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void BytecodeBuilder::IfCmpNotEqual(BytecodeBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpNotEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

void BytecodeBuilder::IfCmpUnsignedLessOrEqual(BytecodeBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpUnsignedLessOrEqual(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void BytecodeBuilder::IfCmpUnsignedLessOrEqual(BytecodeBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpUnsignedLessOrEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

void BytecodeBuilder::IfCmpUnsignedLessThan(BytecodeBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpUnsignedLessThan(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void BytecodeBuilder::IfCmpUnsignedLessThan(BytecodeBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpUnsignedLessThan(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

void BytecodeBuilder::IfCmpUnsignedGreaterOrEqual(BytecodeBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpUnsignedGreaterOrEqual(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void BytecodeBuilder::IfCmpUnsignedGreaterOrEqual(BytecodeBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpUnsignedGreaterOrEqual(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

void BytecodeBuilder::IfCmpUnsignedGreaterThan(BytecodeBuilder * target, IlValue * left, IlValue * right) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpUnsignedGreaterThan(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
}

void BytecodeBuilder::IfCmpUnsignedGreaterThan(BytecodeBuilder ** target, IlValue * left, IlValue * right) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpUnsignedGreaterThan(targetArg, static_cast<TR::IlValue *>(left != NULL ? left->_impl : NULL), static_cast<TR::IlValue *>(right != NULL ? right->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

void BytecodeBuilder::IfCmpEqualZero(BytecodeBuilder * target, IlValue * condition) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpEqualZero(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(condition != NULL ? condition->_impl : NULL));
}

void BytecodeBuilder::IfCmpEqualZero(BytecodeBuilder ** target, IlValue * condition) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpEqualZero(targetArg, static_cast<TR::IlValue *>(condition != NULL ? condition->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

void BytecodeBuilder::IfCmpNotEqualZero(BytecodeBuilder * target, IlValue * condition) {
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpNotEqualZero(static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(target != NULL ? target->_impl : NULL)), static_cast<TR::IlValue *>(condition != NULL ? condition->_impl : NULL));
}

void BytecodeBuilder::IfCmpNotEqualZero(BytecodeBuilder ** target, IlValue * condition) {
    ARG_SETUP(BytecodeBuilder, targetImpl, targetArg, target);
    static_cast<TR::BytecodeBuilder *>(static_cast<TR::IlBuilder *>(_impl))->IfCmpNotEqualZero(targetArg, static_cast<TR::IlValue *>(condition != NULL ? condition->_impl : NULL));
    ARG_RETURN(BytecodeBuilder, targetImpl, target);
}

extern "C" void * allocateBytecodeBuilder(void * impl) {
    return new BytecodeBuilder(impl);
}

} // JitBuilder
} // OMR
