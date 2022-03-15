#pragma once

#include "core.h"
#include "raylib.h"
#include "context.h"
#include "layer.h"

#include "window.h"
#include "editor.h"
#include "actionbox.h"

class App {
public: 
    App();
    ~App();

    void Run();
private:
    std::vector<Layer*> layerStack;
    Context* context;

    Window window;
    Editor editor;
    ActionBox actionBox;
};