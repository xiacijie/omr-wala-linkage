###############################################################################
# Copyright (c) 2015, 2016 IBM Corp. and others
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

###
### omr_defs.mk
###
# This file contains defines which are to be used by languages using OMR.

ifndef OMRDIR
  OMRDIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
endif

ifndef SPEC
  $(error SPEC is not defined)
endif

OMR_IPATH = \
  $(OMRDIR)/include_core \
  $(OMRDIR)/omr/startup \
  $(OMRDIR)/gc/include \
  $(OMRDIR)/gc/startup
  
OMRGC_IPATH = \
  $(OMRDIR)/gc/base \
  $(OMRDIR)/gc/base/standard \
  $(OMRDIR)/gc/verbose \
  $(OMRDIR)/gc/verbose/handler_standard \
  $(OMRDIR)/gc/stats \
  $(OMRDIR)/gc/structs

# Public Core OMR header files
OMRINCLUDECORE = $(addprefix -I,$(OMR_IPATH))

# Internal OMR header files needed by OMR glue code
OMRGLUEINCLUDE = $(addprefix -I, $(OMRGC_IPATH))
