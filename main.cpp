// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Element.hpp"
#include "NaryTree.hpp"
#include "TreeLoader.hpp"

int main() {
    std::ifstream in("tree_input.txt");
    if (!in) {
        std::cerr << "Failed to open tree_input.txt\n";
        return 1;
    }

    std::ofstream out("tree.json", std::ios::trunc);
    if (!out) {
        std::cerr << "Failed to open tree.json for writing\n";
        return 1;
    }

    NaryTree tree;
    std::vector<NaryTree::Node*> stack;
    std::string line;

    while (std::getline(in, line)) {
        if (line.find_first_not_of(" \t\r\n") == std::string::npos) 
            continue;

        // глубина = (кол-во пробелов) / 2
        std::size_t first = line.find_first_not_of(' ');
        std::size_t depth = first / 2;

        std::string content = line.substr(first);
        std::istringstream iss(content);

        std::string type;
        iss >> type;
        Element elem = tree_loader::parseElement(type, iss);

        // Выбор родителя
        NaryTree::Node* parent = nullptr;
        if (depth == 0) {
            tree.clear();
            stack.clear();
        } else {
            if (depth > stack.size())
                stack.resize(depth, nullptr);
            parent = stack[depth - 1];
        }

        // Добавляем и кладём в стек
        NaryTree::Node* node = tree.addChild(parent, elem);
        if (depth == stack.size())
            stack.push_back(node);
        else
            stack[depth] = node;

        // Пишем снимок в JSON
        tree.toJson(out);
        out << "\n";
    }

    // Последний снимок в консоль
    tree.toJson(std::cout);
    std::cout << "\n";

    return 0;
}

