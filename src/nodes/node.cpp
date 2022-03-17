#include "node.h"

Node::Node(Node *parent) : parent(parent) {
  if (this->parent != nullptr) {
    this->parent->children.push_back(this);
  }
}

Node::~Node() {
  if (this->parent != nullptr) {
    auto idx = std::find(this->parent->children.begin(),
                         this->parent->children.end(), this);
    this->parent->children.erase(idx);
  }

  for (auto &child : this->children) {
    delete child;
  }
}