#pragma once

#include "field.h"
#include "node.h"

class Call : public Node {
public:
  Call(Node *parent, std::string name);

  virtual std::string Stringify() override;
  virtual NodeType GetType() override { return CALL; };
  static std::string Validate(Node *parent, std::string name);

  Field name;
};
