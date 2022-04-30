/**
 * @file Test_GetString.cpp
 * @author TSprech
 * @date 2022/04/15
 * @copyright ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#include "E-I18n/GetString.hpp"
#include "E-I18n/ei18n.hpp"
#include "ExampleData.hpp"
#include "gtest/gtest.h"

#define CHECK_SUCCESS(lang)                                         \
  PMR_NULL_STRING(utf32_str, 100);                                  \
  auto err = ei18n::GetString(utf32_str, translated_strings, lang); \
  EXPECT_EQ(err, ei18n::utfcpp::success_)

//#define CHECK_SUCCESS(lang)                                         \
//  std::u32string utf32_str;                                         \
//  auto err = ei18n::GetString(utf32_str, translated_strings, lang); \
//  EXPECT_EQ(err, ei18n::utfcpp::success_)

namespace {
  TEST(GetStringTest, Default) {
    PMR_NULL_STRING(utf32_str, 100);
    auto err = ei18n::GetString(utf32_str, translated_strings);
    EXPECT_EQ(err, ei18n::utfcpp::success_);
    EXPECT_EQ(utf32_str, U"\x48\x65\x6c\x6c\x6f") << "Unable to retrieve string with no language given";
  }

  TEST(GetStringTest, English) {
    CHECK_SUCCESS(Languages::English);
    EXPECT_EQ(utf32_str, U"\x48\x65\x6c\x6c\x6f") << "Unable to retrieve string from English language";
  }

  TEST(GetStringTest, Spanish) {
    CHECK_SUCCESS(Languages::Spanish);
    EXPECT_EQ(utf32_str, U"\xbf\x51\x75\xe9\x20\x74\x61\x6c\x3f") << "Unable to retrieve string from Spanish language";
  }

  TEST(GetStringTest, Danish) {
    CHECK_SUCCESS(Languages::Danish);
    EXPECT_EQ(utf32_str, U"\x48\x61\x6c\x6c\xf8\x6a") << "Unable to retrieve string from Danish language";
  }

  TEST(GetStringTest, Japanese) {
    CHECK_SUCCESS(Languages::Japanese);
    EXPECT_EQ(utf32_str, U"\x3053\x3093\x306b\x3061\x306f") << "Unable to retrieve string from Japanese language";
  }
}  // namespace