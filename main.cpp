/**
 * @file main.cpp
 * @author TSprech
 * @date 2022/04/13
 * @copyright ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#include "gtest/gtest.h"

#include "ExampleData.hpp"
#include "E-I18n/GetString.hpp"

#include "locales/en_US.hpp"
#include "locales/es_ES.hpp"
#include "locales/da_DK.hpp"
#include "locales/ja_JP.hpp"

#include "E-I18n/TranslationFormatter.hpp"

#define MAP_NAME(name) name##_map

int main(int ac, char* av[]) {
  ei18n::Translatable translatable{};
  std::array arr = {"First", "Second", "Third"};
  std::cout << translatable.Translate(arr) << std::endl;
  translatable.Locale(2);
  std::cout << translatable.Translate(arr) << std::endl;
  translatable.Locale(1);
  std::cout << translatable.Translate(arr) << std::endl;

  std::cout << reinterpret_cast<const char*>(std::get<ei18n::infinity>(en_US).data()) << std::endl;

  constexpr auto val = ei18n::GetMap(u8"Hello", MAP_NAME(ExampleData));
  static_assert(val.at(0) == u8"Hello");
  std::u32string str32;
  ei18n::GetString(str32, val, 3);
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}