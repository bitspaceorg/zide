#pragma once

#include "color.h"
#include "forward_declarations.h"

namespace core {

class KeyFrame {
public:
  KeyFrame();
  bool isEmpty();
private:
  std::vector<std::vector<Color>> m_grid;
};

}; // namespace core
