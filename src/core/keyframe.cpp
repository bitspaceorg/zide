#include "keyframe.h"
#include <cassert>

// clang-format off
namespace core {
KeyFrame::KeyFrame(uint32_t width, uint32_t height) : m_width(width), m_height(height) {}

uint32_t  KeyFrame::getWidth()  const { return m_width; }
uint32_t  KeyFrame::getHeight() const { return m_height; }
bool      KeyFrame::isEmpty()   const { return 0; } // TODO

uint32_t  KeyFrame::getIndex(uint32_t w, uint32_t h) const {
  assert(w < m_width && h < m_height); // Boundary Check
  return h * m_width + w;
}
Color KeyFrame::getPixel(uint32_t w, uint32_t h) const {
  return m_grid[getIndex(w, h)];
}

void KeyFrame::resize(uint32_t width, uint32_t height) {
  // New container to store the resized grid
  std::vector<Color> ngrid(width * height);
  for (size_t y = 0; y < std::min(height, m_height); y++) {
    for (size_t x = 0; x < std::min(width, m_width); x++) {
      // Copy the previous values to the new grid
      ngrid[y * width + x] = m_grid[y * m_width + x];
    }
  }
  // Moving the new grid back to the previous one
  m_grid = std::move(ngrid);
  // Set the new width and height of the grid
  m_width = width, m_height = height;
}

void KeyFrame::clear(Color clr) {
  for (size_t i = 0; i < m_width * m_height; ++i) {
    m_grid[i] = clr;
  }
}

bool KeyFrame::setPixel(uint32_t x, uint32_t y, Color clr) {
  bool same = clr == getPixel(x, y);
  m_grid[getIndex(x, y)] = clr;
  return same;
}

KeyFrame::~KeyFrame() {}
} // namespace core
