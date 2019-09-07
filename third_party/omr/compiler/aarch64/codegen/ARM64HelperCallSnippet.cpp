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

#include "codegen/ARM64HelperCallSnippet.hpp"
#include "codegen/ARM64Instruction.hpp"
#include "codegen/CodeGenerator.hpp"
#include "codegen/Relocation.hpp"
#include "codegen/SnippetGCMap.hpp"
#include "runtime/CodeCacheManager.hpp"

uint8_t *
TR::ARM64HelperCallSnippet::emitSnippetBody()
   {
   uint8_t *cursor = cg()->getBinaryBufferCursor();
   intptr_t distance = (intptr_t)(getDestination()->getSymbol()->castToMethodSymbol()->getMethodAddress()) - (intptr_t)cursor;

   getSnippetLabel()->setCodeLocation(cursor);

   if (!constantIsSignedImm28(distance))
      {
      distance = TR::CodeCacheManager::instance()->findHelperTrampoline(getDestination()->getReferenceNumber(), (void *)cursor) - (intptr_t)cursor;
      TR_ASSERT(constantIsSignedImm28(distance), "Trampoline too far away.");
      }

   if (_restartLabel == NULL)
      {
      // b distance
      *(int32_t *)cursor = TR::InstOpCode::getOpCodeBinaryEncoding(TR::InstOpCode::b) | ((distance >> 2) & 0x3ffffff); // imm26
      }
   else
      {
      // bl distance
      *(int32_t *)cursor = TR::InstOpCode::getOpCodeBinaryEncoding(TR::InstOpCode::bl) | ((distance >> 2) & 0x3ffffff); // imm26
      }
   cg()->addExternalRelocation(new (cg()->trHeapMemory()) TR::ExternalRelocation(
                               cursor,
                               (uint8_t *)getDestination(),
                               TR_HelperAddress, cg()), __FILE__, __LINE__, getNode());
   cursor += ARM64_INSTRUCTION_LENGTH;

   gcMap().registerStackMap(cursor, cg());

   if (_restartLabel != NULL)
      {
      distance = (intptr_t)(_restartLabel->getCodeLocation()) - (intptr_t)cursor;
      if (constantIsSignedImm28(distance))
         {
         // b distance
         *(int32_t *)cursor = TR::InstOpCode::getOpCodeBinaryEncoding(TR::InstOpCode::b) | ((distance >> 2) & 0x3ffffff); // imm26
         cursor += ARM64_INSTRUCTION_LENGTH;
         }
      else
         {
         TR_ASSERT(false, "Target too far away.  Not supported yet");
         }
      }

   return cursor;
   }

uint32_t
TR::ARM64HelperCallSnippet::getLength(int32_t estimatedSnippetStart)
   {
   return ((_restartLabel == NULL) ? 1 : 2) * ARM64_INSTRUCTION_LENGTH;
   }
