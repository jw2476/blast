#pragma once

#include "core.h"
#include "event.h"

class Layer {
public:
  virtual void OnTick(){};
  virtual bool OnEvent(Event *event) { return false; };
  virtual void OnDraw(){};

protected:
  Layer(){};
  virtual ~Layer(){};
};