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

#define CHECK_SUCCESS(lang)                                         \
  std::u32string utf32_str;                                         \
  auto err = ei18n::GetString(utf32_str, translated_strings, lang); \
  EXPECT_EQ(err, ei18n::utfcpp::success_)

namespace {
  TEST(GetStringTest, Default) {
    std::u32string utf32_str;
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

  // TODO: Refine UTF8 error testing
#define QUICK_ERROR_MACRO(num, error)                                          \
  std::u32string utf32_str;                                        \
  auto err = ei18n::GetString(utf32_str, translated_strings, num); \
  EXPECT_EQ(err, error)

  TEST(GetStringTest, 4) {
    QUICK_ERROR_MACRO(4, ei18n::utfcpp::invalid_lead_); // 2
  }

  TEST(GetStringTest, 5) {
    QUICK_ERROR_MACRO(5, ei18n::utfcpp::invalid_lead_); // 2
  }

  TEST(GetStringTest, 6) {
    QUICK_ERROR_MACRO(6, ei18n::utfcpp::incomplete_sequence_); // 3
  }

  TEST(GetStringTest, 7) {
    QUICK_ERROR_MACRO(7, ei18n::utfcpp::incomplete_sequence_); // 3
  }

  TEST(GetStringTest, 8) {
    QUICK_ERROR_MACRO(8, ei18n::utfcpp::insufficient_room_); // 1
  }

  TEST(GetStringTest, 9) {
    QUICK_ERROR_MACRO(9, ei18n::utfcpp::insufficient_room_); // 1
  }

  TEST(GetStringTest, 10) {
    QUICK_ERROR_MACRO(10, ei18n::utfcpp::invalid_lead_); // 2
  }

  TEST(GetStringTest, 11) {
    QUICK_ERROR_MACRO(11, ei18n::utfcpp::invalid_lead_); // 2
  }

  TEST(GetStringTest, 12) {
    QUICK_ERROR_MACRO(12, ei18n::utfcpp::overlong_sequence_); // 4
  }

  TEST(GetStringTest, 13) {
    QUICK_ERROR_MACRO(13, ei18n::utfcpp::overlong_sequence_); // 4
  }

  TEST(GetStringTest, 14) {
    QUICK_ERROR_MACRO(14, ei18n::utfcpp::invalid_code_point_); // 5
  }
}  // namespace