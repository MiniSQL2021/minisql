#pragma once

#include <optional>

enum class IntervalBoundType {
    Regular, NegativeInfinity, PositiveInfinity
};

template<typename T>
struct IntervalBound {
    const IntervalBoundType type;
    const std::optional<T> value;
    const bool isClose;

    IntervalBound() = delete;

    static auto negativeInfinity = IntervalBound<T>{IntervalBoundType::NegativeInfinity};
    static auto positiveInfinity = IntervalBound<T>{IntervalBoundType::PositiveInfinity};

    static IntervalBound<T> regular(T value, bool isClose) { return {value, isClose}; }

    [[nodiscard]] constexpr bool isRegular() const { return type == IntervalBoundType::Regular; }

    [[nodiscard]] constexpr bool isNegativeInfinity() const { return type == IntervalBoundType::NegativeInfinity; }

    [[nodiscard]] constexpr bool isPositiveInfinity() const { return type == IntervalBoundType::PositiveInfinity; }

    constexpr bool operator<(const IntervalBound<T> &that);

    constexpr bool operator==(const IntervalBound<T> &that);

private:
    explicit IntervalBound(IntervalBoundType type) : type(type), value(std::nullopt), isClose(false) {};

    IntervalBound(T value, bool isClose) : type(IntervalBoundType::Regular), value(value), isClose(isClose) {};
};

template<typename T>
struct Interval {
    const IntervalBound<T> lhs;
    const IntervalBound<T> rhs;

    Interval(IntervalBound<T> lhs, IntervalBound<T> rhs) : lhs(lhs), rhs(rhs) {};

    static std::optional<Interval<T>> intersect(const std::vector<Interval> &intervals);

private:
    constexpr bool lhsLessThan(const Interval &that);

    constexpr std::optional<Interval<T>> intersect(const Interval &that) const;
};
