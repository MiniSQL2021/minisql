#include <algorithm>
#include <vector>

#include "Interval.hpp"

template<typename T>
constexpr bool IntervalBound<T>::operator<(const IntervalBound<T> &that) {
    return (this->isNegativeInfinity() && !that.isNegativeInfinity()) ||
           (!this->isPositiveInfinity() && that.isPositiveInfinity()) ||
           (this->isRegular() && that.isRegular() && this->value < that.value);
}

template<typename T>
constexpr bool IntervalBound<T>::operator==(const IntervalBound<T> &that) {
    return this->numberType == that.numberType && this->value == that.value;
}

template<typename T>
constexpr bool Interval<T>::lhsLessThan(const Interval<T> &that) const {
    return this->lhs < that.lhs ||
           (this->lhs.isRegular() && that.rhs.isRegular() && this->lhs.value == that.lhs.value && this->lhs.isClose() &&
            that.lhs.isOpen());
}

template<typename T>
constexpr std::optional<Interval<T>> Interval<T>::intersect(const Interval<T> &that) {
    // Lhs of this should be less than that
    if (!this->lhsLessThan(that)) return that.intersect(this);

    if (this->rhs < that.lhs) return std::nullopt;                          // No overlap
    if (this->rhs == that.lhs) {
        if (this->rhs.isOpen() || that.lhs.isOpen())
            return std::nullopt;                                            // No overlap
        else {
            auto value = this->rhs.value;
            auto bound = IntervalBound<T>(value, BoundType::Close);
            return Interval<T>(bound, bound);                               // Overlap with only one point
        }
    }
    if (this->rhs < that.rhs) return Interval<T>(that.lhs, this->rhs);      // Overlap
    if (this->rhs == that.rhs && this->rhs.isOpen() && that.rhs.isClose())
        return Interval<T>(that.lhs, this->rhs);                            // Overlap on rhs
    return that;                                                            // Contain
}

template<typename T>
std::optional<Interval<T>> Interval<T>::intersect(const std::vector<Interval<T>> &intervals) {
    if (intervals.empty()) return std::nullopt;

    auto sortedIntervals = intervals;
    std::sort(sortedIntervals.begin(), sortedIntervals.end(),
              [](Interval<T> a, Interval<T> b) { return a.lhsLessThan(b); });

    auto result = sortedIntervals.front();
    for (auto intervalIter = sortedIntervals.cbegin() + 1; intervalIter < sortedIntervals.cend(); intervalIter++) {
        if (auto intersectResult = result.intersect(*intervalIter))
            result = intersectResult;
        else return std::nullopt;
    }
    return result;
}

template<typename T>
constexpr std::optional<T> Interval<T>::toSingleValue() const {
    if (lhs == rhs && lhs.isClose() && rhs.isClose()) return lhs.value;
    else return std::nullopt;
}

template<typename T>
constexpr bool Interval<T>::contains(const T &value) const {
    bool greaterThanLhs = lhs.isNegativeInfinity() || (lhs.isRegular() && lhs.isClose() && lhs.value <= value) ||
                          (lhs.isRegular() && lhs.isOpen() && lhs.value < value);
    bool lessThanRhs = rhs.isPositiveInfinity() || (rhs.isRegular() && rhs.isClose() && value <= rhs.value) ||
                       (rhs.isRegular() && rhs.isOpen() && value < rhs.value);
    return greaterThanLhs && lessThanRhs;
}
