#pragma once

#include "field.h"
#include "node.h"

class Root : public Node {
public:
  Root(){};
  ~Root(){};

  virtual std::string Stringify() override {
    std::string result = "";
    for (auto &child : this->children) {
      result += child->Stringify();
    }
    return result;
  }

  virtual llvm::Value *Codegen() override;

  virtual NodeType GetType() override { return ROOT; }
};