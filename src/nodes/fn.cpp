#include "fn.h"

Fn::Fn(Node *parent, std::string name) : Node(parent), name(this, name), type(this, "void"){};

std::string Fn::Stringify()
{
    std::string result = "";
    result += "fn " + this->name.Render() + "() " + this->type.Render() + " {" + NEWLINE;
    for (auto& child : this->children) {
        result += "    " + child->Stringify() + NEWLINE;
    }
    result += "}";
    result += NEWLINE;
    return result;
}