/*******************************************************************************
 * Copyright (c) 2016, 2018 IBM Corp. and others
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

#ifndef MACROINFO_HPP
#define MACROINFO_HPP

#include "ddr/std/string.hpp"

#include <set>

using std::pair;
using std::set;
using std::string;

class MacroInfo {
private:
	/* This could be a real type name, or a fake type name representing a
	 * custom rule associated with a macro, or a name based off of a file.
	 */
	string _typeName;

	/* A list of all macros associated with typeName */
	set<pair<string, string> > _macros;

public:
	explicit MacroInfo(const string &typeName);

	const string &getTypeName() const;
	void addMacro(const string &name, const string &value);
	size_t getNumMacros() const;
	set<pair<string, string> >::const_iterator getMacroStart() const;
	set<pair<string, string> >::const_iterator getMacroEnd() const;
};

#endif /* MACROINFO_HPP */
