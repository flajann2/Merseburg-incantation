#include <iostream>
#include <merseberg>
#include "gtest/gtest.h"
namespace {
  using namespace merseberg;
  
  TEST(incantation, basic_test) {
    auto container = std::vector<int>{1, 1, 2, 3, 5, 8, 13};
    auto func = []() {};
    auto imp = incantation(container, );
  }
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
