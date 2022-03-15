#pragma once

#include "node.h"
#include "field.h"

class Fn : public Node
{
public:
    Fn(Node* parent, std::string name);

    virtual std::string Stringify() override;

    Field name;
    Field type;
};