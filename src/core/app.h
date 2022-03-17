#pragma once

#include "context.h"
#include "core.h"
#include "layer.h"
#include "raylib.h"

#include "actionbox.h"
#include "editor.h"
#include "window.h"

class App {
public:
  App();
  ~App();

  void Run();

private:
  std::vector<Layer *> layerStack;
  Context *context;

  Window window;
  Editor editor;
  ActionBox actionBox;
};