#pragma once

#include "context.h"
#include "core.h"
#include "event.h"
#include "layer.h"

class ActionBox : public Layer {
public:
  ActionBox() : ctx(Context::Get()){};

  virtual bool OnEvent(Event *e) override;
  virtual void OnDraw() override;

private:
  Context *ctx;
  std::string response;
};