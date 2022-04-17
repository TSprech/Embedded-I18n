/**
 * @file ExampleData.hpp
 * @author TSprech
 * @author UTF-8 Decoder Capability and Stress Test strings: Markus Kuhn
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
  Japanese
};

const char8_t* const translated_strings[] = {u8"Hello", // English
                                             u8"¿Qué tal?", // Spanish
                                             u8"Halløj", // Danish
                                             u8"こんにちは", // Japanese
                                             // The following are taken from Markus Kuhn's UTF-8 stress test file
                                             u8"\x80", // First continuation byte
                                             u8"\xBF", // Last continuation byte
                                             u8"\xC0 ", // 2 Byte sequence first byte followed by space
                                             u8"\xE0 ", // 3 Byte sequence first byte followed by space
                                             u8"\xC0", // 8: 2 Byte sequence with last byte missing
                                             u8"\xF0\x80\x80", // 4 Byte sequence with last byte missing
                                             u8"\xFE", // Impossible byte
                                             u8"\xFF", // Impossible byte
                                             u8"\xC0\xAF", // Overlong sequence
                                             u8"\xF0\x80\x80\xAF", // Overlong sequence
                                             u8"\xED\xA0\x80", // Invalid characters
                                             u8""
};

#endif // EXAMPLEDATA_HPP
