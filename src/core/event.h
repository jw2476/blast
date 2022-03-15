#pragma once

#include "core.h"

enum EventType
{
    CLOSE = 0,
    KEY_PRESS,
    CHAR_PRESS,
    MOUSE_MOVE,
    ACTION_BOX_ANSWER
};

class Event
{
public:
    virtual EventType GetType() = 0;
protected:
    Event(){};
    virtual ~Event(){};
};