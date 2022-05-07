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

#include <array>
#include <cstdint>
#include <string_view>

#include "E-I18n/eternalAdapted.hpp"

enum class Languages : uint16_t {
  English = 0,
  Spanish,
  Danish,
  Japanese
};

inline constexpr std::basic_string_view<char8_t>
operator""_sv8(const char8_t* str, size_t len) noexcept {
  return std::basic_string_view<char8_t>{str, len};
}

using namespace std::literals::string_view_literals;

constexpr std::array hello_translated = {
    u8"Hello"_sv8,      // English
    u8"¿Qué tal?"_sv8,  // Spanish
    u8"Halløj"_sv8,     // Danish
    u8"こんにちは"_sv8  // Japanese
};

constexpr std::array goodbye_translated = {
    u8"Goodbye"_sv8,      // English
    u8"Adiós"_sv8,  // Spanish
    u8"Farvel"_sv8,     // Danish
    u8"さようなら"_sv8  // Japanese
};

constexpr auto ExampleData_map = eternal::map<eternal::u8string, std::array<std::basic_string_view<char8_t>, 4>> ({
    {hello_translated.at(0), hello_translated},
    {goodbye_translated.at(0), goodbye_translated}
});


#endif  // EXAMPLEDATA_HPP
