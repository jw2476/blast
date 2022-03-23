#pragma once

#include "context.h"
#include "core.h"
#include "layer.h"
#include "nodes/node.h"
#include "raylib.h"

enum InsertMode { INSIDE = 0, AFTER };

class Editor : public Layer {
public:
  Editor();
  ~Editor();

  virtual bool OnEvent(Event *event) override;
  virtual void OnDraw() override;

private:
  Context *ctx;
  std::string text;
  uint32_t textIndex;

  uint32_t insertionStage;
  NodeType insertionType;
  InsertMode insertMode;

  std::vector<Field *> fields;
  void FindFields(Node *node);
  inline void SetCurrentField(Node *node) {
    if (node != nullptr && !node->fields.empty()) {
      this->ctx->currentField = node->fields.front();
    }
  }
  inline Node *GetParent() {
    if (this->ctx->currentField == nullptr) {
      return &this->ctx->root;
    }

    if (this->insertMode == INSIDE) {
      return this->ctx->currentField->node;
    } else if (this->insertMode == AFTER) {
      return this->ctx->currentField->node->parent;
    }

    return nullptr;
  }
  inline bool CheckValidate(std::string validationResult) {
    if (validationResult.empty())
      return true;
    else {
      this->ctx->actionBoxPrompt = validationResult;
      return false;
    }
  }
};