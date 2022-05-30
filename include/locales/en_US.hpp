//
// Created by treys on 5/24/2022.
//

#ifndef EN_US_HPP
#define EN_US_HPP

#include "E-I18n/ei18n.hpp"
using namespace ei18n::literals::string_view_literals;

std::tuple en_US {
  u8"“"_sv8,
  u8"”"_sv8,
  u8"‘"_sv8,
  u8"’"_sv8,
  u8"."_sv8,
  u8","_sv8,
  u8";"_sv8,
  u8"%"_sv8,
  u8"+"_sv8,
  u8"-"_sv8,
  u8"E"_sv8,
  u8"×"_sv8,
  u8"∞"_sv8,
  u8"NaN"_sv8,
  std::array{u8"Sun"_sv8,
             u8"Mon"_sv8,
             u8"Tue"_sv8,
             u8"Wed"_sv8,
             u8"Thu"_sv8,
             u8"Fri"_sv8,
             u8"Sat"_sv8},
  u8"AM"_sv8,
  u8"PM"_sv8,
  u8"h:mm:ss a"_sv8,
  u8"h:mm a"_sv8
};

#endif  // EN_US_HPP
