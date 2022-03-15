#pragma once

#include "node.h"
#include "field.h"

class Root : public Node {
public:
    Root() {};
    ~Root() {};

    virtual std::string Stringify() override {
        std::string result = "";
        for (auto& child : this->children) {
            result += child->Stringify();
        }
        return result;
    }
};