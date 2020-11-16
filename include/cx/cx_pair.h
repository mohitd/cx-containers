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

#pragma once

#include <algorithm>

namespace cx {

template<typename T1, typename T2>
struct pair {
    using first_type = T1;
    using second_type = T2;

    // constructors
    constexpr pair() : first{}, second{} {}
    constexpr pair(const T1& x, const T2& y) : first{x}, second{y} {}

    template<typename U1, typename U2>
    constexpr pair(U1&& x, U2&& y) : first{std::forward<U1>(x)}, second{std::forward<U2>(y)} {}

    template<typename U1, typename U2>
    constexpr pair(const pair<U1, U2>& p) : first{p.first}, second{p.second} {}

    template<typename U1, typename U2>
    constexpr pair(pair<U1, U2>&& p) : first{std::forward<U1>(p.first)}, second{std::forward<U2>(p.second)} {}

    constexpr pair(const pair& p) = default;
    constexpr pair(pair&& p) = default;

    // assignment operators
    constexpr pair& operator=(const pair& other) {
        first = other.first;
        second = other.second;
    }

    template<typename U1, typename U2>
    constexpr pair& operator=(const pair<U1, U2>& other) {
        first = other.first;
        second = other.second;
    }

    constexpr pair& operator=(pair&& other) noexcept {
        first = std::move(other.first);
        second = std::move(other.second);
    }

    template<typename U1, typename U2>
    constexpr pair& operator=(pair<U1, U2>&& other) noexcept {
        first = std::forward<U1>(other.first);
        second = std::forward<U2>(other.second);
    }

    T1 first;
    T2 second;
};

}
