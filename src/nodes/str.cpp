#include "str.h"
#include "nodes/field.h"

#include "core/context.h"

std::string String::Stringify() {
    std::string result;
    result += GENCOLOUR(ORANGE300);
    result += '"';
    result += this->value.Render();
    result += '"';
    return result;
}

llvm::Value* String::Codegen() {
    return Context::Get()->builder.CreateGlobalStringPtr(llvm::StringRef(this->value.data));
}

std::string String::Validate(Node *parent) {
    if (parent->GetType() == ROOT) {
        return "Parent cannot be root";
    }
    return "";
}