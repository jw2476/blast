#pragma once

#include "core.h"
#include "event.h"
#include "layer.h"

class App
{
public:
    App();
    ~App();

    void Run();
    void AttatchLayer(Layer *layer);
private:
    std::queue<Event*> eventBus;
    std::vector<Layer*> layerStack;
};