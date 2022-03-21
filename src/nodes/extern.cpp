#include "extern.h"

#include "core/context.h"

Extern::Extern(Node *parent, std::string name) : Node(parent), name(this, name), type(this, "void") {}

std::string Extern::Stringify() {
    std::string result;
    result += GENCOLOUR(RED300);
    result += "extern fn ";
    result += GENCOLOUR(PURPLE300);
    result += this->name.Render();
    result += GENCOLOUR(RAYWHITE);
    result += "(";

    for (uint32_t i = 0; i < this->children.size(); i++) {
        result += this->children[i]->Stringify();
        if (i != this->children.size() - 1) {
            result += ", ";
        }
    }

    result += GENCOLOUR(RAYWHITE);
    result += ") ";
    result += GENCOLOUR(RED300);
    result += this->type.Render();
    result += GENCOLOUR(RAYWHITE);
    result += NEWLINE;
    return result;
};

llvm::Value *Extern::Codegen() {
    std::vector<llvm::Type*> args;
    for (auto& child : this->children) {
        args.push_back((llvm::Type*)child->Codegen());
    }

    llvm::FunctionType* funcType = llvm::FunctionType::get(this->type.GetLLVMType(), args, false);
    return llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, this->name.data, Context::Get()->module.get());
}

std::string Extern::Validate(Node *parent) {
  if (parent->GetType() != ROOT) {
    return "Invalid parent type, should be root";
  }
  return "";
}