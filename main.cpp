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

int main() {
  std::cout << reinterpret_cast<const char*>(GetString(translated_strings)) << std::endl;
  std::cout << reinterpret_cast<const char*>(GetString(translated_strings, Languages::Spanish)) << std::endl;
  std::cout << reinterpret_cast<const char*>(GetString(translated_strings, Languages::Danish)) << std::endl;
  return 0;
}