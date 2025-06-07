
#pragma once

#include "NaryTree.hpp"
#include <sstream>
#include <istream>
#include <vector>
#include <stack>
#include <cctype>

namespace tree_loader {

inline std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> out; 
    std::stringstream ss(s); 
    std::string item;
    while (std::getline(ss, item, delim)) out.push_back(item);
    return out;
}

inline Element parseElement(const std::string& type, std::istringstream& iss) {
    if (type == "int") {
        int x; iss >> x; return x;
    } else if (type == "double") {
        double d; iss >> d; return d;
    } else if (type == "complex") {
        double re, im; iss >> re >> im; return std::complex<double>{re, im};
    } else if (type == "string") {
        std::string rest; std::getline(iss, rest);
        if (!rest.empty() && std::isspace(rest[0])) rest.erase(0,1);
        return rest;
    } else if (type == "student") {
        int course, age; std::string name, faculty, major; iss >> course >> age >> name >> faculty >> major;
        return Student{course, age, name, faculty, major};
    } else if (type == "teacher") {
        std::string name, subjectsStr; int exp; iss >> name >> subjectsStr >> exp;
        auto subjects = split(subjectsStr, ',');
        return Teacher{name, subjects, exp};
    }
    throw std::runtime_error("Unknown type: " + type);
}
} 