#pragma once
#include "timeline.h"
#include <string>

namespace core {

class Sprite {
public:
  Sprite(uint32_t width, uint32_t height, std::string name);
  void changeDimensions(uint32_t width,
                        uint32_t height); // [TODO]: Observer needed
  void renameSprite(std::string newName);

private:
  uint32_t m_width, m_height;
  std::string m_spriteName;
  Timeline m_timeline;
};

} // namespace core
