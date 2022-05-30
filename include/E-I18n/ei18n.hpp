/**
 * @file GetString.hpp
 * @author TSprech
 * @date 2022/04/29
 * @copyright ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#ifndef EI18N_HPP
#define EI18N_HPP

#include <array>
#include <memory_resource>
#include <string>

#include "ArchConfig.hpp"

namespace ei18n {
  inline namespace literals {
  inline namespace string_view_literals {
    inline constexpr std::basic_string_view<char8_t>
    operator""_sv8(const char8_t* str, size_t len) noexcept {
      return std::basic_string_view<char8_t>{str, len};
    }

    inline constexpr std::basic_string_view<char32_t>
    operator""_sv32(const char32_t* str, size_t len) noexcept {
      return std::basic_string_view<char32_t>{str, len};
    }
  }
  }  // namespace literals::string_view_literals

  enum LocaleIndexes {
    quotation_start,
    quotation_end,
    alt_quotation_start,
    alt_quotation_end,
    decimal,
    group,
    list,
    percent_sign,
    plus_sign,
    minus_sign,
    exponential,
    superscripting_exponent,
    infinity,
    nan,
    weekdays_shortened,
    am,
    pm,
    time_format_h_m_s,
    time_format_h_m
  };
}  // namespace ei18n

#define PMR_NULL_STRING(pmr_string_name_, buffer_size_)                                                                                                                                   \
  std::array<uint8_t, buffer_size_> pmr_string_name_##_buffer_{0};                                                                                                                        \
  std::pmr::monotonic_buffer_resource pmr_string_name_##_buffer_memory_resource_(pmr_string_name_##_buffer_.data(), pmr_string_name_##_buffer_.size(), std::pmr::null_memory_resource()); \
  ei18n_u32_string pmr_string_name_(&pmr_string_name_##_buffer_memory_resource_)

#endif  // EI18N_HPP
