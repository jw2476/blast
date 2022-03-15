#pragma once

#include "core/event.h"

struct CloseEvent : public Event {
    virtual EventType GetType() {
        return CLOSE;
    }
};