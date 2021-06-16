#pragma once

#include <optional>

#include "PointInterval.h"

enum class NumberType {
    Regular, NegativeInfinity, PositiveInfinity
};

enum class BoundType {
    Open, Close
};

template<typename T>
struct IntervalBound {
    const std::optional<T> value;
    const NumberType numberType;
    const BoundType type;

    // Unbounded
    explicit IntervalBound(NumberType numberType) : numberType(numberType), value(std::nullopt),
                                                    type(BoundType::Open) {};

    // Bounded
    IntervalBound(const T &value, BoundType type) : numberType(NumberType::Regular), value(value), type(type) {};

    static IntervalBound<T> negativeInfinity() { return IntervalBound<T>(NumberType::NegativeInfinity); }

    static IntervalBound<T> positiveInfinity() { return IntervalBound<T>(NumberType::PositiveInfinity); }

    [[nodiscard]] constexpr bool isRegular() const { return numberType == NumberType::Regular; }

    [[nodiscard]] constexpr bool isNegativeInfinity() const {
        return numberType == NumberType::NegativeInfinity;
    }

    [[nodiscard]] constexpr bool isPositiveInfinity() const {
        return numberType == NumberType::PositiveInfinity;
    }

    [[nodiscard]] constexpr bool isOpen() const {
        return type == BoundType::Open;
    }

    [[nodiscard]] constexpr bool isClose() const {
        return type == BoundType::Close;
    }

    constexpr bool operator<(const IntervalBound<T> &that);

    constexpr bool operator==(const IntervalBound<T> &that);
};

template<typename T>
struct Interval {
    IntervalBound<T> lhs;
    IntervalBound<T> rhs;

    Interval(const IntervalBound<T> &lhs, const IntervalBound<T> &rhs) : lhs(lhs), rhs(rhs) {};

    static std::optional<Interval<T>> intersect(const std::vector<Interval<T>> &intervals);

    constexpr std::optional<T> toSingleValue() const;

    constexpr bool contains(const T &value) const;

private:
    constexpr bool lhsLessThan(const Interval<T> &that);

    constexpr std::optional<Interval<T>> intersect(const Interval<T> &that) const;
};
