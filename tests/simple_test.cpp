#include <iostream>
#include <merseberg>
#include "gtest/gtest.h"
namespace {
  using namespace merseberg;
  
  TEST(incantation, basic_test) {

  }
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
