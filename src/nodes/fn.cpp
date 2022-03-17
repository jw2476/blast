#include "fn.h"

Fn::Fn(Node *parent, std::string name)
    : Node(parent), name(this, name), type(this, "void"){};

std::string Fn::Stringify() {
  std::string result = "";
  result += "fn " + this->name.Render() + "() " + this->type.Render() + " {" +
            NEWLINE;
  for (auto &child : this->children) {
    result += "    " + child->Stringify() + NEWLINE;
  }
  result += "}";
  result += NEWLINE;
  result += NEWLINE;
  return result;
}

std::string Fn::Validate(Node *parent, std::string name) {
  if (parent->GetType() != ROOT) {
    return "Invalid parent type, should be root";
  }
  return "";
}