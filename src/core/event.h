#pragma once

enum EventType {
    KeyPress = 0
};

class Event {
    virtual EventType GetType() = 0;
};