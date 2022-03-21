#include "call.h"

#include "core/context.h"

Call::Call(Node *parent, std::string name) : Node(parent), name(this, name) {}

std::string Call::Stringify() {
  std::string result;
  result += GENCOLOUR(PURPLE300);
  result += this->name.Render();
  result += GENCOLOUR(RAYWHITE);
  result += "(";
  for (auto &child : this->children) {
    result += child->Stringify();
  }
  result += GENCOLOUR(RAYWHITE);
  result += ")";
  return result;
}

llvm::Value *Call::Codegen() {
  llvm::Function *func = Context::Get()->module->getFunction(this->name.data);
  if (!func) {
    ERROR("Function not found: {}", this->name.data);
  }

  if (func->arg_size() != this->children.size()) {
    ERROR("Incorrect number of arguments passed to: {}", this->name.data);
  }

  std::vector<llvm::Value *> args;
  for (uint32_t i = 0; i < this->children.size(); i++) {
    llvm::Value *arg = this->children[i]->Codegen();
    if (arg->getType() != func->getArg(i)->getType()) {
      ERROR("Argument number {} calling {} is the wrong type", i + 1,
            this->name.data)
    }
    args.push_back(arg);
  }

  return Context::Get()->builder.CreateCall(func, args, "call");
}

std::string Call::Validate(Node *parent) {
  if (parent->GetType() != FUNCTION) {
    return "Invalid parent type, should be function";
  }
  return "";
}