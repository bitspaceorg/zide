#pragma once
#include "color.h"
#include "vector"
#include <cstdint>
// clang-format off
namespace core {
class KeyFrame {
public:
                        KeyFrame(uint32_t width, uint height);
                        ~KeyFrame();

  bool                  isEmpty()                                   const;
  Color                 getPixel(uint32_t x, uint y)                const;
  uint32_t              getWidth()                                  const;
  uint32_t              getHeight()                                 const;
  uint32_t              getIndex(uint x, uint y)                    const;

  void                  clear(Color clr);
  void                  resize(uint32_t width, uint height);
  bool                  setPixel(uint32_t x, uint y, Color clr);

private:
  std::vector<Color>    m_grid;
  uint32_t              m_width, m_height;
};
}; // namespace core
