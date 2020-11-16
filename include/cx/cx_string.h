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

#include <cstring>
#include <string>

namespace cx {

// implementation heavily inspired by https://gist.github.com/dsanders11/8951887 and Jason Turner's constexpr talk
template<std::size_t N>
class string {
public:
    template<typename... Characters>
    constexpr string(Characters... characters)
            : str_{characters..., '\0'} {}

    template<std::size_t... Indices>
    constexpr string(const string<N>& rhs, std::index_sequence<Indices...> = typename std::make_index_sequence<N>{})
            : str_{rhs[Indices]..., '\0'} {}

    template<std::size_t X, std::size_t... Indices>
    constexpr string(const string<X>& rhs, std::index_sequence<Indices...>)
            : str_{rhs[Indices]..., '\0' } {}

    template<std::size_t... Indices>
    constexpr string(const char (&value)[N + 1], std::index_sequence<Indices...>)
            : string(value[Indices]...) {}

    constexpr string(const char (&value)[N + 1])
            : string(value, std::make_index_sequence<N>{}) {}

    constexpr char operator[](const std::size_t index) const {
        return index < N ? str_[index] : throw std::out_of_range("cx::string::operator[]: index out of range");
    }

    constexpr std::size_t size() const { return N; }

    constexpr const char* c_str() const { return str_; }
    std::string str() const { return std::string(str_); }

private:
    const char str_[N + 1];
};

template<typename T>
struct length_of {
    static_assert(true, "Must specialize type for length_of");
};

// char[] specializations
template<std::size_t N>
struct length_of<const char (&)[N]> {
    static constexpr std::size_t value = N - 1;
};

template<std::size_t N>
struct length_of<char[N]> {
    static constexpr std::size_t value = N - 1;
};

template<std::size_t N>
struct length_of<const char[N]> {
    static constexpr std::size_t value = N - 1;
};

// cx::string specializations
template<std::size_t N>
struct length_of<string<N>> {
    static constexpr std::size_t value = N;
};

template<std::size_t N>
struct length_of<const string<N>> {
    static constexpr std::size_t value = N;
};

template<std::size_t N>
struct length_of<const string<N>&> {
    static constexpr std::size_t value = N;
};

template<typename Left, typename Right>
constexpr bool operator==(const Left& lhs, const Right& rhs) {
    if (length_of<Left>::value != length_of<Right>::value) return false;
    for (int i = 0; i < length_of<Left>::value; ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

template<typename Left, typename Right, std::size_t... IndicesLeft, std::size_t... IndicesRight>
constexpr string<sizeof...(IndicesLeft) + sizeof...(IndicesRight)> concat_strs(
        const Left& lhs,
        const Right& rhs,
        std::index_sequence<IndicesLeft...>,
        std::index_sequence<IndicesRight...>) {
    return string<sizeof...(IndicesLeft) + sizeof...(IndicesRight)>(lhs[IndicesLeft]..., rhs[IndicesRight]...);
}

template<typename Left, typename Right>
constexpr string<length_of<Left>::value + length_of<Right>::value> concat_strs(const Left& lhs, const Right& rhs) {
    return concat_strs(lhs, rhs,
                       typename std::make_index_sequence<length_of<decltype(lhs)>::value>{},
                       typename std::make_index_sequence<length_of<decltype(rhs)>::value>{});
}

template<typename Left, typename Right>
constexpr auto operator+(const Left& lhs, const Right& rhs) {
    return concat_strs(lhs, rhs);
}

template<std::size_t N, std::size_t... Indices>
constexpr auto lit(const char (&value)[N], std::index_sequence<Indices...>) {
    return string<N - 1>(value[Indices]...);
}

template<std::size_t N>
constexpr auto lit(const char (&value)[N]) {
    return lit(value, typename std::make_index_sequence<N - 1>{});
}

}
