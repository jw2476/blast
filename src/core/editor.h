#pragma once

#include "layer.h"
#include "core.h"
#include "context.h"
#include "raylib.h"
#include "nodes/node.h"

class Editor : public Layer {
public:
    Editor();
    ~Editor();

    virtual bool OnEvent(Event* event) override;
    virtual void OnDraw() override;
private:
    Context* ctx;
    std::string text;

    uint32_t insertionStage;
    NodeType insertionType;

    std::vector<Field*> fields;
    void FindFields(Node* node);
    inline void SetCurrentField(Node* node) {
        if (node != nullptr && !node->fields.empty()) {
            this->ctx->currentField = node->fields.front();
        }
    }
};