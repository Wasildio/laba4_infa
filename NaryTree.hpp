#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <ostream>
#include "Element.hpp"

class NaryTree {
public:
    struct Node {
        Element value;
        std::vector<std::unique_ptr<Node>> children;
        explicit Node(Element val) : value(std::move(val)) {}
    };

    NaryTree() = default;
    explicit NaryTree(Element rootVal);

    Node* addChild(Node* parent, Element value);
    bool removeSubtree(Node* target);
    Node* find(const std::function<bool(const Element&)>& pred) const;
    void clear();

    void traversePreOrder() const;
    void traversePostOrder() const;
    void traverseDFSIterative() const;
    void traverseLevelOrder() const;
    void traverseReverseLevel() const;
    void traverseZigZag() const;

    // Новый метод для JSON-вывода
    void toJson(std::ostream& out) const;

private:
    void traversePreOrder(Node* n, size_t level) const;
    void traversePostOrder(Node* n, size_t level) const;

    std::unique_ptr<Node> root;
};
