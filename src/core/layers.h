#pragma once

#include "forward_declarations.h"
#include "layer_flags.h"

namespace core {

class Layer {
public:
  Layer() = default;
  void setFlag(core::LAYER_FLAG flag);
  bool insertKeyFrame(KeyFrameRef keyframe);
  bool insertEmptyKeyFrame();

private:
  layer_flags m_layerFlags = 0;
  KeyFrameList m_keyframe;
};

}; // namespace core
