#pragma once

#include "field.h"
#include "node.h"

class Assign : public Node {
public:
  Assign(Node *parent, std::string name);

  virtual std::string Stringify() override;
  virtual NodeType GetType() override { return ASSIGN; };
  virtual llvm::Value *Codegen() override;
  static std::string Validate(Node *parent);

  Field name;
  Field type;
};