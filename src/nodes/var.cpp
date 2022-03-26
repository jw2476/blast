#include "var.h"

#include "core/context.h"

Var::Var(Node *parent, std::string name) : Node(parent), name(this, name) {}

std::string Var::Stringify() {
    std::string result;
    result += GENCOLOUR(BLUE300);
    result += this->name.Render();
    return result;
}
llvm::Value *Var::Codegen() {
    Context* ctx = Context::Get();

    if (ctx->variables.at(this->name.data)) {
        return ctx->variables.at(this->name.data);
    } else {
        ERROR("Variable named {} has not been declared", this->name.data);
        return nullptr;
    }
}
std::string Var::Validate(Node *parent) {
    if (parent->GetType() != CALL) {
        return "Parent type invalid, should be call";
    }

    return "";
}