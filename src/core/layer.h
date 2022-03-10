#pragma once

#include "event.h"

class Layer {
public:
    virtual void OnTick(std::queue<Event*> &eventBus) {};
    virtual void OnEvent(Event *event, std::queue<Event*> &eventBus) {};
    virtual void Draw() {};
};