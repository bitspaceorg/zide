#pragma once

#include "keyframe.h"
#include <cstdint>
#include <memory>
#include <vector>

class Sprite;
class Layer;
class KeyFrame;

typedef std::shared_ptr<Sprite> SpriteRef;
typedef std::shared_ptr<Layer>  LayerRef;
typedef std::shared_ptr<KeyFrame> KeyFrameRef;

typedef uint8_t  layer_flags;
typedef uint16_t fps;
typedef uint16_t frame;

typedef std::vector<SpriteRef> SpriteList;
typedef std::vector<LayerRef>  LayerList;
typedef std::vector<KeyFrameRef>  KeyFrameList;
