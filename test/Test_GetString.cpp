/**
 * @file Test_GetString.cpp
 * @author TSprech
 * @date 2022/04/15
 * @copyright ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#include "E-I18n/GetString.hpp"
#include "E-I18n/utfcppAdapted.hpp"
#include "ExampleData.hpp"
#include "gtest/gtest.h"

namespace {
  TEST(GetStringTest, Default) {
    EXPECT_EQ(ei18n::GetString(translated_strings), U"\x48\x65\x6c\x6c\x6f") << "Unable to retrieve string with no language given";
  }

  TEST(GetStringTest, English) {
    EXPECT_EQ(ei18n::GetString(translated_strings, Languages::English), U"\x48\x65\x6c\x6c\x6f") << "Unable to retrieve string from English language";
  }

  TEST(GetStringTest, Spanish) {
    EXPECT_EQ(ei18n::GetString(translated_strings, Languages::Spanish), U"\xbf\x51\x75\xe9\x20\x74\x61\x6c\x3f") << "Unable to retrieve string from Spanish language";
  }

  TEST(GetStringTest, Danish) {
    EXPECT_EQ(ei18n::GetString(translated_strings, Languages::Danish), U"\x48\x61\x6c\x6c\xf8\x6a") << "Unable to retrieve string from Danish language";
  }

  TEST(GetStringTest, Japanese) {
    EXPECT_EQ(ei18n::GetString(translated_strings, Languages::Japanese), U"\x3053\x3093\x306b\x3061\x306f") << "Unable to retrieve string from Japanese language";
  }
}  // namespace