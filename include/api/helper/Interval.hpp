#pragma once

#include <optional>

#include "PointInterval.hpp"

enum class NumberType {
    Regular, NegativeInfinity, PositiveInfinity
};

enum class BoundType {
    Open, Close
};

template<typename T>
struct IntervalBound {
    std::optional<T> value;
    NumberType numberType;
    BoundType type;

    // Unbounded
    explicit IntervalBound(NumberType numberType) : numberType(numberType), value(std::nullopt),
                                                    type(BoundType::Open) {};

    // Bounded
    IntervalBound(const T &value, BoundType type) : numberType(NumberType::Regular), value(value), type(type) {};

    // Copy ctor
    IntervalBound(const IntervalBound<T> &other) = default;

    // Copy assignment
    IntervalBound &operator=(const IntervalBound<T> &other) = default;

    // Move ctor
    IntervalBound(IntervalBound<T> &&other) noexcept = default;

    // Move assignment
    IntervalBound &operator=(IntervalBound<T> &&other) noexcept = default;

    static IntervalBound<T> negativeInfinity() { return IntervalBound<T>(NumberType::NegativeInfinity); }

    static IntervalBound<T> positiveInfinity() { return IntervalBound<T>(NumberType::PositiveInfinity); }

    [[nodiscard]] constexpr bool isRegular() const { return numberType == NumberType::Regular; }

    [[nodiscard]] constexpr bool isNegativeInfinity() const { return numberType == NumberType::NegativeInfinity; }

    [[nodiscard]] constexpr bool isPositiveInfinity() const { return numberType == NumberType::PositiveInfinity; }

    [[nodiscard]] constexpr bool isOpen() const { return type == BoundType::Open; }

    [[nodiscard]] constexpr bool isClose() const { return type == BoundType::Close; }

    constexpr bool operator<(const IntervalBound<T> &that) const {
        return (this->isNegativeInfinity() && !that.isNegativeInfinity()) ||
               (!this->isPositiveInfinity() && that.isPositiveInfinity()) ||
               (this->isRegular() && that.isRegular() && this->value < that.value);
    }

    constexpr bool operator==(const IntervalBound<T> &that) const {
        return this->numberType == that.numberType && this->value == that.value;
    }
};

template<typename T>
struct Interval {
    IntervalBound<T> lhs;
    IntervalBound<T> rhs;

    Interval(const IntervalBound<T> &lhs, const IntervalBound<T> &rhs) : lhs(lhs), rhs(rhs) {};

    // Copy ctor
    Interval(const Interval<T> &other) = default;

    // Copy assignment
    Interval &operator=(const Interval<T> &other) = default;

    // Move ctor
    Interval(Interval<T> &&other) noexcept = default;

    // Move assignment
    Interval &operator=(Interval<T> &&other) noexcept = default;

    static std::optional<Interval<T>> intersect(const std::vector<Interval<T>> &intervals) {
        if (intervals.empty()) return std::nullopt;

        auto sortedIntervals = intervals;
        std::sort(sortedIntervals.begin(), sortedIntervals.end(),
                  [](Interval<T> a, Interval<T> b) { return a.lhsLessThan(b); });

        auto current = *sortedIntervals.cbegin();
        for (auto intervalIter = sortedIntervals.cbegin() + 1; intervalIter < sortedIntervals.cend(); intervalIter++) {
            if (auto intersectResult = current.intersect(*intervalIter))
                current = *intersectResult;
            else return std::nullopt;
        }
        return current;
    }

    std::optional<T> toSingleValue() const {
        if (lhs == rhs && lhs.isClose() && rhs.isClose()) return *lhs.value;
        else return std::nullopt;
    }

    bool contains(const T &value) const {
        bool greaterThanLhs = lhs.isNegativeInfinity() || (lhs.isRegular() && lhs.isClose() && lhs.value <= value) ||
                              (lhs.isRegular() && lhs.isOpen() && lhs.value < value);
        bool lessThanRhs = rhs.isPositiveInfinity() || (rhs.isRegular() && rhs.isClose() && value <= rhs.value) ||
                           (rhs.isRegular() && rhs.isOpen() && value < rhs.value);
        return greaterThanLhs && lessThanRhs;
    }

private:
    bool lhsLessThan(const Interval<T> &that) const {
        return this->lhs < that.lhs ||
               (this->lhs.isRegular() && that.rhs.isRegular() && this->lhs.value == that.lhs.value &&
                this->lhs.isClose() && that.lhs.isOpen());
    }

    std::optional<Interval<T>> intersect(const Interval<T> &that) const {
        // Lhs of this should be less than that
        if (!this->lhsLessThan(that)) return that.intersect(*this);

        if (this->rhs < that.lhs) return std::nullopt;                          // No overlap
        if (this->rhs == that.lhs) {
            if (this->rhs.isOpen() || that.lhs.isOpen())
                return std::nullopt;                                            // No overlap
            else {
                auto bound = IntervalBound<T>(*this->rhs.value, BoundType::Close);
                return Interval<T>(bound, bound);                               // Overlap with only one point
            }
        }
        if (this->rhs < that.rhs) return Interval<T>(that.lhs, this->rhs);      // Overlap
        if (this->rhs == that.rhs && this->rhs.isOpen() && that.rhs.isClose())
            return Interval<T>(that.lhs, this->rhs);                            // Overlap on rhs
        return Interval<T>(that.lhs, that.rhs);                                 // Contain
    }
};
