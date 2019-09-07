/*******************************************************************************
 * Copyright (c) 2000, 2018 IBM Corp. and others
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

/*
 * This file will be included within an enum.  Only comments and enumerator
 * definitions are permitted.
 */

IsNotExtended,
      IsLabel,
         IsVirtualGuardNOP,
      IsFence,
      IsPadding,
      IsAlignment,
      IsBoundaryAvoidance,
         IsPatchableCodeAlignment,
      IsImm,
         IsImmSnippet,
         IsImmSym,
      IsImm64,
         IsImm64Sym,
      IsVFPSave,
      IsVFPRestore,
      IsVFPDedicate,
      IsVFPRelease,
      IsVFPCallCleanup,
      IsReg,
         IsRegReg,
            IsRegRegImm,
            IsRegRegReg,
            IsFPRegReg,
               IsFPST0ST1RegReg,
               IsFPST0STiRegReg,
               IsFPSTiST0RegReg,
               IsFPArithmeticRegReg,
               IsFPCompareRegReg,
               IsFPRemainderRegReg,
         IsRegImm,
            IsRegImmSym,
         IsRegImm64,
            IsRegImm64Sym,
         IsRegMem,
            IsRegMemImm,
            IsRegRegMem,
            IsFPRegMem,
         IsFPReg,
      IsMem,
         IsMemTable,
         IsCallMem,
         IsMemImm,
            IsMemImmSym,
            IsMemImmSnippet,
         IsMemReg,
            IsMemRegImm,
            IsFPMemReg,
      IsFPCompareEval,
      IsFfsdPPSRecord,
