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

#define MAP_NAME(name) name##_map

int main(int ac, char* av[]) {
//  std::cout << ei18n::utfcpp::distance(hello_translated.at(3).data(), hello_translated.at(3).data() + hello_translated.at(3).size());
  std::cout << ei18n::utfcpp::length(hello_translated.at(3));
  constexpr auto val = ei18n::GetMap(u8"Hello", MAP_NAME(ExampleData));
  static_assert(val.at(0) == u8"Hello");
  std::u32string str32;
  ei18n::GetString(str32, val, 3);
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}