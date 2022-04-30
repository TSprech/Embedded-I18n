/**
 * @file GetString.hpp
 * @author TSprech
 * @date 2022/04/29
 * @copyright ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#ifndef EI18N_HPP
#define EI18N_HPP

#include <string>
#include <memory_resource>
#include "ArchConfig.hpp"

#define PMR_NULL_STRING(pmr_string_name_, buffer_size_)                                                                                                                                   \
  std::array<uint8_t, buffer_size_> pmr_string_name_##_buffer_{0};                                                                                                                        \
  std::pmr::monotonic_buffer_resource pmr_string_name_##_buffer_memory_resource_(pmr_string_name_##_buffer_.data(), pmr_string_name_##_buffer_.size(), std::pmr::null_memory_resource()); \
  ei18n_u32_string pmr_string_name_(&pmr_string_name_##_buffer_memory_resource_)

#endif  // EI18N_HPP
