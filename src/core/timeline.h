#pragma once
#include "forward_declarations.h"

// clang-format off
namespace core {
class Timeline {
public:
  enum class        ANIMATION_TYPE { FORWARD, BACKWARD, PINGPONG };

                    Timeline(Sprite* parent);
                    ~Timeline();

  void              play();
  void              stop();
  void              goToEnd();
  void              nextFrame();
  void              goToStart();
  void              setLayer(frame layer);     // [TODO]: Observer needed
  void              setPlayHead(frame playhead);  // [TODO]: Observer needed
  void              addNewLayer();
  void              setFPS(fps fps);
  void              setAnimationType(ANIMATION_TYPE animationType);

private:
  fps               m_fps           = 6;
  frame             m_playhead      = 0;
  frame             m_selectedLayer = 0;
  frame             m_maxFrame      = 20;
  LayerList         m_layers;
  ANIMATION_TYPE    m_animationType = ANIMATION_TYPE::FORWARD;

  Sprite*           m_parentSprite;
};
} // namespace core
