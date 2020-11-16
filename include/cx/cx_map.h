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

#include <initializer_list>

#include "cx/cx_pair.h"
#include "cx/cx_array.h"

#include <exception>

namespace cx {

template<typename Key, typename T, std::size_t N>
class map {
public:
    // a bunch of typedefs
    using key_type = Key;
    using mapped_type = T;
    using value_type = cx::pair<const Key, const T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // constructors and assignment
    constexpr map() = default;
    constexpr map(std::initializer_list<value_type> entries)
            : map(entries, std::make_index_sequence<N>()) {
        if (entries.size() != N) throw std::invalid_argument("cx::map: initialized with wrong number of entries!");
    }

    constexpr map(const map&) = default;
    constexpr map(map&&) noexcept = default;

    constexpr map& operator=(const map&) = default;
    constexpr map& operator=(map&&) noexcept = default;

    // iterators
    constexpr const_iterator begin() const noexcept { return arr_.begin(); }
    constexpr const_iterator end() const noexcept { return arr_.end(); }
    constexpr const_reverse_iterator rbegin() const noexcept { return arr_.rbegin(); }
    constexpr const_reverse_iterator rend() const noexcept { return arr_.rend(); }
    constexpr const_iterator cbegin() const noexcept { return arr_.cbegin(); }
    constexpr const_iterator cend() const noexcept { return arr_.cend(); }
    constexpr const_reverse_iterator crbegin() const noexcept { return arr_.crbegin(); }
    constexpr const_reverse_iterator crend() const noexcept { return arr_.crend(); }

    // element access
    constexpr const T& at(const Key& key) const {
        for (int i = 0; i < arr_.size(); ++i) {
            if (arr_[i].first == key) return arr_[i].second;
        }
        // we can't directly put the throw here since this is a core constant expression
        // (see C++ spec §5.20 [expr.const])
        throw_out_of_range();
    }

    constexpr const T& operator[](const Key& key) const {
        return at(key);
    }

    // capacity
    constexpr bool empty() const noexcept { return size() == 0; }
    constexpr std::size_t size() const noexcept { return N; }
    constexpr std::size_t max_size() const noexcept { return N; }

    // lookup
    template<typename K>
    constexpr size_type count(const K& key) const {
       size_type count{};
        for (int i = 0; i < arr_.size(); ++i) {
            if (arr_[i].first == key) ++count;
        }
       return count;
    }

    constexpr size_type count(const Key& key) const {
        return count<Key>(key);
    }

private:
    const cx::array<value_type, N> arr_;

    // we need this roundabout way since std::array is an aggregate type with no constructor and we can't directly
    // convert a std::initializer_list into a no-constructor aggregate type without some std::index_sequence indirection
    template<std::size_t... Indices>
    constexpr map(std::initializer_list<value_type>& entries, std::index_sequence<Indices...>)
            : arr_{*(entries.begin() + Indices)...} {}

    constexpr void throw_out_of_range() const {
        throw std::out_of_range("cx::map::at: could not find entry in map");
    }
};

}
