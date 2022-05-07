/**
 * @file Test_Eternal.cpp
 * @brief The tests for mapbox's eternal library.
 * @author eternal Tests: Mapbox
 * @author Adapted Changes: TSprech
 * @date 2022/05/06
 * @copyright mapbox Library:
 * ISC License
 * Copyright (c) 2018, Mapbox
 * Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby
 * granted, provided that the above copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL,
 * DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE
 * USE OR PERFORMANCE OF THIS SOFTWARE.
 * @copyright Adapted Code: ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#include "EternalTestData.hpp"
#include "gtest/gtest.h"

constexpr auto colors = eternal::map<eternal::string, Color>({COLORS});

constexpr auto multi_colors = eternal::map<eternal::string, Color>({
    {"red", {255, 0, 0, 1}},
    {"yellow", {255, 255, 0, 1}},
    {"white", {255, 255, 255, 1}},  // comes before yellow!
    {"yellow", {255, 220, 0, 1}},   // a darker yellow
});

constexpr auto hash_colors = eternal::hash_map<eternal::string, Color>({
    {"red", {255, 0, 0, 1}},
    {"yellow", {255, 255, 0, 1}},
    {"yellow", {255, 220, 0, 1}},  // a darker yellow
    {"white", {255, 255, 255, 1}},
});

#define CONSTEXPR_ASSERT(value, str) static_assert(value); ASSERT_TRUE(value) << str

TEST(Eternal, FullTest) {
  CONSTEXPR_ASSERT(colors.unique(), "multi_colors are not unique");
  CONSTEXPR_ASSERT(colors.find("beige") != colors.end(), "colors contains beige");
  CONSTEXPR_ASSERT(colors.find("beige")->second == Color(245, 245, 220, 1), "beige returns the correct color");
  CONSTEXPR_ASSERT(colors.find("blackquoise") == colors.end(), "blackquoise is not a color");
  CONSTEXPR_ASSERT(colors.count("beige") == 1, "beige is found once");
  CONSTEXPR_ASSERT(colors.count("blackquoise") == 0, "blackquoise is not found");
  CONSTEXPR_ASSERT(colors.contains("beige") == true, "beige is not found");
  CONSTEXPR_ASSERT(colors.contains("blackquoise") == false, "blackquoise is not found");

  CONSTEXPR_ASSERT(!multi_colors.unique(), "multi_colors are not unique");
  CONSTEXPR_ASSERT(multi_colors.find("yellow") != multi_colors.end(), "colors contains yellow");
  CONSTEXPR_ASSERT(multi_colors.find("yellow")->second == Color(255, 255, 0, 1), "yellow returns the correct color");
  CONSTEXPR_ASSERT((++multi_colors.find("yellow"))->second == Color(255, 220, 0, 1), "yellow returns the correct color");
  CONSTEXPR_ASSERT(multi_colors.equal_range("white").first == multi_colors.find("white"), "white range returns the correct begin");
  CONSTEXPR_ASSERT(multi_colors.equal_range("white").second == multi_colors.find("yellow"), "white range end is the next color");
  CONSTEXPR_ASSERT(multi_colors.equal_range("yellow").first == multi_colors.find("yellow"), "yellow range returns the correct begin");
  CONSTEXPR_ASSERT(multi_colors.equal_range("yellow").second == multi_colors.end(), "yellow range end returns end");
  CONSTEXPR_ASSERT(multi_colors.count("yellow") == 2, "has 2 yellows");

  CONSTEXPR_ASSERT(hash_colors.size() == 4, "hash_colors has 4 elements");
  CONSTEXPR_ASSERT(!hash_colors.unique(), "hash_colors are not unique");
  CONSTEXPR_ASSERT(hash_colors.find("yellow") != hash_colors.end(), "colors contains yellow");
  CONSTEXPR_ASSERT(hash_colors.find("yellow")->second == Color(255, 255, 0, 1), "yellow returns the correct color");
  CONSTEXPR_ASSERT((++hash_colors.find("yellow"))->second == Color(255, 220, 0, 1), "yellow returns the correct color");
  CONSTEXPR_ASSERT(hash_colors.equal_range("white").first == hash_colors.find("white"), "white range returns the correct begin");
  CONSTEXPR_ASSERT(hash_colors.equal_range("yellow").first == hash_colors.find("yellow"), "yellow range returns the correct begin");
  CONSTEXPR_ASSERT(hash_colors.count("yellow") == 2, "has 2 yellows");

  // Can use range-for
  for (auto& x : colors) {
    (void) x;
  }

  // Can use range-for over equal_range
  for (auto range = multi_colors.equal_range("yellow"); range.first != range.second; ++range.first) {
    (void) range;
  }
}
