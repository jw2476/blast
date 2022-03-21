#include "fn.h"
#include "core/core.h"
#include <sstream>

Fn::Fn(Node *parent, std::string name)
    : Node(parent), name(this, name), type(this, "void"){};

std::string Fn::Stringify() {
  std::string result = "";
  result += GENCOLOUR(RED300);
  result += "fn ";
  result += GENCOLOUR(PURPLE300);
  result += this->name.Render();
  result += GENCOLOUR(RAYWHITE);
  result += "() ";
  result += GENCOLOUR(RED300);
  result += this->type.Render();
  result += GENCOLOUR(RAYWHITE);
  result += " {";
  result += NEWLINE;
  for (auto &child : this->children) {
    std::string childResult = child->Stringify();
    std::istringstream childResultStream(childResult);
    std::string line;
    while (std::getline(childResultStream, line)) {
      result += "  " + line + NEWLINE;
    }
  }
  result += GENCOLOUR(RAYWHITE);
  result += "}";
  return result;
}

std::string Fn::Validate(Node *parent) {
  if (parent->GetType() != ROOT) {
    return "Invalid parent type, should be root";
  }
  return "";
}