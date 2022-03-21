#pragma once

#include "context.h"
#include "core.h"
#include "layer.h"
#include "nodes/node.h"
#include "raylib.h"

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
  bool insertIntoRoot;

  std::vector<Field *> fields;
  void FindFields(Node *node);
  inline void SetCurrentField(Node *node) {
    if (node != nullptr && !node->fields.empty()) {
      this->ctx->currentField = node->fields.front();
    }
  }
  inline Node *GetParent() {
    if (this->ctx->currentField == nullptr || this->insertIntoRoot) {
      return &this->ctx->root;
    } else {
      return this->ctx->currentField->node;
    }
  }
  inline bool CheckValidate(std::string validationResult) {
    if (validationResult.empty()) return true;
    else {
      this->ctx->actionBoxPrompt = validationResult;
      return false;
    }
  }
};