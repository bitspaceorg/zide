#pragma once
#include <cstdint>
// clang-format off
namespace core {
enum class LAYER_FLAG : uint8_t {
  NONE     = 1 << 0,
  EDITABLE = 1 << 1,
  VISIBLE  = 1 << 2,
};
}
