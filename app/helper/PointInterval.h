#pragma once

enum class PointIntervalType {
    Equal, NotEqual
};

template<typename T>
struct PointInterval {
    const T value;
    const PointIntervalType type;

    PointInterval(const T &value, PointIntervalType type) : value(value), type(type) {};

    static PointInterval<T> equal(const T &value) { return PointInterval<T>(value, PointIntervalType::Equal); }

    static PointInterval<T> notEqual(const T &value) { return PointInterval<T>(value, PointIntervalType::NotEqual); }
};
