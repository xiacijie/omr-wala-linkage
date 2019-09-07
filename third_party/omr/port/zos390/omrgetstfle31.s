***********************************************************************
* Copyright (c) 2013, 2016 IBM Corp. and others
* 
* This program and the accompanying materials are made available 
* under the terms of the Eclipse Public License 2.0 which accompanies 
* this distribution and is available at  
* https://www.eclipse.org/legal/epl-2.0/ or the Apache License, 
* Version 2.0 which accompanies this distribution and
* is available at https://www.apache.org/licenses/LICENSE-2.0.
* 
* This Source Code may also be made available under the following
* Secondary Licenses when the conditions for such availability set
* forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
* General Public License, version 2 with the GNU Classpath 
* Exception [1] and GNU General Public License, version 2 with the
* OpenJDK Assembly Exception [2].
* 
* [1] https://www.gnu.org/software/classpath/license.html
* [2] http://openjdk.java.net/legal/assembly-exception.html
* 
* SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR
* GPL-2.0 WITH Classpath-exception-2.0 OR
* LicenseRef-GPL-2.0 WITH Assembly-exception
***********************************************************************

* This is a zOS 31 helper that stores the STFLE bits
* into the passed memory reference.  Called as a C func
* from C++ code.
*
* The helper returns the number of valid double-words in the STFLE
* bits, minus 1.
*
* The stfle instruction is encoded as 0xb2b00000 in binary, leaving
* it in as such so that we can compile on any platform.

        TITLE 'omrgetstfle31.s'

CARG1 EQU 1
CRA EQU 7
RETURNOFFSET EQU 4
r0 EQU 0
r3 EQU 3

Z_GSTFLE  DS 0D
     ENTRY Z_GSTFLE
Z_GSTFLE  ALIAS C'getstfle'
Z_GSTFLE  XATTR SCOPE(X),LINKAGE(XPLINK)
Z_GSTFLE      AMODE 31

  lr   r0,CARG1
  DC X'b2b02000'
  lr   r3,r0
  b  RETURNOFFSET(CRA)
