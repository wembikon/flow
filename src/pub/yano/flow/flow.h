/**
 * Copyright (C) 2019 Adrian T Visarra
 */

#pragma once

#include <system_error>
#include <type_traits>

namespace yano {

class FlowOption {
 public:
  FlowOption() = default;
  FlowOption(std::error_code ec) : _ec(ec) {}
  std::error_code ec() const { return _ec; }

  template <typename HappyPath, typename = std::enable_if_t<std::is_convertible_v<
                                    std::invoke_result_t<HappyPath>, FlowOption>>>
  FlowOption operator|(HappyPath hpath) const {
    if (_ec) {
      return _ec;
    }
    return hpath();
  }

  std::error_code operator|(std::error_code) const { return _ec; }

 private:
  std::error_code _ec;
};

}  // namespace yano