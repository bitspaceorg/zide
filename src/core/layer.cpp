#include "layer.h"
#include "forward_declarations.h"
#include <cassert>

namespace core {
Layer::Layer(uint32_t width, uint32_t height)
    : m_width(width), m_height(height) {}
Layer::~Layer() = default;

void Layer::setFlag(LAYER_FLAG flag) { m_layerFlags = flag; }
void Layer::insertKeyFrame(KeyFrameRef keyframe) {
  m_keyframes.emplace(m_keyframes.begin() + m_framehead, keyframe);
}
void Layer::insertEmptyKeyFrame() {
  m_keyframes.emplace(m_keyframes.begin() + m_framehead,
                      std::make_shared<KeyFrame>(m_width, m_height));
}
void Layer::addKeyFrame() {
  m_keyframes.emplace_back(std::make_shared<KeyFrame>(m_width, m_height));
}
void Layer::resizeCallback(uint32_t width, uint32_t height) {
  m_width = width;
  m_height = height;

  // [TODO]: Observer callback here
}
} // namespace core
