#pragma once

#include "core.h"
#include "event.h"
#include "nodes/root.h"
#include "raylib.h"
#include "llvm.h"

static struct Context *ctx;

struct Context {
  Context() : builder(this->context), currentField(nullptr) {
    this->font = LoadFontEx("resources/fonts/JetBrainsMono-Medium.ttf", 24,
                            nullptr, 250);
    this->module = std::make_unique<llvm::Module>("program", this->context);
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

  llvm::LLVMContext context;
  llvm::IRBuilder<> builder;
  std::unique_ptr<llvm::Module> module;
  std::unordered_map<std::string, llvm::Value*> variables;
};
