#include <atomic>
#include <iostream>
#include <merseberg>
#include "gtest/gtest.h"

namespace {
  using namespace merseberg;
  using namespace std;

  TEST(incantation, basic_test) {
    auto container = std::vector<int>{};
    for (int i = 0; i < 117; ++i) {
      container.push_back(i);
    }

    auto sigma = [](auto begin, auto end) {
      int sum = 0;
      for (auto pi = begin; pi != end; ++pi) {
        sum += *pi;
      }
      return static_cast<int>(sum);
    };

    // single threaded operation
    auto single = sigma(container.begin(), container.end());
    cout << "*** single = " << single << endl;

    auto imp = incantation(container);
    imp.invoke(sigma);
    imp.join();
    auto concurrent = imp([](auto res) {
      int s = 0;
      for (auto a : res) {
        s += a;
      }
      return s;
    });
    EXPECT_EQ(single, concurrent);    
  }
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
