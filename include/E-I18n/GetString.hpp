/**
 * @file GetString.hpp
 * @author TSprech
 * @date 2022/04/14
 * @copyright ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#ifndef GETSTRING_HPP
#define GETSTRING_HPP

#include <cstdint>
#include <memory_resource>
#include <string>
#include <span>

#include "utfcppAdapted.hpp"

#include "eternalAdapted.hpp"

namespace ei18n {
  constexpr auto GetMap(const eternal::u8string key, const auto map) { return map.at(key); }

  /**
   * @brief Retrieves a pmr::u32string for translation into the specified language.
   * @tparam T The type of the enum which specifies the language to be translated into. Typically can be deduced.
   * @param str The string which will be populated with the UTF32 characters.
   * @param msg_array The array which contains the translated strings.
   * @param lang_enum The enum value which represents the language to translate into. TODO: Default to the system language instead of 0.
   * @returns Any errors when converting.
   */
  template <typename T = uint16_t>
  auto GetString(std::pmr::u32string& str, std::span<const std::basic_string_view<char8_t>> msg_array, T lang_enum = 0) -> utfcpp::utf_error {
    return utfcpp::utf8to32(msg_array[static_cast<uint16_t>(lang_enum)], str);
  }

  /**
   * @brief Retrieves a u32string for translation into the specified language.
   * @tparam T The type of the enum which specifies the language to be translated into. Typically can be deduced.
   * @param str The string which will be populated with the UTF32 characters.
   * @param msg_array The array which contains the translated strings.
   * @param lang_enum The enum value which represents the language to translate into. TODO: Default to the system language instead of 0.
   * @returns Any errors when converting.
   */
  template <typename T = uint16_t>
  auto GetString(std::u32string& str, std::span<const std::basic_string_view<char8_t>> msg_array, T lang_enum = 0) -> utfcpp::utf_error {
    return utfcpp::utf8to32(msg_array[static_cast<uint16_t>(lang_enum)], str);
  }
}  //namespace ei18n

#endif  // GETSTRING_HPP
