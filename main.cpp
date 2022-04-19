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
#include <E-I18n/GetString.hpp>
#include "ExampleData.hpp"

int main(int ac, char* av[]) {
  std::array<uint8_t, 32> utf8_buffer{};
  std::pmr::monotonic_buffer_resource buffer_mem_res(utf8_buffer.data(), utf8_buffer.size(), std::pmr::null_memory_resource());
  std::pmr::u32string str(&buffer_mem_res);

  ei18n::GetString(str, translated_strings, 3);

//  testing::InitGoogleTest(&ac, av);
//  return RUN_ALL_TESTS();
}