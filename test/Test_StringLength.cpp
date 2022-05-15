/**
 * @file Test_StringLength.cpp
 * @author TSprech
 * @date 2022/05/15
 * @copyright ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#include "ExampleData.hpp"
#include "E-I18n/GetString.hpp"

static_assert(ei18n::utfcpp::length(hello_translated.at(0)) == 5);
static_assert(ei18n::utfcpp::length(hello_translated.at(1)) == 9);
static_assert(ei18n::utfcpp::length(hello_translated.at(2)) == 6);
static_assert(ei18n::utfcpp::length(hello_translated.at(3)) == 5);

static_assert(ei18n::utfcpp::length(goodbye_translated.at(0)) == 7);
static_assert(ei18n::utfcpp::length(goodbye_translated.at(1)) == 5);
static_assert(ei18n::utfcpp::length(goodbye_translated.at(2)) == 6);
static_assert(ei18n::utfcpp::length(goodbye_translated.at(3)) == 5);