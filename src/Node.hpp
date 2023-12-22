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

    Node(Node&& other) noexcept : _val(std::move(other._val)), _children(std::move(other._children)) {
        other._val = '\0';
        other._children = { nullptr, nullptr };
    }

    Node& operator=(const Node& other) {
        if (this != &other) {
            _val = other._val;
            _children.first = (other._children.first) ? std::make_unique<Node>(*other._children.first) : nullptr;
            _children.second = (other._children.second) ? std::make_unique<Node>(*other._children.second) : nullptr;
        }
        return *this;
    }

    Node& operator=(Node&& other) noexcept {
        if (this != &other) {
            _val = std::move(other._val);
            _children = std::move(other._children);

            other._val = '\0';
            other._children = { nullptr, nullptr };
        }
        return *this;
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


std::pair<Node::Ptr, Node::Ptr> nodeDivider(const Node::Ptr& node, const char symbol) {
    if (node.get() == nullptr) return { nullptr, nullptr };

    if (node->get() == symbol) {
        return { std::make_unique<Node>(*node->getPair().first), std::make_unique<Node>(*node->getPair().second) };
    }

    auto leftResult = nodeDivider(node->getPair().first, symbol);
    auto rightResult = nodeDivider(node->getPair().second, symbol);

    return { std::move(leftResult.first), std::move(rightResult.first) };
}
