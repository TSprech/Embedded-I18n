///**
// * @file Test_GetStringInvalid.cpp
// * @author TSprech
// * @date 2022/04/17
// * @copyright ©, 2022, TSprech - Apache License 2.0
// * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// * @bug The FirstNByteSequence loops result in premature exit of testing
// * LastSequences fails with invalid code point
// * ImpossibleBytes causes premature test framework exit
// * OverlongMax fails with insufficient room error
// */
//
//#include "E-I18n/GetString.hpp"
//#include "E-I18n/utfcppAdapted.hpp"
//#include "UTF8StressTest.hpp"
//#include "gtest/gtest.h"
//
//// TODO: Get other cases working - currently all error codes are able to be invoked, the main goal of these tests
//
//const uint8_t valid_byte_length_of_longest_code_point = 4;
//
//#define LOOP_TEST_ERROR_STRINGS(string_array, expected_error)                                                             \
//  for (int index = 0; index < valid_byte_length_of_longest_code_point; ++index) {                           \
//    std::u32string utf32_str;                                                                               \
//    auto err = ei18n::GetString(utf32_str, string_array, index); \
//    EXPECT_EQ(err, expected_error); }
//
//TEST(GetStringInvalid, FirstSequences) {
//  LOOP_TEST_ERROR_STRINGS(utf8stress::first_possible_sequence_of_a_certain_length, ei18n::utfcpp::success_)
//}
//
////TEST(GetStringInvalid, LastSequences) {
////  LOOP_TEST_ERROR_STRINGS(utf8stress::last_possible_sequence_of_a_certain_length, ei18n::utfcpp::success_)
////}
//
//TEST(GetStringInvalid, OtherBoundary) {
//  LOOP_TEST_ERROR_STRINGS(utf8stress::other_boundary_conditions, ei18n::utfcpp::success_)
//}
//
//TEST(GetStringInvalid, UnexpectedContinue) {
//  LOOP_TEST_ERROR_STRINGS(utf8stress::unexpected_continuation_bytes, ei18n::utfcpp::invalid_lead_)
//}
//
//TEST(GetStringInvalid, First2ByteSequence) {
//  std::u32string utf32_str;
//  auto err = ei18n::GetString(utf32_str, utf8stress::all_first_2_byte_sequences, 0);
//  EXPECT_EQ(err, ei18n::utfcpp::incomplete_sequence_);
//}
//
//TEST(GetStringInvalid, First3ByteSequence) {
//  std::u32string utf32_str;
//  auto err = ei18n::GetString(utf32_str, utf8stress::all_first_3_byte_sequences, 0);
//  EXPECT_EQ(err, ei18n::utfcpp::incomplete_sequence_);
//}
//
//TEST(GetStringInvalid, First4ByteSequence) {
//  std::u32string utf32_str;
//  auto err = ei18n::GetString(utf32_str, utf8stress::all_first_4_byte_sequences, 0);
//  EXPECT_EQ(err, ei18n::utfcpp::incomplete_sequence_);
//}
//
//TEST(GetStringInvalid, LastContinueByteMissing) {
//  // This set of strings starts at 2 bytes so the regular loop would go to 5 bytes
//  for (int index = 0; index < valid_byte_length_of_longest_code_point - 1; ++index) {
//    std::u32string utf32_str;
//    auto err = ei18n::GetString(utf32_str, utf8stress::last_continuation_byte_missing, index);
//    EXPECT_EQ(err, ei18n::utfcpp::insufficient_room_);
//  }
//
//  for (int index = 5; index < valid_byte_length_of_longest_code_point - 1 + 5; ++index) {
//    std::u32string utf32_str;
//    auto err = ei18n::GetString(utf32_str, utf8stress::last_continuation_byte_missing, index);
//    EXPECT_EQ(err, ei18n::utfcpp::insufficient_room_);
//  }
//}
//
////TEST(GetStringInvalid, ImpossibleBytes) {
////  LOOP_TEST_ERROR_STRINGS(utf8stress::impossible_bytes, ei18n::utfcpp::invalid_lead_)
////}
//
//TEST(GetStringInvalid, OverlongASCII) {
//  LOOP_TEST_ERROR_STRINGS(utf8stress::overlong_ascii_character, ei18n::utfcpp::overlong_sequence_)
//}
//
////TEST(GetStringInvalid, OverlongMax) {
////  // This set of strings starts at 2 bytes so the regular loop would go to 5 bytes
////  for (int index = 0; index < valid_byte_length_of_longest_code_point - 2; ++index) {
////    std::u32string utf32_str;
////    auto err = ei18n::GetString(utf32_str, utf8stress::maximum_overlong_sequences, index);
////    EXPECT_EQ(err, ei18n::utfcpp::overlong_sequence_);
////  }
////}
//
//TEST(GetStringInvalid, OverlongNul) {
//  // This set of strings starts at 2 bytes so the regular loop would go to 5 bytes
//  for (int index = 0; index < valid_byte_length_of_longest_code_point - 1; ++index) {
//    std::u32string utf32_str;
//    auto err = ei18n::GetString(utf32_str, utf8stress::overlong_nul_character, index);
//    EXPECT_EQ(err, ei18n::utfcpp::overlong_sequence_);
//  }
//}
//
//TEST(GetStringInvalid, SingleSurrogates) {
//  LOOP_TEST_ERROR_STRINGS(utf8stress::single_utf16_surrogates, ei18n::utfcpp::invalid_code_point_)
//}
//
//TEST(GetStringInvalid, PairedSurrogates) {
//  LOOP_TEST_ERROR_STRINGS(utf8stress::paired_utf16_surrogates, ei18n::utfcpp::invalid_code_point_)
//}