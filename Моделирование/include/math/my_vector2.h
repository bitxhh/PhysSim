#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <limits>

class vec2 {
public:
    double x, y;

    // Конструкторы
    vec2() noexcept : x(0), y(0){}
    vec2(const double x, const double y) noexcept : x(x), y(y) {}

    // Операторы присваивания
    vec2& operator+= (const vec2& other) noexcept {
        x += other.x;
        y += other.y;
        return *this;
    }
    vec2& operator-= (const vec2& other) noexcept {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    vec2& operator*= (const double scalar) noexcept {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    vec2& operator/=(const double scalar) {
        if (std::abs(scalar) < std::numeric_limits<double>::min()) throw std::invalid_argument("Division by zero");
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Бинарные арифметические операторы
    [[nodiscard]] vec2 operator+(const vec2& other) const noexcept {
        return {x + other.x, y + other.y};
    }
    [[nodiscard]] vec2 operator-(const vec2& other) const noexcept {
        return {x - other.x, y - other.y};
    }
    [[nodiscard]] vec2 operator*(const double scalar) const noexcept {
        return {x * scalar, y * scalar};
    }
    [[nodiscard]] vec2 operator/(const double scalar) const {
        if (std::abs(scalar) < std::numeric_limits<double>::min()) throw std::invalid_argument("Division by zero");
        return {x / scalar, y / scalar};
    }

    // Скалярное произведение
    [[nodiscard]] double operator* (const vec2& other) const noexcept{
        return x * other.x + y * other.y;
    }
    bool operator== (const vec2& other) const noexcept{
        return std::abs(x - other.x) < 1e-9 &&
               std::abs(y - other.y) < 1e-9;
    }
    bool operator!= (const vec2& other) const noexcept{
        return !(*this == other);
    }

    // Оператор доступа по индексу
    double operator[](const size_t i) const {
        if (i == 0) return x;
        if (i == 1) return y;
        throw std::out_of_range("vec2: index is out of range");
    }
    double& operator[](const size_t i) {
        if (i == 0) return x;
        if (i == 1) return y;
        throw std::out_of_range("vec2: index is out of range");
    }

    // Методы для работы с вектором
    [[nodiscard("Похоже вы не используете значение длины")]] double magnitude() const {
        return std::sqrt(x * x + y * y);
    }
    vec2& reset() noexcept{
        x = 0;
        y = 0;
        return *this;
    }
    vec2& normalize() {
        if (const double mag = magnitude(); mag > 1e-9) {
            x /= mag;
            y /= mag;
        } else {
            throw std::logic_error("Cannot normalize zero vector");
        }
        return *this;
    }
    [[nodiscard]] vec2 normalized() const {
        if (const double mag = magnitude(); mag > 1e-9) {
            return vec2{x / mag, y / mag};
        }
        throw std::logic_error("Cannot normalize zero vector");
    }

    // Дружественная функция для вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const vec2& v) noexcept {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

inline vec2 operator*(const double scalar, const vec2& v) noexcept {
    return v * scalar;
}
