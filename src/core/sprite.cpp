#include "sprite.h"

namespace core {
Sprite::Sprite(uint32_t width, uint32_t height, std::string name)
    : m_spriteName(name), m_height(height), m_width(width), m_timeline(this) {};

void Sprite::changeDimensions(uint32_t width, uint32_t height) {
  m_width = width;
  m_height = height;

  // [TODO]: Call notify here
}

void Sprite::renameSprite(std::string newName) { m_spriteName = newName; }
} // namespace core
