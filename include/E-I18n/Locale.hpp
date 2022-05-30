//
// Created by treys on 5/22/2022.
//

#ifndef LOCALE_HPP
#define LOCALE_HPP

#include "ei18n.hpp"

using namespace ei18n::literals::string_view_literals;

#include "Languages.hpp"

struct Locale {
  static Languages lang;
  static constexpr std::u8string_view comma;
  static constexpr std::u8string_view decimal;
};

enum Data_Order {
  language,
  decimal,
  comma
};

constexpr std::tuple tup = {
    Languages::English,
    u8"."_sv8,
    u8","_sv8};

static_assert(std::get<decimal>(tup) == u8"."_sv8);

#endif  // LOCALE_HPP
