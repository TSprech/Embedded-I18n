//
// Created by treys on 5/24/2022.
//

#ifndef ES_ES_HPP
#define ES_ES_HPP

#include "E-I18n/ei18n.hpp"

using namespace ei18n::literals::string_view_literals;

std::tuple es_ES {
  u8"«"_sv8,
      u8"»"_sv8,
      u8"“"_sv8,
      u8"”"_sv8,
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
      std::array{u8"dom"_sv8,
                 u8"lun"_sv8,
                 u8"mar"_sv8,
                 u8"mié"_sv8,
                 u8"jue"_sv8,
                 u8"vie"_sv8,
                 u8"sáb"_sv8},
      u8"a.m."_sv8,
      u8"p.m."_sv8,
      u8"H:mm:ss"_sv8,
      u8"H:mm"_sv8
};

#endif  // ES_ES_HPP
