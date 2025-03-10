#pragma once
#include "forward_declarations.h"
#include "layer_flags.h"
// clang-format off
namespace core {
class Layer {
public:
                Layer(uint32_t width, uint32_t height);
                ~Layer();

  void         setFlag(LAYER_FLAG         flag);
  void         insertKeyFrame(KeyFrameRef keyframe);
  void         insertEmptyKeyFrame();
  void         addKeyFrame();
  void         resizeCallback(uint32_t width, uint32_t height);

private:
  frame        m_framehead;
  uint32_t     m_width;
  uint32_t     m_height;
  LAYER_FLAG   m_layerFlags               = LAYER_FLAG::NONE;
  KeyFrameList m_keyframes;
};
}; // namespace core
