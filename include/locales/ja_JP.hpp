//
// Created by treys on 5/24/2022.
//

#ifndef JA_JP_HPP
#define JA_JP_HPP

#include "E-I18n/ei18n.hpp"
using namespace ei18n::literals::string_view_literals;
std::tuple ja_JP {
    u8"「"_sv8,
    u8"」"_sv8,
    u8"『"_sv8,
    u8"』"_sv8,
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
    std::array{u8"日"_sv8,
               u8"月"_sv8,
               u8"火"_sv8,
               u8"水"_sv8,
               u8"木"_sv8,
               u8"金"_sv8,
               u8"土"_sv8},
    u8"午前"_sv8,
    u8"午後"_sv8,
    u8"H:mm:ss"_sv8,
    u8"H:mm"_sv8};

#endif  // JA_JP_HPP
