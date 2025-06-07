// NaryTree.cpp
#include "NaryTree.hpp"
#include "Element.hpp"
#include <queue>
#include <stack>
#include <iostream>
#include <utility>

NaryTree::NaryTree(Element rootVal) {
    root = std::make_unique<Node>(std::move(rootVal));
}

NaryTree::Node* NaryTree::addChild(Node* parent, Element value) {
    if (!parent) {
        if (!root) root = std::make_unique<Node>(std::move(value));
        return root.get();
    }
    parent->children.push_back(std::make_unique<Node>(std::move(value)));
    return parent->children.back().get();
}

bool NaryTree::removeSubtree(Node* target) {
    if (!target || !root) return false;
    if (target == root.get()) { clear(); return true; }
    std::queue<Node*> q; q.push(root.get());
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        for (auto it = cur->children.begin(); it != cur->children.end(); ++it) {
            if (it->get() == target) {
                cur->children.erase(it);
                return true;
            }
            q.push(it->get());
        }
    }
    return false;
}

NaryTree::Node* NaryTree::find(const std::function<bool(const Element&)>& pred) const {
    if (!root) return nullptr;
    std::queue<Node*> q; q.push(root.get());
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (pred(cur->value)) return cur;
        for (auto& ch : cur->children) q.push(ch.get());
    }
    return nullptr;
}

void NaryTree::clear() { root.reset(); }

// Остальные обходы остаются без изменений...

// ---------------------
// JSON-сериализация
// ---------------------
void NaryTree::toJson(std::ostream& out) const {
    // Рекурсивная лямбда для обхода
    std::function<void(const Node*)> dump = [&](const Node* n) {
        out << "{ \"value\": \"" << to_string(n->value) << "\"";
        if (!n->children.empty()) {
            out << ", \"children\": [";
            for (size_t i = 0; i < n->children.size(); ++i) {
                dump(n->children[i].get());
                if (i + 1 < n->children.size()) out << ", ";
            }
            out << "]";
        }
        out << "}";
    };

    if (root) {
        dump(root.get());
    } else {
        out << "null";
    }
}

