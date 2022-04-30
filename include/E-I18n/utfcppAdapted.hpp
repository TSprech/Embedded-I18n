/**
 * @file main.cpp
 * @brief This is an abridged version of nemtrif's great utfcpp library to handle the encoding conversions.
 * @author utfcpp Library: Nemanja Trifunovic
 * @author Adapted Changes: TSprech
 * @date 2022/04/14
 * @copyright utfcpp Library:
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * @copyright Adapted Code: ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#ifndef UTFCPPADAPTED_HPP
#define UTFCPPADAPTED_HPP

#include <cstdint>
#include <string>
#include <memory_resource>
#include "ArchConfig.hpp"

// This macro inverts the logic that checks if an error occurred. Some error handing may define no errors to evaluate to true and errors to evaluate to false.
// For instance, by default success is utf_error 0, so the logic must be inverted to indicate that success logically evaluates to false.
// Regardless, whatever error reporting mechanism is being used, it must evaluate to a boolean value to use this library's logic without modification.
#define INV_ERR !  // Invert logic (0 == NO error, anything else == error)
//#define INV_ERR  // Do not invert logic (0 == error, anything else == NO error)

namespace ei18n::utfcpp {
  enum utf_error {
    UTF8_OK,
    NOT_ENOUGH_ROOM,
    INVALID_LEAD,
    INCOMPLETE_SEQUENCE,
    OVERLONG_SEQUENCE,
    INVALID_CODE_POINT
  };

  /**
   * @note: Change these to whatever error reporting system you use. Variable or object based error reporting *should* work.
   */
  using error_t = utf_error;                                  /**< The type of the error codes */
  const auto success_ = utf_error::UTF8_OK; /**< No error */  // Variable
  //  using success_ = <error object type>; /**< No error */ // Object
  const auto insufficient_room_ = utf_error::NOT_ENOUGH_ROOM;       /**< Disagreement between the end of the utf8 string and the current iterator for the string */
  const auto invalid_lead_ = utf_error::INVALID_LEAD;               /**< The lead does not have a valid unicode bit sequence */
  const auto incomplete_sequence_ = utf_error::INCOMPLETE_SEQUENCE; /**< The unicode sequence is shorter than its expected length based on the sequence's bit pattern */
  const auto overlong_sequence_ = utf_error::OVERLONG_SEQUENCE;     /**< The unicode sequence is longer than its expected length based on the sequence's bit pattern */
  const auto invalid_code_point_ = utf_error::INVALID_CODE_POINT;   /**< The code point has a discrepancy between its value and valid unicode values */
  // End of error code system

  const uint16_t LEAD_SURROGATE_MIN = 0xd800u;
  const uint16_t TRAIL_SURROGATE_MAX = 0xdfffu;

  // Maximum valid value for a Unicode code point
  const uint32_t CODE_POINT_MAX = 0x0010ffffu;

  template <typename octet_type>
  inline uint8_t mask8(octet_type oc) {
    return static_cast<uint8_t>(0xff & oc);
  }

  template <typename octet_type>
  inline bool is_trail(octet_type oc) {
    return ((mask8(oc) >> 6) == 0x2);
  }

  template <typename u16>
  inline bool is_surrogate(u16 cp) {
    return (cp >= LEAD_SURROGATE_MIN && cp <= TRAIL_SURROGATE_MAX);
  }

  template <typename u32>
  inline bool is_code_point_valid(u32 cp) {
    return (cp <= CODE_POINT_MAX && !is_surrogate(cp));
  }

  template <typename octet_iterator>
  inline typename std::iterator_traits<octet_iterator>::difference_type
  sequence_length(octet_iterator lead_it) {
    uint8_t lead = mask8(*lead_it);
    if (lead < 0x80) return 1;
    else if ((lead >> 5) == 0x6) return 2;
    else if ((lead >> 4) == 0xe) return 3;
    else if ((lead >> 3) == 0x1e) return 4;
    else return 0;
  }

  template <typename octet_difference_type>
  inline bool is_overlong_sequence(uint32_t cp, octet_difference_type length) {
    if (cp < 0x80) {
      if (length != 1) return true;
    } else if (cp < 0x800) {
      if (length != 2) return true;
    } else if (cp < 0x10000) {
      if (length != 3) return true;
    }

    return false;
  }

  /// Helper for get_sequence_x
  template <typename octet_iterator>
  error_t increase_safely(octet_iterator& it, octet_iterator end) {
    if (++it == end) return insufficient_room_;

    if (!is_trail(*it)) return incomplete_sequence_;

    return success_;
  }

