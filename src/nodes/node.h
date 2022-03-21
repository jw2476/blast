#pragma once

#include "core/core.h"
#include "core/llvm.h"

class Field;

enum NodeType { ROOT = 0, FUNCTION, CALL, STRING, EXTERN, ARG };

class Node {
public:
  virtual ~Node();

  Node *parent;
  std::vector<Node *> children;
  std::vector<Field *> fields;

  virtual std::string Stringify() = 0;
  virtual NodeType GetType() = 0;
  virtual llvm::Value* Codegen() = 0;

protected:
  Node(){};
  Node(Node *parent);
};