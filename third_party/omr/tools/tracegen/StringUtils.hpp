/*******************************************************************************
 * Copyright (c) 2014, 2015 IBM Corp. and others
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

#ifndef STRINGUTILS_HPP_
#define STRINGUTILS_HPP_

#include "Port.hpp"

class StringUtils
{
	/*
	 * Data members
	 */
private:
protected:
public:

	/*
	 * Function members
	 */
private:
protected:
public:
	/**
	 * Find an integer value delimited by white space associated
	 * with the given key.
	 * @param line Format "prefix space number"
	 * @param key String prefix
	 * @return Value after the key. RC_FAILED if not found
	 */
	static RCType getPositiveIntValue(const char *line, const char *key, unsigned int *result);

	/**
	 * Check if text starts with prefix (case insensitive)
	 * @param text
	 * @param prefix
	 * @return true if the text starts with prefix, otherwise false.
	 */
	static bool startsWithUpperLower(const char *text, const char *prefix);

	/**
	 * Check if text contains toFind (case insensitive)
	 * @param text
	 * @param toFind
	 * @return Pointer to location in text that contains toFind, otherwise NULL
	 */
	static const char *containsUpperLower(const char *text, const char *toFind);
};
#endif /* STRINGUTILS_HPP_ */
