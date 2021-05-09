#include "gtest/gtest.h"

#include "yano/flow/flow.h"

#include <stdexcept>
#include <string>

namespace {

class A {
 public:
  std::error_code ok1() {
    _flow += "ok1";
    return {};
  }
  std::error_code ok2() {
    _flow += "ok2";
    return {};
  }
  std::error_code error1() {
    _flow += "error1";
    return std::make_error_code(std::errc::io_error);
  }
  std::error_code error2() {
    _flow += "error2";
    try {
      throw std::exception();
    } catch (...) {
      return std::make_error_code(std::errc::invalid_argument);
    }
    return std::make_error_code(std::errc::io_error);
  }

  std::string check() const { return _flow; }

 private:
  std::string _flow;
};

}  // namespace

TEST(flow_test, no_error) {
  A a;
  const auto ec = yano::Flow(a.ok1()) | [&] { return a.ok2(); } | std::error_code();
  EXPECT_EQ(a.check(), "ok1ok2");
  EXPECT_EQ(ec, std::error_code());
}

TEST(flow_test, error_at_the_beginning) {
  A a;
  const auto ec = yano::Flow(a.error1()) | [&] { return a.ok1(); } | [&] { return a.ok2(); } |
                  std::error_code();
  EXPECT_EQ(a.check(), "error1");
  EXPECT_EQ(ec, std::errc::io_error);
}

TEST(flow_test, error_in_the_middle) {
  A a;
  const auto ec = yano::Flow(a.ok1()) | [&] { return a.error2(); } | [&] { return a.ok2(); } |
                  std::error_code();
  EXPECT_EQ(ec, std::errc::invalid_argument);
  EXPECT_EQ(a.check(), "ok1error2");
}

TEST(flow_test, error_at_the_end) {
  A a;
  const auto ec = yano::Flow(a.ok1()) | [&] { return a.ok2(); } | [&] { return a.error2(); } |
                  std::error_code();
  EXPECT_EQ(a.check(), "ok1ok2error2");
  EXPECT_EQ(ec, std::errc::invalid_argument);
}