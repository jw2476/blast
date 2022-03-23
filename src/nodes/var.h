#pragma once

#include "field.h"
#include "node.h"

class Var : public Node {
public:
  Var(Node *parent, std::string name);

  virtual std::string Stringify() override;
  virtual NodeType GetType() override { return VARIABLE; };
  virtual llvm::Value* Codegen() override;
  static std::string Validate(Node *parent);

  Field name;
};