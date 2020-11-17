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

namespace cx {

template<typename T, std::size_t N>
struct array {
    // a bunch of typedefs
    using value_type = T;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // all of the iterators
    constexpr const_iterator begin() const noexcept { return const_iterator(data()); }
    constexpr const_iterator end() const noexcept { return const_iterator(data() + N); }
    constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    constexpr const_iterator cbegin() const noexcept { return const_iterator(data()); }
    constexpr const_iterator cend() const noexcept { return const_iterator(data() + N); }
    constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
    constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    // capacity
    constexpr size_type size() const noexcept { return N; }
    constexpr size_type max_size() const noexcept { return N; }
    [[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }

    // element access
    constexpr const_reference operator[](size_type i) const noexcept { return elems_[i]; }
    constexpr const_reference at(size_type i) const {
        // we can't directly put the throw here since this is a core constant expression
        // (see C++ spec §5.20 [expr.const])
        if (i >= N) throw_out_of_range();
        return elems_[i];
    }

    constexpr const_reference front() const noexcept { return elems_[0]; }
    constexpr const_reference back() const noexcept { return N ? *(end() - 1) : *end(); }
    constexpr const_pointer data() const noexcept { return elems_; }

    const T elems_[N];
private:
    constexpr void throw_out_of_range() const {
        throw std::out_of_range("cx::array::at: index out of bounds");
    }
};

template<typename T, std::size_t N>
constexpr bool operator==(cx::array<T, N> lhs, cx::array<T, N> rhs) {
    for (int i = 0; i < N; ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}


}
