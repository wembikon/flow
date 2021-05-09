/**
 * Copyright (C) 2019 Adrian T Visarra
 */

#pragma once

#include <system_error>
#include <type_traits>

namespace yano {

class Flow final {
 public:
  Flow() = default;
  Flow(std::error_code ec) : _ec(ec) {}
  inline std::error_code ec() const { return _ec; }

  template <typename HappyPath, typename = std::enable_if_t<
                                    std::is_convertible_v<std::invoke_result_t<HappyPath>, Flow>>>
  Flow operator|(HappyPath hpath) const {
    if (_ec) {
      return _ec;
    }
    return hpath();
  }

  inline std::error_code operator|(std::error_code) const { return _ec; }

 private:
  std::error_code _ec;
};

}  // namespace yano