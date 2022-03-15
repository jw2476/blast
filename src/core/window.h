#pragma once

#include "core.h"
#include "layer.h"
#include "context.h"

class Window : public Layer
{
public:
    Window();
    ~Window();

    virtual void OnTick() override; 
private:
    Context* ctx;
};