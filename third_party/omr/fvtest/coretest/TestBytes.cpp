/*******************************************************************************
 * Copyright (c) 2018, 2019 IBM Corp. and others
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

#include <OMR/Bytes.hpp>
#include <gtest/gtest.h>

namespace OMR
{

TEST(TestBytes, CompareZeroToZero)
{
	EXPECT_EQ(0, bytes(0));
	EXPECT_EQ(0, kibibytes(0));
	EXPECT_EQ(0, mebibytes(0));
	EXPECT_EQ(0, gibibytes(0));
}

TEST(TestBytes, CompareOneUnitToBytes)
{
	EXPECT_EQ(1, bytes(1));
	EXPECT_EQ(1024, kibibytes(1));
	EXPECT_EQ(1024 * 1024, mebibytes(1));
	EXPECT_EQ(1024 * 1024 * 1024, gibibytes(1));
}

TEST(TestBytes, CompareOneUnitToSmallerUnit)
{
	EXPECT_EQ(bytes(1024), kibibytes(1));
	EXPECT_EQ(kibibytes(1024), mebibytes(1));
	EXPECT_EQ(mebibytes(1024), gibibytes(1));
}

TEST(TestBytes, IsPow2)
{
	EXPECT_TRUE(isPow2(1));
	EXPECT_TRUE(isPow2(2));
	EXPECT_TRUE(isPow2(4));
	EXPECT_TRUE(isPow2(8));
	EXPECT_TRUE(isPow2(size_t(1) << ((sizeof(size_t)*8) - 1)));

	EXPECT_FALSE(isPow2(0));
	EXPECT_FALSE(isPow2(3));
	EXPECT_FALSE(isPow2(5));
	EXPECT_FALSE(isPow2(6));
	EXPECT_FALSE(isPow2(7));
	EXPECT_FALSE(isPow2(9));
	EXPECT_FALSE(isPow2(std::numeric_limits<size_t>::max()));
}

TEST(TestBytes, AlignedUnsafe)
{
	EXPECT_TRUE(alignedNoCheck(0, 0));
	EXPECT_FALSE(alignedNoCheck(1, 0));
	EXPECT_FALSE(alignedNoCheck(2, 0));
	EXPECT_FALSE(alignedNoCheck(gibibytes(1), 0));
}

TEST(TestBytes, Aligned)
{
	EXPECT_TRUE(aligned(1, 1));
	EXPECT_TRUE(aligned(2, 1));

	EXPECT_FALSE(aligned(1, 2));
	EXPECT_TRUE(aligned(2, 2));
	EXPECT_FALSE(aligned(3, 2));
}

TEST(TestBytes, AlignToZero)
{
	// Zero is considered an invalid input, since the calculation always results in zero.
	// This test is validating that behaviour, but users should NOT be aligning to zero.
	// the minimum valid alignment is 1.
	EXPECT_EQ(0, alignNoCheck(0, 0));
	EXPECT_EQ(0, alignNoCheck(1, 0));
	EXPECT_EQ(0, alignNoCheck(2, 0));
	EXPECT_EQ(0, alignNoCheck(3, 0));
	EXPECT_EQ(0, alignNoCheck(gibibytes(1), 0));
}

TEST(TestBytes, AlignToOne)
{
	EXPECT_EQ(0, align(0, 1));
	EXPECT_EQ(1, align(1, 1));
	EXPECT_EQ(2, align(2, 1));
	EXPECT_EQ(3, align(3, 1));
	EXPECT_EQ(gibibytes(1), align(gibibytes(1), 1));
}

TEST(TestBytes, AlignToTwo)
{
	EXPECT_EQ(0, align(0, 2));
	EXPECT_EQ(2, align(1, 2));
	EXPECT_EQ(2, align(2, 2));
	EXPECT_EQ(4, align(3, 2));
	EXPECT_EQ(gibibytes(1), align(gibibytes(1), 2));
}

TEST(TestBytes, AlignToFour)
{
	EXPECT_EQ(0, align(0, 4));
	EXPECT_EQ(4, align(1, 4));
	EXPECT_EQ(4, align(2, 4));
	EXPECT_EQ(4, align(3, 4));
	EXPECT_EQ(4, align(4, 4));
	EXPECT_EQ(8, align(5, 4));
	EXPECT_EQ(gibibytes(1), align(gibibytes(1), 4));
}

TEST(TestBytes, AlignToEight)
{
	EXPECT_EQ(0, align(0, 8));
	EXPECT_EQ(8, align(1, 8));
	EXPECT_EQ(8, align(7, 8));
	EXPECT_EQ(8, align(8, 8));
	EXPECT_EQ(16, align(9, 8));
	EXPECT_EQ(gibibytes(1), align(gibibytes(1), 8));
}

TEST(TestBytes, SaneAlignmentMaximums)
{
	EXPECT_NE(0, ALIGNMENT_MAX);
	EXPECT_NE(0, UNALIGNED_SIZE_MAX);
	EXPECT_TRUE(isPow2(ALIGNMENT_MAX));
	EXPECT_TRUE(isPow2(UNALIGNED_SIZE_MAX));
	EXPECT_LE(ALIGNMENT_MAX, UNALIGNED_SIZE_MAX);
	EXPECT_TRUE(aligned(UNALIGNED_SIZE_MAX, ALIGNMENT_MAX));

	// Soft requirement: we should be able to align sizes of at least 1Gib to
	// alignments of at least 1Gib.
	EXPECT_LE(gibibytes(1), ALIGNMENT_MAX);
	EXPECT_LE(gibibytes(1), UNALIGNED_SIZE_MAX);
}

TEST(TestBytes, AlignToMaximumAlignment)
{
	EXPECT_EQ(0, align(0, ALIGNMENT_MAX));
	EXPECT_EQ(ALIGNMENT_MAX, align(1, ALIGNMENT_MAX));

	EXPECT_EQ(UNALIGNED_SIZE_MAX, align(UNALIGNED_SIZE_MAX - 1, ALIGNMENT_MAX));
	EXPECT_EQ(UNALIGNED_SIZE_MAX, align(UNALIGNED_SIZE_MAX, ALIGNMENT_MAX));
}

TEST(TestBytes, TautologicalAlign)
{
	// Note: This only works because UNALIGNED_SIZE_MAX == ALIGNMENT_MAX.
	// If ALIGNMENT_MAX is ever decreased to allow a larger UNALIGNED_SIZE_MAX,
	// this test will fail.
	EXPECT_EQ(ALIGNMENT_MAX, align(UNALIGNED_SIZE_MAX, ALIGNMENT_MAX));
	EXPECT_EQ(UNALIGNED_SIZE_MAX, align(UNALIGNED_SIZE_MAX, UNALIGNED_SIZE_MAX));

	EXPECT_EQ(ALIGNMENT_MAX, align(ALIGNMENT_MAX - 1, ALIGNMENT_MAX));
	EXPECT_EQ(ALIGNMENT_MAX, align(ALIGNMENT_MAX, ALIGNMENT_MAX));
}

TEST(TestBytes, AlignAndOverflow)
{
	// purposefully overflow while aligning.
	EXPECT_EQ(0, alignNoCheck(UNALIGNED_SIZE_MAX + 1, ALIGNMENT_MAX));
	EXPECT_EQ(0, alignNoCheck(ALIGNMENT_MAX + 1, ALIGNMENT_MAX));
}

TEST(TestBytes, AlignMaximumSizeFor16byteAlignment)
{
	// hand crafted maximums for a 16 byte alignment
	EXPECT_EQ(std::numeric_limits<size_t>::max() - 15, align(std::numeric_limits<size_t>::max() - 17, 16));
	EXPECT_EQ(std::numeric_limits<size_t>::max(), align(std::numeric_limits<size_t>::max(), 1));
}

}  // namespace OMR
