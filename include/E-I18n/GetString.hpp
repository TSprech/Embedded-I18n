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

template <typename T = uint16_t>
auto GetString(auto msg_array, T lang_enum = 0) {
  return msg_array[static_cast<uint16_t>(lang_enum)];
}

#endif // GETSTRING_HPP
