#include "arg.h"
#include "nodes/node.h"

Arg::Arg(Node *parent, std::string name)
    : Node(parent), name(this, name), type(this, "void") {}

std::string Arg::Stringify() {
  std::string result;
  result += GENCOLOUR(RED300);
  result += this->type.Render();
  result += " ";
  result += GENCOLOUR(PURPLE300);
  result += this->name.Render();
  return result;
};

llvm::Value *Arg::Codegen() {
    return (llvm::Value*)this->type.GetLLVMType();
}

std::string Arg::Validate(Node *parent) {
    if (parent->GetType() == FUNCTION || parent->GetType() == EXTERN) {
        return "";
    }

    return "Incorrect parent type, should be function or an extern function";
}