#!/bin/sh
###############################################################################
# Copyright (c) 2015, 2015 IBM Corp. and others
# 
# This program and the accompanying materials are made available under
# the terms of the Eclipse Public License 2.0 which accompanies this
# distribution and is available at https://www.eclipse.org/legal/epl-2.0/
# or the Apache License, Version 2.0 which accompanies this distribution and
# is available at https://www.apache.org/licenses/LICENSE-2.0.
#      
# This Source Code may also be made available under the following
# Secondary Licenses when the conditions for such availability set
# forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
# General Public License, version 2 with the GNU Classpath
# Exception [1] and GNU General Public License, version 2 with the
# OpenJDK Assembly Exception [2].
#    
# [1] https://www.gnu.org/software/classpath/license.html
# [2] http://openjdk.java.net/legal/assembly-exception.html
#
# SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
###############################################################################

OMRDIR=$1
echo "\
${OMRDIR}/lib/libomrvmstartup.a \
${OMRDIR}/lib/libj9omr.a \
${OMRDIR}/lib/libomrgcstartup.a \
${OMRDIR}/lib/libomrgcstandard.a \
${OMRDIR}/lib/libomrgcverbose.a \
${OMRDIR}/lib/libomrgcverbosehandlerstandard.a \
${OMRDIR}/lib/libomrgcbase.a \
${OMRDIR}/lib/libomrgcstats.a \
${OMRDIR}/lib/libomrgcstructs.a \
${OMRDIR}/lib/libj9hookstatic.a \
${OMRDIR}/lib/libj9thrstatic.a \
${OMRDIR}/lib/libj9prtstatic.a \
${OMRDIR}/lib/libomrtrace.a \
${OMRDIR}/lib/libj9hashtable.a \
${OMRDIR}/lib/libj9avl.a \
${OMRDIR}/lib/libj9pool.a \
${OMRDIR}/lib/libomrutil.a"
