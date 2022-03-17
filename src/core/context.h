#pragma once

#include "core.h"
#include "event.h"
#include "nodes/root.h"
#include "raylib.h"

static struct Context *ctx;

struct Context {
  Context() {
    this->font = LoadFontEx("resources/fonts/JetBrainsMono-Medium.ttf", 24,
                            nullptr, 250);
  }

  static Context *Get() {
    if (ctx == nullptr) {
      ctx = new Context();
    }

    return ctx;
  }

  std::queue<Event *> eventBus;

  std::string actionBoxPrompt;
  std::string actionBoxAnswer;

  Font font;

  Root root;
  Field *currentField;
};
