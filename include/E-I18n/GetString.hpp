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
#include <string>

#include "ArchConfig.hpp"

#include "utfcppAdapted.hpp"
#include <memory_resource>

namespace ei18n {
  /**
   * @brief Retrieves a string for translation into the specified language.
   * @tparam T The type of the enum which specifies the language to be translated into. Typically can be deduced.
   * @param str The string which will be populated with the UTF32 characters.
   * @param msg_array The array which contains the translated strings.
   * @param lang_enum The enum value which represents the language to translate into. TODO: Default to the system language instead of 0.
   * @returns Any errors when converting.
   */
  template <typename T = uint16_t>
  auto GetString(ei18n_u32_string& str, auto msg_array, T lang_enum = 0) {
    return utfcpp::utf8to32(msg_array.at(static_cast<uint16_t>(lang_enum)), str);
  }
}  //namespace ei18n

#endif  // GETSTRING_HPP
