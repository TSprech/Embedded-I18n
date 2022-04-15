/**
 * @file main.cpp
 * @author TSprech
 * @date 2022/04/13
 * @copyright ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#include "E-I18n/GetString.hpp"
#include "ExampleData.hpp"
#include <iostream>

#include "E-I18n/utfcppAdapted.hpp"

int main() {
  std::cout << reinterpret_cast<const char*>(ei18n::GetString(translated_strings)) << std::endl;
  std::cout << reinterpret_cast<const char*>(ei18n::GetString(translated_strings, Languages::Spanish)) << std::endl;
  std::cout << reinterpret_cast<const char*>(ei18n::GetString(translated_strings, Languages::Danish)) << std::endl;

  std::string_view test_str = reinterpret_cast<const char *>(u8"こんにちは");
  std::u32string string_result = utf8to32(test_str);
  std::cout << string_result.length() << std::endl;
  return 0;
}