#include "app.h"
#include "context.h"

App::App() {
  this->context = Context::Get();
  this->layerStack.push_back(&this->window);
  this->layerStack.push_back(&this->editor);
  this->layerStack.push_back(&this->actionBox);
}

App::~App() {}

void App::Run() {
  while (true) {
    for (auto layer : this->layerStack) {
      layer->OnTick();
    }

    while (!this->context->eventBus.empty()) {
      Event *event = this->context->eventBus.front();
      if (event->GetType() == CLOSE) {
        return;
      }

      for (int i = this->layerStack.size() - 1; i >= 0; i--) {
        if (this->layerStack[i]->OnEvent(
                event)) { // If true, no longer propogate the event
          break;
        }
      }
      this->context->eventBus.pop();
    }

    BeginDrawing();
    for (auto layer : this->layerStack) {
      layer->OnDraw();
    }
    EndDrawing();
  }
}
