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

#ifndef UDT_HPP
#define UDT_HPP

#include "ddr/ir/Type.hpp"

class UDT : public Type
{
public:
	NamespaceUDT *_outerNamespace;
	unsigned int const _lineNumber;

	explicit UDT(size_t size, unsigned int lineNumber = 0);
	virtual ~UDT();

	virtual string getFullName() const;
	virtual bool insertUnique(Symbol_IR *ir);
	virtual NamespaceUDT * getNamespace();

	bool operator==(const Type & rhs) const;
	virtual bool compareToUDT(const UDT &) const;
};

#endif /* UDT_HPP */
