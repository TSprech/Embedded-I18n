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
  //#. E18_MAP: main_map_name
  //#. TRANSLATOR: This is the first comment
  //#. E18_ARR: hello_array
  std::string first_string = gettext("Hello");
  //#. This is the comment for "Goodbye"
  std::string second_string = gettext("Goodbye");
  // This shouldn't be written
  // Nor should this. Or this. Even this.
  std::string third_string = ("This is the third string");
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}