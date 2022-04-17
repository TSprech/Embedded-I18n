/**
 * @file ExampleData.hpp
 * @author TSprech
 * @date 2022/04/14
 * @copyright ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#ifndef EXAMPLEDATA_HPP
#define EXAMPLEDATA_HPP

#include <cstdint>

enum class Languages : uint16_t {
  English = 0,
  Spanish,
  Danish,
  Japanese,
  Invalid_Lead,
  Incomplete_Sequence,
  Invalid_Character,
};

const char8_t* const translated_strings[] = {u8"Hello", u8"¿Qué tal?", u8"Halløj", u8"こんにちは", u8"ABC\xff", u8"\xe3\xF1\x93", u8"\xe3\x81\x00"};

#endif // EXAMPLEDATA_HPP
