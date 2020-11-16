// Copyright (c) 2020. Mohit Deshpande.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of
// the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <gtest/gtest.h>

#include "cx/cx_array.h"

TEST(Constructors, EmptyArray) {
    constexpr cx::array<int, 0> a{};
    static_assert(a.empty(), "");
}

TEST(Constructors, OneElement) {
    constexpr cx::array<int, 1> a{1};
    static_assert(a.size() == 1, "");
    static_assert(a.size() == a.max_size(), "");
}

TEST(Constructors, TwoElements) {
    constexpr cx::array<int, 2> a{1, 2};
    static_assert(a.size() == 2, "");
    static_assert(a.size() == a.max_size(), "");
}

TEST(ElementAccess, ValidIndex) {
    constexpr cx::array<int, 2> a{1, 2};
    constexpr auto e = a[0];
    static_assert(e == 1, "");
}

TEST(ElementAccess, InvalidIndex) {
    constexpr cx::array<int, 2> a{1, 2};
    //constexpr auto e = a[5];
    //static_assert(e == 1, "");
}

TEST(ElementAccess, ValidAt) {
    constexpr cx::array<int, 2> a{1, 2};
    constexpr auto e = a.at(0);
    static_assert(e == 1, "");
}

TEST(ElementAccess, InvalidAt) {
    constexpr cx::array<int, 2> a{1, 2};
    //constexpr auto e = a.at(5);
    //static_assert(e == 1, "");
}

TEST(EqualityOperator, EqualArrays) {
    constexpr cx::array<int, 2> a{1, 2};
    constexpr cx::array<int, 2> b{1, 2};
    static_assert(a == b, "");
}

TEST(EqualityOperator, UnequalArrays) {
    constexpr cx::array<int, 2> a{1, 2};
    constexpr cx::array<int, 2> b{1, 8};
    //static_assert(a == b, "");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
