#pragma once

#include "forward_declarations.h"
#include "timeline.h"
#include <string>

namespace core {

class Sprite {
public:
  // IN PIXELS
  Sprite(int height, int width, std::string name)
      : m_spriteName(name), m_height(height), m_width(width) {};

private:
  int m_height;
  int m_width;
  std::string m_spriteName;
  Timeline m_timeline;
};

} // namespace core
