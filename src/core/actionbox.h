#pragma once

#include "core.h"
#include "layer.h"
#include "event.h"
#include "context.h"

class ActionBox : public Layer
{
public: 
    ActionBox() : ctx(Context::Get()) {};

    virtual bool OnEvent(Event* e) override;
    virtual void OnDraw() override;
private:
    Context* ctx;
    std::string response;
};