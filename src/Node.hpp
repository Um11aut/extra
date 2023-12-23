#pragma once
#include <memory>
#include <iostream>

class Node {
public:
    using Ptr = std::unique_ptr<Node>;
    using _Pair = std::pair<Ptr, Ptr>;

    Node(const char val) : _val(val) {}
    Node() : _val('\0') {}

    Node(const Node& other) : _val(other._val) {
        _children.first = (other._children.first) ? std::make_unique<Node>(*other._children.first) : nullptr;
        _children.second = (other._children.second) ? std::make_unique<Node>(*other._children.second) : nullptr;
    }

    void setFirst(Ptr node) {
        _children.first = std::move(node);
    }

    void setSecond(Ptr node) {
        _children.second = std::move(node);
    }

    const inline char& get() const& { return _val; }
    const inline _Pair& getPair() const& { return _children; }

private:
    char _val;
    _Pair _children = { nullptr, nullptr };
};

static void print(const Node::Ptr& node, int depth = 0) {
    if (node.get() == nullptr) return;

    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }
    std::cout << node->get() << std::endl;

    print(node->getPair().first, depth + 1);
    print(node->getPair().second, depth + 1);
}

static bool areEqual(const Node::Ptr& first, const Node::Ptr& second) {
  if(first.get() == nullptr && second.get() == nullptr) return true;

  if(first->get() != second->get()) return false;

  areEqual(first->getPair().first, second->getPair().first);
  areEqual(first->getPair().second, second->getPair().second);
  return true;
}
