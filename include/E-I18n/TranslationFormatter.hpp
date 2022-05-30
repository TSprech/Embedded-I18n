//
// Created by treys on 5/22/2022.
//

#ifndef TRANSLATIONFORMATTER_HPP
#define TRANSLATIONFORMATTER_HPP

#include "eternalAdapted.hpp"
#include "usf/usf.hpp"

namespace ei18n {

class Translatable {
 public:
  auto Locale(uint8_t new_locale) -> void {
    locale = new_locale;
  }
  auto Translate(auto translated_array) -> std::string {
    return translated_array.at(locale);
  }
 private:
  uint8_t locale = 0;
};
}

#endif  // TRANSLATIONFORMATTER_HPP
