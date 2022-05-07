/**
 * @file eternalAdapted.hpp
 * @brief This is an abridged version of mapbox's great eternal library to handle constexpr map lookup.
 * @author eternal Library: Mapbox
 * @author Adapted Changes: TSprech
 * @date 2022/05/06
 * @copyright mapbox Library:
 * ISC License
 * Copyright (c) 2018, Mapbox
 * Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby
 * granted, provided that the above copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL,
 * DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE
 * USE OR PERFORMANCE OF THIS SOFTWARE.
 * @copyright Adapted Code: ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#ifndef ETERNALADAPTED_HPP
#define ETERNALADAPTED_HPP

#include <cstdint>
#include <functional>
#include <utility>
#include <string_view>

namespace eternal {
  namespace impl {

    template <typename T>
    constexpr void swap(T& a, T& b) noexcept {
      T tmp{a};
      a = b;
      b = tmp;
    }

    template <typename Key>
    class compare_key {
     public:
      const Key key;

      constexpr compare_key(const Key& key_) noexcept
          : key(key_) {}

      template <typename Element>
      constexpr bool operator<(const Element& rhs) const noexcept {
        return key < rhs->first;
      }
    };

    template <typename Key, typename Value>
    class element {
     public:
      using key_type = Key;
      using mapped_type = Value;
      using value_type = std::pair<key_type, mapped_type>;
      using compare_key_type = compare_key<key_type>;

      constexpr element(const key_type& key, const mapped_type& value) noexcept
          : pair(key, value) {}

      constexpr bool operator<(const element& rhs) const noexcept {
        return pair.first < rhs.pair.first;
      }

      constexpr bool operator<(const compare_key_type& rhs) const noexcept {
        return pair.first < rhs.key;
      }

      constexpr const auto& operator*() const noexcept {
        return pair;
      }

      constexpr const auto* operator->() const noexcept {
        return &pair;
      }

      constexpr void swap(element& rhs) noexcept {
        impl::swap(pair.first, rhs.pair.first);
        impl::swap(pair.second, rhs.pair.second);
      }

     private:
      value_type pair;
    };

    template <typename Key, typename Hasher = std::hash<Key>>
    class compare_key_hash : public compare_key<Key> {
      using base_type = compare_key<Key>;

     public:
      const std::size_t hash;

      constexpr compare_key_hash(const Key& key_) noexcept
          : base_type(key_), hash(Hasher()(key_)) {
      }

      template <typename Element>
      constexpr bool operator<(const Element& rhs) const noexcept {
        return hash < rhs.hash || (!(rhs.hash < hash) && base_type::operator<(rhs));
      }
    };

    template <typename Key, typename Value, typename Hasher = std::hash<Key>>
    class element_hash : public element<Key, Value> {
      using base_type = element<Key, Value>;

     public:
      using key_type = Key;
      using mapped_type = Value;
      using compare_key_type = compare_key_hash<key_type, Hasher>;

      friend compare_key_type;

      constexpr element_hash(const key_type& key, const mapped_type& value) noexcept
          : base_type(key, value), hash(Hasher()(key)) {}

      template <typename T>
      constexpr bool operator<(const T& rhs) const noexcept {
        return hash < rhs.hash || (!(rhs.hash < hash) && base_type::operator<(rhs));
      }

      constexpr void swap(element_hash& rhs) noexcept {
        impl::swap(hash, rhs.hash);
        base_type::swap(rhs);
      }

     private:
      std::size_t hash;
    };
  }  // namespace impl

  template <typename Element>
  class iterator {
   public:
    constexpr iterator(const Element* pos_) noexcept
        : pos(pos_) {}

    constexpr bool operator==(const iterator& rhs) const noexcept {
      return pos == rhs.pos;
    }

    constexpr bool operator!=(const iterator& rhs) const noexcept {
      return pos != rhs.pos;
    }

    constexpr iterator& operator++() noexcept {
      ++pos;
      return *this;
    }

    constexpr iterator& operator+=(std::size_t i) noexcept {
      pos += i;
      return *this;
    }

    constexpr iterator operator+(std::size_t i) const noexcept {
      return pos + i;
    }

    constexpr iterator& operator--() noexcept {
      --pos;
      return *this;
    }

    constexpr iterator& operator-=(std::size_t i) noexcept {
      pos -= i;
      return *this;
    }

    constexpr std::size_t operator-(const iterator& rhs) const noexcept {
      return pos - rhs.pos;
    }

    constexpr const auto& operator*() const noexcept {
      return **pos;
    }

    constexpr const auto* operator->() const noexcept {
      return &**pos;
    }

   private:
    const Element* pos;
  };

  namespace impl {

    template <typename Compare, typename Iterator, typename Key>
    constexpr auto bound(Iterator left, Iterator right, const Key& key) noexcept {
      std::size_t count = right - left;
      while (count > 0) {
        const std::size_t step = count / 2;
        right = left + step;
        if (Compare()(*right, key)) {
          left = ++right;
          count -= step + 1;
        } else {
          count = step;
        }
      }
      return left;
    }

    struct less {
      template <typename A, typename B>
      constexpr bool operator()(const A& a, const B& b) const noexcept {
        return a < b;
      }
    };

    struct greater_equal {
      template <typename A, typename B>
      constexpr bool operator()(const A& a, const B& b) const noexcept {
        return !(b < a);
      }
    };

    template <typename Element, std::size_t N>
    class map {
     private:
      static_assert(N > 0, "map is empty");

      Element data_[N];

      template <typename T, std::size_t... I>
      constexpr map(const T (&data)[N], std::index_sequence<I...>) noexcept
          : data_{{data[I].first, data[I].second}...} {
        static_assert(sizeof...(I) == N, "index_sequence has identical length");
        // Yes, this is a bubblesort. It's usually evaluated at compile-time, it's fast for data
        // that is already sorted (like static maps), it has a small code size, and it's stable.
        for (auto left = data_, right = data_ + N - 1; data_ < right; right = left, left = data_) {
          for (auto it = data_; it < right; ++it) {
            if (it[1] < it[0]) {
              it[0].swap(it[1]);
              left = it;
            }
          }
        }
      }

      using compare_key_type = typename Element::compare_key_type;

     public:
      template <typename T>
      constexpr map(const T (&data)[N]) noexcept
          : map(data, std::make_index_sequence<N>()) {}

      using key_type = typename Element::key_type;
      using mapped_type = typename Element::mapped_type;
      using value_type = typename Element::value_type;
      using size_type = std::size_t;
      using difference_type = std::ptrdiff_t;
      using const_reference = const value_type&;
      using const_pointer = const value_type*;
      using const_iterator = iterator<Element>;

      constexpr bool unique() const noexcept {
        for (auto right = data_ + N - 1, it = data_; it < right; ++it) {
          if (!(it[0] < it[1])) {
            return false;
          }
        }
        return true;
      }

      constexpr const mapped_type& at(const key_type& key) const noexcept {
        return find(key)->second;
      }

      constexpr std::size_t size() const noexcept {
        return N;
      }

      constexpr const_iterator begin() const noexcept {
        return data_;
      }

      constexpr const_iterator cbegin() const noexcept {
        return begin();
      }

      constexpr const_iterator end() const noexcept {
        return data_ + N;
      }

      constexpr const_iterator cend() const noexcept {
        return end();
      }

      constexpr const_iterator lower_bound(const key_type& key) const noexcept {
        return bound<less>(data_, data_ + N, compare_key_type{key});
      }

      constexpr const_iterator upper_bound(const key_type& key) const noexcept {
        return bound<greater_equal>(data_, data_ + N, compare_key_type{key});
      }

      constexpr std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const noexcept {
        const compare_key_type compare_key{key};
        auto first = bound<less>(data_, data_ + N, compare_key);
        return {first, bound<greater_equal>(first, data_ + N, compare_key)};
      }

      constexpr std::size_t count(const key_type& key) const noexcept {
        const auto range = equal_range(key);
        return range.second - range.first;
      }

      constexpr const_iterator find(const key_type& key) const noexcept {
        const compare_key_type compare_key{key};
        auto it = bound<less>(data_, data_ + N, compare_key);
        if (it != data_ + N && greater_equal()(*it, compare_key)) {
          return it;
        } else {
          return end();
        }
      }

      constexpr bool contains(const key_type& key) const noexcept {
        return find(key) != end();
      }
    };

    /// TODO: Combine the map and translation map to remove repeated code
    template <typename Element, std::size_t N>
    class translation_map {
     private:
      static_assert(N > 0, "map is empty");

      Element data_[N];

      template <typename T, std::size_t... I>
      constexpr translation_map(const T (&data)[N], std::index_sequence<I...>) noexcept
          : data_{{data[I].at(0), data[I]}...} {
        static_assert(sizeof...(I) == N, "index_sequence has identical length");
        // Yes, this is a bubblesort. It's usually evaluated at compile-time, it's fast for data
        // that is already sorted (like static maps), it has a small code size, and it's stable.
        for (auto left = data_, right = data_ + N - 1; data_ < right; right = left, left = data_) {
          for (auto it = data_; it < right; ++it) {
            if (it[1] < it[0]) {
              it[0].swap(it[1]);
              left = it;
            }
          }
        }
      }

      using compare_key_type = typename Element::compare_key_type;

     public:
      template <typename T>
      constexpr translation_map(const T (&data)[N]) noexcept
          : translation_map(data, std::make_index_sequence<N>()) {}

      using key_type = typename Element::key_type;
      using mapped_type = typename Element::mapped_type;
      using value_type = typename Element::value_type;
      using size_type = std::size_t;
      using difference_type = std::ptrdiff_t;
      using const_reference = const value_type&;
      using const_pointer = const value_type*;
      using const_iterator = iterator<Element>;

      constexpr bool unique() const noexcept {
        for (auto right = data_ + N - 1, it = data_; it < right; ++it) {
          if (!(it[0] < it[1])) {
            return false;
          }
        }
        return true;
      }

      constexpr const mapped_type& at(const key_type& key) const noexcept {
        return find(key)->second;
      }

      constexpr std::size_t size() const noexcept {
        return N;
      }

      constexpr const_iterator begin() const noexcept {
        return data_;
      }

      constexpr const_iterator cbegin() const noexcept {
        return begin();
      }

      constexpr const_iterator end() const noexcept {
        return data_ + N;
      }

      constexpr const_iterator cend() const noexcept {
        return end();
      }

      constexpr const_iterator lower_bound(const key_type& key) const noexcept {
        return bound<less>(data_, data_ + N, compare_key_type{key});
      }

      constexpr const_iterator upper_bound(const key_type& key) const noexcept {
        return bound<greater_equal>(data_, data_ + N, compare_key_type{key});
      }

      constexpr std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const noexcept {
        const compare_key_type compare_key{key};
        auto first = bound<less>(data_, data_ + N, compare_key);
        return {first, bound<greater_equal>(first, data_ + N, compare_key)};
      }

      constexpr std::size_t count(const key_type& key) const noexcept {
        const auto range = equal_range(key);
        return range.second - range.first;
      }

      constexpr const_iterator find(const key_type& key) const noexcept {
        const compare_key_type compare_key{key};
        auto it = bound<less>(data_, data_ + N, compare_key);
        if (it != data_ + N && greater_equal()(*it, compare_key)) {
          return it;
        } else {
          return end();
        }
      }

      constexpr bool contains(const key_type& key) const noexcept {
        return find(key) != end();
      }
    };
  }  // namespace impl

  template <typename Key, typename Value, std::size_t N>
  static constexpr auto map(const std::pair<const Key, const Value> (&items)[N]) noexcept {
    return impl::map<impl::element<Key, Value>, N>(items);
  }

  template <typename Value, std::size_t ArrSize, std::size_t N>
  static constexpr auto translation_map(const std::array<Value, ArrSize> (&items)[N]) noexcept {
    return impl::translation_map<impl::element<Value, std::array<Value, ArrSize>>, N>(items);
  }

  template <typename Key, typename Value, std::size_t N>
  static constexpr auto hash_map(const std::pair<const Key, const Value> (&items)[N]) noexcept {
    return impl::map<impl::element_hash<Key, Value>, N>(items);
  }
}  // namespace eternal

// eternal::string

namespace eternal {
  namespace impl {

    // Use different constants for 32 bit vs. 64 bit size_t
    constexpr std::size_t hash_offset = std::conditional_t<sizeof(std::size_t) < 8,
                                                           std::integral_constant<uint32_t, 0x811C9DC5>,
                                                           std::integral_constant<uint64_t, 0xCBF29CE484222325>>::value;

    constexpr std::size_t hash_prime = std::conditional_t<sizeof(std::size_t) < 8,
                                                          std::integral_constant<uint32_t, 0x1000193>,
                                                          std::integral_constant<uint64_t, 0x100000001B3>>::value;

    // FNV-1a hash
    constexpr static std::size_t str_hash(const char* str,
                                          const std::size_t value = hash_offset) noexcept {
      return *str ? str_hash(str + 1, (value ^ static_cast<std::size_t>(*str)) * hash_prime) : value;
    }

    constexpr bool str_less(const char* lhs, const char* rhs) noexcept {
      return *lhs && *rhs && *lhs == *rhs ? str_less(lhs + 1, rhs + 1) : *lhs < *rhs;
    }

    constexpr bool str_equal(const char* lhs, const char* rhs) noexcept {
      return *lhs == *rhs && (*lhs == '\0' || str_equal(lhs + 1, rhs + 1));
    }

    constexpr bool u8str_less(const char8_t* lhs, const char8_t* rhs) noexcept {
      return *lhs && *rhs && *lhs == *rhs ? u8str_less(lhs + 1, rhs + 1) : *lhs < *rhs;
    }

    constexpr bool u8str_equal(const char8_t* lhs, const char8_t* rhs) noexcept {
      return *lhs == *rhs && (*lhs == '\0' || u8str_equal(lhs + 1, rhs + 1));
    }
  }  // namespace impl

  class string {
   private:
    const char* data_;

   public:
    constexpr string(char const* data) noexcept
        : data_(data) {}

    constexpr string(const string&) noexcept = default;
    constexpr string(string&&) noexcept = default;
    constexpr string& operator=(const string&) noexcept = default;
    constexpr string& operator=(string&&) noexcept = default;

    constexpr bool operator<(const string& rhs) const noexcept {
      return impl::str_less(data_, rhs.data_);
    }

    constexpr bool operator==(const string& rhs) const noexcept {
      return impl::str_equal(data_, rhs.data_);
    }

    constexpr const char* data() const noexcept {
      return data_;
    }

    constexpr const char* c_str() const noexcept {
      return data_;
    }
  };

  class u8string {
   private:
    const char8_t* data_;

   public:
    constexpr u8string(char8_t const* data) noexcept
        : data_(data) {}

    constexpr u8string(std::basic_string_view<char8_t> data) noexcept
        : data_(data.data()) {}

    constexpr u8string(const u8string&) noexcept = default;
    constexpr u8string(u8string&&) noexcept = default;
    constexpr u8string& operator=(const u8string&) noexcept = default;
    constexpr u8string& operator=(u8string&&) noexcept = default;

    constexpr bool operator<(const u8string& rhs) const noexcept {
      return impl::u8str_less(data_, rhs.data_);
    }

    constexpr bool operator==(const u8string& rhs) const noexcept {
      return impl::u8str_equal(data_, rhs.data_);
    }

    constexpr const char8_t* data() const noexcept {
      return data_;
    }

    constexpr const char8_t* c_str() const noexcept {
      return data_;
    }
  };
}  // namespace eternal

namespace std {
  template <>
  struct hash<::eternal::string> {
    constexpr std::size_t operator()(const ::eternal::string& str) const {
      return ::eternal::impl::str_hash(str.data());
    }
  };
}  // namespace std

#endif  //ETERNALADAPTED_HPP
