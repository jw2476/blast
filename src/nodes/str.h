#pragma once

#include "field.h"
#include "node.h"

class String : public Node {
public:
    String(Node* parent, std::string value) : Node(parent), value(this, value) {}

    virtual std::string Stringify() override;
    virtual NodeType GetType() override { return STRING; };
    virtual llvm::Value* Codegen() override;
    static std::string Validate(Node *parent);

    Field value;
};