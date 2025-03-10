#pragma once
#include "timeline.h"

namespace core {
Timeline::Timeline(Sprite *parent) { m_parentSprite = parent; }
Timeline::~Timeline() = default;

void Timeline::play() {}
void Timeline::stop() {}
void Timeline::goToEnd() {}
void Timeline::nextFrame() {}
void Timeline::setLayer(frame layer) {
  m_selectedLayer = layer; /* [TODO]: Observer callback */
}
void Timeline::goToStart() { m_playhead = 0; }
void Timeline::setPlayHead(frame playhead) { m_playhead = playhead; }
void Timeline::addNewLayer() { m_layers.emplace_back(); }
void Timeline::setFPS(fps fps) { m_fps = fps; }
void Timeline::setAnimationType(ANIMATION_TYPE animationType) {}
} // namespace core
