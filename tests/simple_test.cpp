#include <atomic>
#include <iostream>
#include <merseberg>
#include "gtest/gtest.h"

namespace {
  using namespace merseberg;
  using namespace std;

  TEST(incantation, basic_test) {
    auto container = std::vector<int>{};
    for (int i = 0; i < 1024; ++i) {
      container.push_back(i);
    }

    std::atomic<int> sum = 0;

    auto sigma = [&sum](auto begin, auto end) {
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
    auto cocurrent = imp([](auto res) {
      int s = 0;
      for (auto a : res) {
        s += a;
      }
      return s;
    });
    cout << "*** thread count is " << imp.threads() << endl;
    EXPECT_EQ(single, cocurrent);    
  }
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
