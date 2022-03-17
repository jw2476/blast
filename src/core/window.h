#pragma once

#include "context.h"
#include "core.h"
#include "layer.h"

class Window : public Layer {
public:
  Window();
  ~Window();

  virtual void OnTick() override;

private:
  Context *ctx;
};