#pragma once

#include "core/core.h"
#include "core/event.h"

struct KeyPressEvent : public Event {
  KeyPressEvent(int key) : key(key) {}

  virtual EventType GetType() override { return KEY_PRESS; }

  int key;
};

struct CharPressEvent : public Event {
  CharPressEvent(char key) : key(key) {}

  virtual EventType GetType() override { return CHAR_PRESS; }

  char key;
};

struct MouseMoveEvent : public Event {
  MouseMoveEvent(int x, int y) : x(x), y(y) {}

  virtual EventType GetType() override { return MOUSE_MOVE; }

  int x;
  int y;
};

struct ActionBoxAnswerEvent : public Event {
  ActionBoxAnswerEvent(std::string text) : text(text) {}

  virtual EventType GetType() override { return ACTION_BOX_ANSWER; }

  std::string text;
};