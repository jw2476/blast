#include "fn.h"
#include "core/context.h"
#include "core/core.h"
#include "core/llvm.h"

Fn::Fn(Node *parent, std::string name)
    : Node(parent), name(this, name), type(this, "void"){};

std::string Fn::Stringify() {
  std::string result = "";
  result += GENCOLOUR(RED300);
  result += "fn ";
  result += GENCOLOUR(PURPLE300);
  result += this->name.Render();

  result += GENCOLOUR(RAYWHITE);
  result += "(";
  for (auto &child : this->children) {
    if (child->GetType() == ARG)
      result += child->Stringify();
  }
  result += GENCOLOUR(RAYWHITE);
  result += ") ";

  result += GENCOLOUR(RED300);
  result += this->type.Render();
  result += GENCOLOUR(RAYWHITE);
  result += " {";
  result += NEWLINE;
  for (auto &child : this->children) {
    if (child->GetType() == ARG)
      continue;
    std::string childResult = child->Stringify();
    std::istringstream childResultStream(childResult);
    std::string line;
    while (std::getline(childResultStream, line)) {
      result += "  " + line + NEWLINE;
    }
  }
  result += GENCOLOUR(RAYWHITE);
  result += "}";

  result += NEWLINE;
  result += NEWLINE;
  return result;
}

llvm::Value *Fn::Codegen() {
  std::vector<llvm::Type *> args;
  for (auto &child : this->children) {
    if (child->GetType() == ARG)
      args.push_back((llvm::Type *)child->Codegen());
  }

  llvm::FunctionType *funcType =
      llvm::FunctionType::get(this->type.GetLLVMType(), args, false);
  llvm::Function *func =
      llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                             this->name.data, Context::Get()->module.get());

  llvm::BasicBlock *block =
      llvm::BasicBlock::Create(Context::Get()->context, "entry", func);
  Context::Get()->builder.SetInsertPoint(block);

  for (auto &child : this->children) {
    child->Codegen();
  }

  if (this->type.data == "void")
    Context::Get()->builder.CreateRetVoid();
  else if (this->type.data == "i32")
    Context::Get()->builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(Context::Get()->context), 0, false));
  else {
    ERROR("Unknown return type: {}", this->type.data);
  }

  return func;
}

std::string Fn::Validate(Node *parent) {
  if (parent->GetType() != ROOT) {
    return "Invalid parent type, should be root";
  }
  return "";
}