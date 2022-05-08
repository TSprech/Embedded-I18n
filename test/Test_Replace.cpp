//
// Created by treys on 5/8/2022.
//

#include <gtest/gtest.h>
#include <E-I18n/utfcppAdapted.hpp>
#include <ExampleData.hpp>

namespace {
  TEST(Replace1StringPMR, English) {
    PMR_NULL_STRING(utf32_str, 100);
    ei18n::utfcpp::utf8to32_replace(hello_translated[0], utf32_str, {{U'H', U'Y'}});
    EXPECT_EQ(utf32_str, U"\x59\x65\x6c\x6c\x6f") << "Unable to retrieve string from English language";
  }

  TEST(Replace2StringPMR, English) {
    PMR_NULL_STRING(utf32_str, 100);
    ei18n::utfcpp::utf8to32_replace(hello_translated[0], utf32_str, {{U'H', U'Y'}, {U'l', U'ん'}});
    EXPECT_EQ(utf32_str, U"\x59\x65\x3093\x3093\x6f") << "Unable to retrieve string from English language";
  }
}