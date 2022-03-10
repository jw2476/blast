#pragma once

#include "core.h"
#include "event.h"
#include "layer.h"

#include "raylib.h"

class Editor : public Layer {
public: 
    Editor();
    ~Editor();

    virtual void Draw();
    virtual void OnEvent(Event* event, std::queue<Event*> eventBus);
private:
    Font font;
    std::string code;
};