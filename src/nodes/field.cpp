#include "field.h"
#include "core/context.h"

Field::Field(Node *node, std::string data) : data(data), node(node), ctx(Context::Get()) { node->fields.push_back(this); };

std::string Field::Render()
{
    if (this->ctx->currentField == this)
    {
        return "|" + this->data + "|";
    }
    else
    {
        return data;
    }
}
