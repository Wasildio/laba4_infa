#pragma once

#include <variant>
#include <complex>
#include <string>
#include <functional>
#include <vector>
#include <sstream>

struct Student {
    int course{};
    int age{};
    std::string name;
    std::string faculty;
    std::string major;
    bool operator==(const Student&) const = default;
};

struct Teacher {
    std::string name;
    std::vector<std::string> subjects;
    int experience{}; // years
    bool operator==(const Teacher&) const = default;
};

using Element = std::variant<
    int,
    double,
    std::complex<double>,
    std::string,
    std::function<double(double)>,
    Student,
    Teacher>;

inline std::string to_string(const Element& e) {
    return std::visit([](const auto& v) -> std::string {
        using V = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<V, int> || std::is_same_v<V, double>) {
            return std::to_string(v);
        } else if constexpr (std::is_same_v<V, std::complex<double>>) {
            std::ostringstream oss;
            oss << v;
            return oss.str();
        } else if constexpr (std::is_same_v<V, std::string>) {
            return v;
        } else if constexpr (std::is_same_v<V, std::function<double(double)>>) {
            return "<function>";
        } else if constexpr (std::is_same_v<V, Student>) {
            return "Student{" + v.name + ", age=" + std::to_string(v.age) + "}";
        } else if constexpr (std::is_same_v<V, Teacher>) {
            return "Teacher{" + v.name + "}";
        } else {
            return "<unknown>";
        }
    }, e);
}
