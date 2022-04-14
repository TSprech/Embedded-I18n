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
  Danish
};

const char8_t* const translated_strings[] = {u8"Hello", u8"¿Qué tal?", u8"Halløj"};

#endif // EXAMPLEDATA_HPP
