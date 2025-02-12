#pragma once

#include "forward_declarations.h"
#include "layers.h"
#include <vector>

namespace core {

enum class ANIMATION_TYPE { FORWARD, BACKWARD, PINGPONG };

class Timeline {
public:
  Timeline();

  void play();
  void stop();
  void nextFrame();
  void goToEnd();
  void goToStart();
  void setFPS(fps newFPS);
  void setAnimationType(ANIMATION_TYPE animationType);

private:
  ANIMATION_TYPE m_animationType = ANIMATION_TYPE::FORWARD;
  fps m_fps = 6;
  frame m_playhead = 0;
  frame m_maxFrame = 20;

  LayerList m_layers;
};

} // namespace core
