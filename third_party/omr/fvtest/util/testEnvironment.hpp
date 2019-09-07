/*******************************************************************************
 * Copyright (c) 2015, 2018 IBM Corp. and others
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

#ifndef TESTENVIRONMENT_HPP_
#define TESTENVIRONMENT_HPP_

/**
 * Google test's Environment class provides virtual SetUp() and TearDown() that are invoked before the
 * first test case is run and after the last test case completes. This complements Google test's Test
 * class, which provides virtual SetUp() and TearDown() that are invoked before and after each test case.
 *
 * The BaseEnvironment and PortEnvironment classes can be used directly or subclassed and
 * specialized as required. Other generic Environment subclasses, eg GCEnvironment, might belong here.
 *
 * Some Environment subclasses may require that SetUp() and TearDown() must be called on the same
 * thread. This should not be a problem, since the Google test framework runs each test suite on a
 * single thread, ie, the same test thread executes:
 *
 * 		Environment::SetUp() (Test::SetUp() TEST Test::TearDown())* Environment::TearDown()
 *
 */

#include <stdio.h>
#include "omrport.h"
#include "omrthread.h"
#include "omrTest.h"

enum LogLevel {
	LEVEL_VERBOSE = 0,
	LEVEL_INFO,
	LEVEL_WARN,
	LEVEL_ERROR,
	LEVEL_OFF
};

/**
 * BaseEnvironment provides access to command line arguments for all tests run from main().
 */
class BaseEnvironment: public ::testing::Environment
{
	/*
	 * Data members
	 */
private:
	int s_indentLevel;
protected:
	LogLevel _minLevel;
public:
	int _argc;
	char **_argv;
	OMRPortLibrary *portLib;

	/*
	 * Function members
	 */
private:
protected:
	virtual void
	SetUp()
	{
		for (int i = 1; i < _argc; i++) {
			if (0 == strncmp(_argv[i], "-logLevel=", strlen("-logLevel="))) {
				const char *logLevelStr = &_argv[i][strlen("-logLevel=")];
				if (0 == strcmp(logLevelStr, "verbose")) {
					_minLevel = LEVEL_VERBOSE;
				} else if (0 == strcmp(logLevelStr, "info")) {
					_minLevel = LEVEL_INFO;
				} else if (0 == strcmp(logLevelStr, "warn")) {
					_minLevel = LEVEL_WARN;
				} else if (0 == strcmp(logLevelStr, "error")) {
					_minLevel = LEVEL_ERROR;
				} else if (0 == strcmp(logLevelStr, "off")) {
					_minLevel = LEVEL_OFF;
				}	else {
					FAIL() << "Unrecognized -logLevel option, the valid log levels are verbose, info, warn, error, off.";
				}
			}
		}
	}

	virtual void TearDown() { }

	virtual void log_vprintf(LogLevel ll, const char *format, va_list args) {
		if (NULL != portLib) {
			OMRPORT_ACCESS_FROM_OMRPORT(portLib);
			if (ll >= _minLevel) {
				omrtty_vprintf(format, args);
			}
		} else {
			FAIL() << "Log function can only be used by child of BaseEnvironment which has port library initialized!";
		}
	}

public:
	BaseEnvironment(int argc, char **argv)
		: ::testing::Environment()
		, s_indentLevel(0)
		, _minLevel(LEVEL_ERROR) 
		, _argc(argc)
		, _argv(argv)
		, portLib(NULL)
	{
	}

	OMRPortLibrary *
	getPortLibrary()
	{
		return portLib;
	}
	
	virtual void
	indent(LogLevel ll)
	{
        	for (int i = 0; i < s_indentLevel; i++) {
			logRaw(ll, "\t");
        	}
	}

	virtual void
	changeIndent(int delta)
	{
        	s_indentLevel += delta;
	}


	virtual void
	log(const char *format, ...)
	{
		indent(LEVEL_INFO);
		va_list args;
		va_start(args, format);
		log_vprintf(LEVEL_INFO, format, args);
		va_end(args);
	}

	virtual void
	log(LogLevel ll, const char *format, ...)
	{
		indent(ll);
		va_list args;
		va_start(args, format);
		log_vprintf(ll, format, args);
		va_end(args);
	}

        virtual void
        logRaw(const char *format, ...)
        {
                va_list args;
                va_start(args, format);
                log_vprintf(LEVEL_INFO, format, args);
                va_end(args);
        }
	
        virtual void
        logRaw(LogLevel ll, const char *format, ...)
        {
                va_list args;
                va_start(args, format);
                log_vprintf(ll, format, args);
                va_end(args);
        }

};

/*
 * Thread library initialization can be performed only once per process, so it cannot be placed
 * in an Environment subclass without precluding use of the --gtest_repeat option, which is
 * sometimes useful for debugging tests that fail intermittently and unpredictably. These macros
 * can be used before and after RUN_ALL_TESTS() to attach and detach the main test thread.
 *
 * Note that Googletest's ASSERT_*() macros cannot be used in this context. Those macros can
 * only be used in methods that return void.
 */
#define INITIALIZE_THREADLIBRARY_AND_ATTACH() \
	do { \
		intptr_t rc = omrthread_attach_ex(NULL, J9THREAD_ATTR_DEFAULT); \
		if (0 != rc) { \
			fprintf(stderr, "omrthread_attach_ex(NULL, J9THREAD_ATTR_DEFAULT) failed, rc=%d\n", (int)rc); \
		} \
	} while (0)

#define DETACH_AND_DESTROY_THREADLIBRARY() \
	omrthread_detach(NULL); \
	omrthread_shutdown_library();

/**
 * PortEnvironment provides BaseEnvironment and initializes/finalizes the j9port
 * library for all tests run from main(). As a prerequisite, the omrthread library must be
 * initialized and the main test thread attached before instantiating this class and calling
 * RUN_ALL_TESTS() and the main test thread must be detached and the omrthread library shut
 * down after RUN_ALL_TESTS(). The INITIALIZE_THREADLIBRARY_AND_ATTACH() and DETACH_AND_DESTROY_THREADLIBRARY() macros can be used
 * for this purpose.
 */
class PortEnvironment: public BaseEnvironment
{
	/*
	 * Data members
	 */
private:
	OMRPortLibrary _portLibrary;
protected:
public:

	/*
	 * Function members
	 */
private:
protected:
	virtual void
	SetUp()
	{
		BaseEnvironment::SetUp();

		/* Use portlibrary version which we compiled against, and have allocated space
		 * for on the stack.  This version may be different from the one in the linked DLL.
		 */
		int rc = (int)omrport_init_library(&_portLibrary, sizeof(OMRPortLibrary));
		ASSERT_EQ(0, rc) << "omrport_init_library(&_OMRPortLibrary, sizeof(OMRPortLibrary)) failed, %d\n" << rc;
		portLib = &_portLibrary;
	}

	virtual void
	TearDown()
	{
		_portLibrary.port_shutdown_library(&_portLibrary);

		BaseEnvironment::TearDown();
	}
public:
	PortEnvironment(int argc, char **argv)
		: BaseEnvironment(argc, argv)
	{
	}
};

#endif /* TESTENVIRONMENT_HPP_ */
