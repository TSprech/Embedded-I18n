//
// Created by treys on 5/24/2022.
//

#ifndef DA_DK_HPP
#define DA_DK_HPP

#include "E-I18n/ei18n.hpp"
using namespace ei18n::literals::string_view_literals;

std::tuple da_DK {
  u8"“"_sv8,
      u8"”"_sv8,
      u8"‘"_sv8,
      u8"’"_sv8,
      u8","_sv8,
      u8"."_sv8,
      u8";"_sv8,
      u8"%"_sv8,
      u8"+"_sv8,
      u8"-"_sv8,
      u8"E"_sv8,
      u8"×"_sv8,
      u8"∞"_sv8,
      u8"NaN"_sv8,
      std::array{u8"søn."_sv8,
                 u8"man."_sv8,
                 u8"tir."_sv8,
                 u8"ons."_sv8,
                 u8"tor."_sv8,
                 u8"fre."_sv8,
                 u8"lør."_sv8},
      u8"AM"_sv8,
      u8"PM"_sv8,
      u8"HH.mm.ss"_sv8,
      u8"HH.mm"_sv8
};

#endif  // DA_DK_HPP
