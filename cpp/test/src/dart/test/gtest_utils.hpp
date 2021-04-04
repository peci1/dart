/*
 * Copyright (c) 2011-2021, The DART development contributors
 * All rights reserved.
 *
 * The list of contributors can be found at:
 *   https://github.com/dartsim/dart/blob/master/LICENSE
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <gtest/gtest.h>

#include "dart/common/all.hpp"

#define EXPECT_SCALAR_EQ(val1, val2)                                           \
  if constexpr (::std::is_same_v<Scalar, float>) {                             \
    EXPECT_FLOAT_EQ(val1, val2);                                               \
  } else {                                                                     \
    EXPECT_DOUBLE_EQ(val1, val2);                                              \
  }                                                                            \
  void ANONYMOUS_FUNCTION_1()

#define EXPECT_S_EQ(val1, val2)                                                \
  if constexpr (::std::is_same_v<S, float>) {                                  \
    EXPECT_FLOAT_EQ(val1, val2);                                               \
  } else {                                                                     \
    EXPECT_DOUBLE_EQ(val1, val2);                                              \
  }                                                                            \
  void ANONYMOUS_FUNCTION_2()

#define EXPECT_VECTOR2_EQ(expected, actual)                                    \
  EXPECT_DOUBLE_EQ((expected).x(), (actual).x());                              \
  EXPECT_DOUBLE_EQ((expected).y(), (actual).y())

#define EXPECT_VECTOR2_NEAR(expected, actual, eps)                             \
  EXPECT_NEAR((expected).x(), (actual).x(), eps);                              \
  EXPECT_NEAR((expected).y(), (actual).y(), eps)

#define EXPECT_VECTOR3_EQ(expected, actual)                                    \
  EXPECT_DOUBLE_EQ((expected).x(), (actual).x());                              \
  EXPECT_DOUBLE_EQ((expected).y(), (actual).y());                              \
  EXPECT_DOUBLE_EQ((expected).z(), (actual).z())

#define EXPECT_VECTOR3_NEAR(expected, actual, eps)                             \
  EXPECT_NEAR((expected).x(), (actual).x(), eps);                              \
  EXPECT_NEAR((expected).y(), (actual).y(), eps);                              \
  EXPECT_NEAR((expected).z(), (actual).z(), eps)

#define EXPECT_VECTOR4_EQ(expected, actual)                                    \
  EXPECT_DOUBLE_EQ((expected).x(), (actual).x());                              \
  EXPECT_DOUBLE_EQ((expected).y(), (actual).y());                              \
  EXPECT_DOUBLE_EQ((expected).z(), (actual).z());                              \
  EXPECT_DOUBLE_EQ((expected).w(), (actual).w())

#define EXPECT_VECTOR4_NEAR(expected, actual, eps)                             \
  EXPECT_NEAR((expected).x(), (actual).x(), eps);                              \
  EXPECT_NEAR((expected).y(), (actual).y(), eps);                              \
  EXPECT_NEAR((expected).z(), (actual).z(), eps);                              \
  EXPECT_NEAR((expected).w(), (actual).w(), eps)

#define EXPECT_BOUNDING_BOX2_EQ(expected, actual)                              \
  EXPECT_VECTOR2_EQ((expected).lowerCorner, (actual).lowerCorner);             \
  EXPECT_VECTOR2_EQ((expected).upperCorner, (actual).upperCorner)

#define EXPECT_BOUNDING_BOX2_NEAR(expected, actual, eps)                       \
  EXPECT_VECTOR2_NEAR((expected).lowerCorner, (actual).lowerCorner, eps);      \
  EXPECT_VECTOR2_NEAR((expected).upperCorner, (actual).upperCorner, eps);

#define EXPECT_BOUNDING_BOX3_EQ(expected, actual)                              \
  EXPECT_VECTOR3_EQ((expected).lowerCorner, (actual).lowerCorner);             \
  EXPECT_VECTOR3_EQ((expected).upperCorner, (actual).upperCorner)

#define EXPECT_BOUNDING_BOX3_NEAR(expected, actual, eps)                       \
  EXPECT_VECTOR3_NEAR((expected).lowerCorner, (actual).lowerCorner, eps);      \
  EXPECT_VECTOR3_NEAR((expected).upperCorner, (actual).upperCorner, eps)

namespace dart::test {

#if DART_ARCH_S390X
using FloatingTypes = testing::Types<float, double>;
#else
using FloatingTypes = testing::Types<float, double, long double>;
#endif

} // namespace dart::test
