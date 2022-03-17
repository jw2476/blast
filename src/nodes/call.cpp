#include "call.h"

Call::Call(Node *parent, std::string name) : Node(parent), name(this, name) {}

std::string Call::Stringify() {
    std::string result;
    result += this->name.Render() + "()";
    return result;
}

static std::string Validate(Node *parent, std::string name) {
    if (parent->GetType() != FUNCTION) {
        return "Invalid parent type, should be function";
    }
    return "";
}