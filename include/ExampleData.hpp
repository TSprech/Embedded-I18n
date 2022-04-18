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

const char8_t* const translated_strings[] = {
    u8"Hello",       // English
    u8"¿Qué tal?",   // Spanish
    u8"Halløj",      // Danish
    u8"こんにちは",  // Japanese
};

#endif  // EXAMPLEDATA_HPP
