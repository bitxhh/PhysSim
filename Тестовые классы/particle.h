//
// Created by Илья Чернов on 04.07.2025.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iomanip>


// --- Класс vec2: Полная реализация в заголовочном файле ---
// Это хороший тон для небольших служебных классов для лучшей оптимизации.
class vec2 {
public:
    double x, y;

    // Конструкторы
    vec2() : x(0), y(0) {}
    explicit vec2(const double x, const double y) : x(x), y(y) {}

    // Операторы присваивания
    vec2& operator+=(const vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    vec2& operator-=(const vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    vec2& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Бинарные арифметические операторы
    vec2 operator+(const vec2& other) const {
        return vec2(x + other.x, y + other.y);
    }
    vec2 operator-(const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }
    vec2 operator*(double scalar) const {
        return vec2(x * scalar, y * scalar);
    }
    // Скалярное произведение
    double operator*(const vec2& other) const {
        return x * other.x + y * other.y;
    }

    vec2 operator/(const double scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Оператор доступа по индексу
    double operator[](size_t i) const {
        if (i == 0) return x;
        if (i == 1) return y;
        throw std::out_of_range("vec2: index is out of range");
    }

    // Методы для работы с вектором
    [[nodiscard("Похоже вы не используете значение длины")]] double magnitude() const {
        return std::sqrt(x * x + y * y);
    }
    vec2& reset() {
        x = 0;
        y = 0;
        return *this;
    }
    vec2& normalize() {
        const double mag = magnitude();
        if (mag > 1e-9) {
            x /= mag;
            y /= mag;
        } else {
            reset();
        }
        return *this;
    }
    [[nodiscard]] vec2 normalized() const {
        const double mag = magnitude();
        if (mag > 1e-9) {
            return vec2(x / mag, y / mag);
        }
        return vec2(0, 0);
    }

    // Дружественная функция для вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const vec2& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

// --- Класс particle: Только объявление ---
class particle {
public:
    const double mass;
    vec2 position;
    vec2 velocity;
    vec2 acceleration;

    particle(const vec2& initial_position, const vec2& initial_velocity, double particle_mass);
};

// --- Класс particle_system: Только объявление ---
class particle_system {
    double time;
    vec2 g;
    const double G;
    size_t quantity;
    static constexpr double restitution = 0.5;

public:
    std::vector<particle> particles;
    explicit particle_system(size_t particle_quantity);

    void update(double dt);
    void render() const;
};

#endif //PARTICLE_H