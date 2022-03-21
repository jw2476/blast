#pragma once

#include "node.h"
#include "field.h"


class Extern : public Node {
public:
  Extern(Node *parent, std::string name);

  virtual std::string Stringify() override;
  virtual NodeType GetType() override { return EXTERN; };
  virtual llvm::Value* Codegen() override;
  static std::string Validate(Node *parent);

  Field name;
  Field type;
};