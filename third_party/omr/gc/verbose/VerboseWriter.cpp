/*******************************************************************************
 * Copyright (c) 1991, 2016 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
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
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

#include "modronapicore.hpp"

#include "VerboseWriter.hpp"

#include "GCExtensionsBase.hpp"

#undef _UTE_MODULE_HEADER_
#undef UT_MODULE_LOADED
#undef UT_MODULE_UNLOADED
#include "ut_j9vgc.h"

/* Output constants */
#define VERBOSEGC_HEADER "<?xml version=\"1.0\" ?>\n\n<verbosegc xmlns=\"http://www.ibm.com/j9/verbosegc\" version=\"%s\">\n\n"
#define VERBOSEGC_FOOTER "</verbosegc>\n"

MM_VerboseWriter::MM_VerboseWriter(WriterType type)
	: MM_Base()
	,_nextWriter(NULL)
	,_header(NULL)
	,_footer(NULL)
	,_type(type)
	,_isActive(false)
{}

const char*
MM_VerboseWriter::getHeader(MM_EnvironmentBase *env)
{
	return _header;
}

const char*
MM_VerboseWriter::getFooter(MM_EnvironmentBase *env)
{
	return _footer;
}

MM_VerboseWriter*
MM_VerboseWriter::getNextWriter()
{
	return _nextWriter;
}

void
MM_VerboseWriter::setNextWriter(MM_VerboseWriter* writer)
{
	_nextWriter = writer;
}

void
MM_VerboseWriter::tearDown(MM_EnvironmentBase* env)
{
	MM_GCExtensionsBase* ext = env->getExtensions();
	ext->getForge()->free(_header);
	_header = NULL;
	ext->getForge()->free(_footer);
	_footer = NULL;
}

void
MM_VerboseWriter::kill(MM_EnvironmentBase* env) {
	tearDown(env);
	env->getExtensions()->getForge()->free(this);
}

bool
MM_VerboseWriter::initialize(MM_EnvironmentBase* env)
{
	OMRPORT_ACCESS_FROM_OMRPORT(env->getPortLibrary());
	MM_GCExtensionsBase* ext = env->getExtensions();

	/* Initialize _header */
	const char* version = omrgc_get_version(env->getOmrVM());
	/* The length is -2 for the "%s" in VERBOSEGC_HEADER and +1 for '\0' */
	uintptr_t headerLength = strlen(version) + strlen(VERBOSEGC_HEADER) - 1;
	_header = (char*)ext->getForge()->allocate(sizeof(char) * headerLength, OMR::GC::AllocationCategory::DIAGNOSTIC, OMR_GET_CALLSITE());
	if (NULL == _header) {
		return false;
	}
	omrstr_printf(_header, headerLength, VERBOSEGC_HEADER, version);

	/* Initialize _footer */
	uintptr_t footerLength = strlen(VERBOSEGC_FOOTER) + 1;
	_footer = (char*)ext->getForge()->allocate(sizeof(char) * footerLength, OMR::GC::AllocationCategory::DIAGNOSTIC, OMR_GET_CALLSITE());
	if (NULL == _footer) {
		ext->getForge()->free(_header);
		return false;
	}
	omrstr_printf(_footer, footerLength, VERBOSEGC_FOOTER);
	
	return true;
}
