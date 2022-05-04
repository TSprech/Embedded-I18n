/**
 * @file main.cpp
 * @author TSprech
 * @date 2022/04/13
 * @copyright ©, 2022, TSprech - Apache License 2.0
 * @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * @bug None (yet)
 */

#include "gtest/gtest.h"

int main(int ac, char* av[]) {
  ///TRANSLATOR: This is the first comment
  ///PARSER: This is under the first comment, before the second comment
  std::string first_string = gettext("This is the first string");
  //#. This is the second comment
  std::string second_string = gettext(this_is_second);
  // This shouldn't be written
  // Nor should this. Or this. Even this.
  std::string third_string = gettext("This is the third string");
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}