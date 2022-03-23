#include "assign.h"

#include "core/context.h"

Assign::Assign(Node *parent, std::string name) : Node(parent), name(this, name), type(this, "i32") {}


std::string Assign::Stringify() {
  std::string result;
  result += GENCOLOUR(RED300);
  result += this->type.Render();
  result += " ";

  result += GENCOLOUR(PURPLE300);
  result += this->name.Render();

  result += GENCOLOUR(RAYWHITE);
  result += " = ";

  if (!this->children.empty()) {
    result += this->children[0]->Stringify();
  }

  return result;
}

llvm::Value *Assign::Codegen() {
  if (!this->children.empty()) {
    Context::Get()->variables[this->name.data] = this->children[0]->Codegen();
  } else {
    ERROR("Variable must be assigned a value");
  }

  return nullptr;
}

std::string Assign::Validate(Node *parent) {
  if (parent->GetType() == FUNCTION) {
    return "";
  }

  return "Invalid parent type, should be function";
}