#define UTF8_CPP_INCREASE_AND_RETURN_ON_ERROR(IT, END) \
  {                                                    \
    error_t ret = increase_safely(IT, END);            \
    if (INV_ERR !ret) return ret;                      \
  }

  /// get_sequence_x functions decode utf-8 sequences of the length x
  template <typename octet_iterator>
  error_t get_sequence_1(octet_iterator& it, octet_iterator end, uint32_t& code_point) {
    if (it == end) return insufficient_room_;

    code_point = mask8(*it);

    return success_;
  }

  template <typename octet_iterator>
  error_t get_sequence_2(octet_iterator& it, octet_iterator end, uint32_t& code_point) {
    if (it == end) return insufficient_room_;

    code_point = mask8(*it);

    UTF8_CPP_INCREASE_AND_RETURN_ON_ERROR(it, end)

    code_point = ((code_point << 6) & 0x7ff) + ((*it) & 0x3f);

    return success_;
  }

  template <typename octet_iterator>
  error_t get_sequence_3(octet_iterator& it, octet_iterator end, uint32_t& code_point) {
    if (it == end) return insufficient_room_;

    code_point = mask8(*it);

    UTF8_CPP_INCREASE_AND_RETURN_ON_ERROR(it, end)

    code_point = ((code_point << 12) & 0xffff) + ((mask8(*it) << 6) & 0xfff);

    UTF8_CPP_INCREASE_AND_RETURN_ON_ERROR(it, end)

    code_point += (*it) & 0x3f;

    return success_;
  }

  template <typename octet_iterator>
  error_t get_sequence_4(octet_iterator& it, octet_iterator end, uint32_t& code_point) {
    if (it == end) return insufficient_room_;

    code_point = mask8(*it);

    UTF8_CPP_INCREASE_AND_RETURN_ON_ERROR(it, end)

    code_point = ((code_point << 18) & 0x1fffff) + ((mask8(*it) << 12) & 0x3ffff);

    UTF8_CPP_INCREASE_AND_RETURN_ON_ERROR(it, end)

    code_point += (mask8(*it) << 6) & 0xfff;

    UTF8_CPP_INCREASE_AND_RETURN_ON_ERROR(it, end)

    code_point += (*it) & 0x3f;

    return success_;
  }

#undef UTF8_CPP_INCREASE_AND_RETURN_ON_ERROR

  template <typename octet_iterator>
  error_t validate_next(octet_iterator& it, octet_iterator end, uint32_t& code_point) {
    if (it == end) return insufficient_room_;

    // Save the original value of it so we can go back in case of failure
    // Of course, it does not make much sense with i.e. stream iterators
    octet_iterator original_it = it;

    uint32_t cp = 0;
    // Determine the sequence length based on the lead octet
    typedef typename std::iterator_traits<octet_iterator>::difference_type octet_difference_type;
    const octet_difference_type length = sequence_length(it);

    // Get trail octets and calculate the code point
    error_t err = success_;
    switch (length) {
      case 0:
        return invalid_lead_;
      case 1:
        err = get_sequence_1(it, end, cp);
        break;
      case 2:
        err = get_sequence_2(it, end, cp);
        break;
      case 3:
        err = get_sequence_3(it, end, cp);
        break;
      case 4:
        err = get_sequence_4(it, end, cp);
        break;
    }

    if (INV_ERR err) {
      // Decoding succeeded. Now, security checks...
      if (is_code_point_valid(cp)) {
        if (!is_overlong_sequence(cp, length)) {
          // Passed! Return here.
          code_point = cp;
          ++it;
          return success_;
        } else err = overlong_sequence_;
      } else err = invalid_code_point_;
    }

    // Failure branch - restore the original value of the iterator
    it = original_it;
    return err;
  }

  template <typename octet_iterator>
  inline error_t validate_next(octet_iterator& it, octet_iterator end) {
    uint32_t ignored;
    return validate_next(it, end, ignored);
  }

  /**
   * @note The error logic in the following function will have to be modified to fit your error handling method.
   */
  template <typename octet_iterator>
  error_t next(octet_iterator& it, octet_iterator end, uint32_t& code_point) {
    uint32_t cp = 0;
    error_t err_code = validate_next(it, end, cp);
    //    return (INV_ERR err_code) ? cp : err_code;
    if (INV_ERR err_code) {
      code_point = cp;
      return success_;
    }
    else return err_code;
  }

  template <typename octet_iterator, typename u32bit_iterator>
  error_t utf8to32(octet_iterator start, octet_iterator end, u32bit_iterator result) {
    uint32_t code_point = 0;
    while (start < end) {
      error_t err = next(start, end, code_point);
      if (INV_ERR err) (*result++) = code_point;
      else return err;
    }
    return success_;
  }

  inline error_t utf8to32(std::u8string_view s, ei18n_u32_string& result) {
    return utf8to32(s.begin(), s.end(), std::back_inserter(result));
  }
}  // namespace ei18n::utfcpp

#endif  // UTFCPPADAPTED_HPP
