#pragma once

#include "field.h"
#include "node.h"

class Fn : public Node {
public:
  Fn(Node *parent, std::string name);

  virtual std::string Stringify() override;
  virtual NodeType GetType() override { return FUNCTION; };
  virtual llvm::Value* Codegen() override;
  static std::string Validate(Node *parent);

  Field name;
  Field type;
};