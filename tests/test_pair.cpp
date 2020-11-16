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

#include "cx/cx_pair.h"

struct A {};
struct B {};

static constexpr double kEpsilon = 1e-6;

TEST(Constructors, Default) {
    constexpr cx::pair<int, double> p{};
    static_assert(p.first == 0, "");
    static_assert(std::abs(p.second) < kEpsilon, "");
}

TEST(Constructors, CopyInit) {
    constexpr cx::pair<int, double> p{3, 3.14};
    static_assert(p.first == 3, "");
    static_assert(std::abs(p.second - 3.14) < kEpsilon, "");
}

TEST(Constructors, MoveInit) {
    constexpr cx::pair<A, B> p{A{}, B{}};
    static_assert(std::is_same<decltype(p.first), A>::value, "");
    static_assert(std::is_same<decltype(p.second), B>::value, "");
}

TEST(Constructors, CopyConstruct) {
    constexpr cx::pair<A, B> p{A{}, B{}};
    constexpr cx::pair<A, B> q{p};
    static_assert(std::is_same<decltype(p.first), A>::value, "");
    static_assert(std::is_same<decltype(p.second), B>::value, "");
    static_assert(std::is_same<decltype(q.first), A>::value, "");
    static_assert(std::is_same<decltype(q.second), B>::value, "");
}

TEST(Constructors, MoveConstruct) {
    constexpr cx::pair<A, B> p{A{}, B{}};
    constexpr cx::pair<A, B> q{std::move(p)};
    static_assert(std::is_same<decltype(p.first), A>::value, "");
    static_assert(std::is_same<decltype(p.second), B>::value, "");
    static_assert(std::is_same<decltype(q.first), A>::value, "");
    static_assert(std::is_same<decltype(q.second), B>::value, "");
}

TEST(AssignmentOperator, CopyAssign) {
    constexpr cx::pair<A, B> p{A{}, B{}};
    constexpr cx::pair<A, B> q = p;
    static_assert(std::is_same<decltype(p.first), A>::value, "");
    static_assert(std::is_same<decltype(p.second), B>::value, "");
    static_assert(std::is_same<decltype(q.first), A>::value, "");
    static_assert(std::is_same<decltype(q.second), B>::value, "");
}

TEST(AssignmentOperator, MoveAssign) {
    constexpr cx::pair<A, B> p{A{}, B{}};
    constexpr cx::pair<A, B> q = std::move(p);
    static_assert(std::is_same<decltype(p.first), A>::value, "");
    static_assert(std::is_same<decltype(p.second), B>::value, "");
    static_assert(std::is_same<decltype(q.first), A>::value, "");
    static_assert(std::is_same<decltype(q.second), B>::value, "");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
