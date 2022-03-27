#pragma once

#include "field.h"
#include "node.h"

class Arg : public Node {
public:
  Arg(Node *parent, std::string name);

  virtual std::string Stringify() override;
  virtual NodeType GetType() override { return ARG; };
  virtual llvm::Value *Codegen() override;
  static std::string Validate(Node *parent);

  Field name;
  Field type;
};
