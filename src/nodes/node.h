#pragma once

#include "core/core.h"

class Field;

enum NodeType { ROOT = 0, FUNCTION, CALL };

class Node {
public:
  virtual ~Node();

  Node *parent;
  std::vector<Node *> children;
  std::vector<Field *> fields;

  virtual std::string Stringify() = 0;
  virtual NodeType GetType() = 0;

protected:
  Node(){};
  Node(Node *parent);
};