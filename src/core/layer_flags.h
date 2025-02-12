#pragma once

namespace core {
  enum class LAYER_FLAG {
    NONE     = 1 << 0,
    EDITABLE = 1 << 1,
    VISIBLE  = 1 << 2,
  };
}
