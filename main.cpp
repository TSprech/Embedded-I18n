/**
 * @file main.cpp
 * @author TSprech
 * @date 2022/04/13
 * @copyright ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#include "gtest/gtest.h"
#include <memory_resource>
#include "E-I18n/GetString.hpp"
#include "E-I18n/ei18n.hpp"
#include "ExampleData.hpp"

constexpr size_t maximum_code_point_byte_length = 4; // The max number of bytes that are used to represent a single code point

int main(int ac, char* av[]) {
//  PMR_NULL_STRING(str, 100);
////  std::u32string str;
//  ei18n::GetString(str, translated_strings, 3);
//
//  for (auto& data : str) {
//    std::cout << (uint32_t) data << std::endl;
//  }

  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}