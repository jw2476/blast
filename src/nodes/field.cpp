#include "field.h"
#include "core/context.h"

Field::Field(Node *node, std::string data)
    : data(data), node(node), ctx(Context::Get()) {
  node->fields.push_back(this);
};

std::string Field::Render() {
  if (this->ctx->currentField == this) {
    return "|" + this->data + "|";
  } else {
    return data;
  }
}

llvm::Type* Field::GetLLVMType() {
  if (this->data == "void") {
    return llvm::Type::getVoidTy(this->ctx->context);
  } else if (this->data == "i32") {
    return llvm::Type::getInt32Ty(this->ctx->context);
  } else if (this->data == "i8*") {
    return llvm::Type::getInt8PtrTy(this->ctx->context);
  } else {
    ERROR("Unknown type: {}", this->data);
  }
}
