#pragma once

#include "core/core.h"

class Field;

enum NodeType {
    FUNCTION = 0
};

class Node {
public: 
    Node* parent;
    std::vector<Node*> children;
    std::vector<Field*> fields;

    virtual std::string Stringify() = 0;

protected:
    Node() {};
    Node(Node* parent);
    ~Node();  
};