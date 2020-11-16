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

#include "cx/cx_string.h"

template<std::size_t N>
constexpr bool equal(const cx::string<N>& x, const char* y) {
    for (int i = 0; i < N; ++i) {
        if (x[i] != y[i]) return false;
    }
    return true;
}

TEST(Constructors, CharArray) {
    constexpr cx::string<4> x{"Test"};
    static_assert(x == "Test", "");
}

TEST(Constructors, CopyConstructor) {
    constexpr cx::string<4> x{"Test"};
    constexpr cx::string<4> y{x};
    static_assert(x == y, "");
}

TEST(Operators, Indexing) {
    constexpr cx::string<4> x{"Test"};
    constexpr auto y = x[0];
    static_assert(y == 'T', "");
}

TEST(Operators, InvalidIndexing) {
    constexpr cx::string<4> x{"Test"};
    // constexpr auto y = x[100];
}

TEST(Utilities, Size) {
    constexpr cx::string<4> x{"Test"};
    constexpr int s = x.size();
    static_assert(s == 4, "");
}

TEST(EqualityOperator, TwoEqualCxStrings) {
    constexpr cx::string<4> x{"Test"};
    constexpr cx::string<4> y{"Test"};
    constexpr auto result = x == y;
    static_assert(result, "");
}

TEST(EqualityOperator, TwoUnequalLengthCxStrings) {
    constexpr cx::string<4> x{"Test"};
    constexpr cx::string<5> y{"Test2"};
    constexpr auto result = x == y;
    static_assert(!result, "");
}

TEST(EqualityOperator, TwoUnequalValueCxStrings) {
    constexpr cx::string<4> x{"Test"};
    constexpr cx::string<4> y{"T4st"};
    constexpr auto result = x == y;
    static_assert(!result, "");
}

TEST(EqualityOperator, EqualCxStringAndCharArray) {
    constexpr cx::string<4> x{"Test"};
    constexpr const char y[5] = {"Test"};
    constexpr auto result = x == y;
    static_assert(result, "");
}

TEST(EqualityOperator, UnequalLengthCxStringAndCharArray) {
    constexpr cx::string<4> x{"Test"};
    constexpr const char y[6] = {"Test2"};
    constexpr auto result = x == y;
    static_assert(!result, "");
}

TEST(EqualityOperator, UnequalValueCxStringAndCharArray) {
    constexpr cx::string<4> x{"Test"};
    constexpr const char y[5] = {"T4st"};
    constexpr auto result = x == y;
    static_assert(!result, "");
}

TEST(ConcatOperator, TwoCxStrings) {
    constexpr cx::string<4> x{"Test"};
    constexpr cx::string<4> y{"Test"};
    constexpr auto z = x + y;
    static_assert(z == "TestTest", "");
}

TEST(ConcatOperator, CxStringAndCharArray) {
    constexpr cx::string<4> x{"Test"};
    constexpr const char y[5]{"Test"};
    constexpr auto z = x + y;
    static_assert(z == "TestTest", "");
}

TEST(LiteralCreation, EmptyString) {
    constexpr auto x = cx::lit("");
    static_assert(x.size() == 0, "");
    static_assert(x == "", "");
}

TEST(LiteralCreation, NonemptyString) {
    constexpr auto x = cx::lit("Test");
    static_assert(x.size() == 4, "");
    static_assert(x == "Test", "");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
