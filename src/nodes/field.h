#pragma once

#include "node.h"

struct Context;

class Field {
public:
  Field(Node *node, std::string data);
  std::string data;
  Node *node;
  Context *ctx;

  std::string Render();
};