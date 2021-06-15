#include <algorithm>
#include <vector>

#include "Interval.h"

template<typename T>
constexpr bool IntervalBound<T>::operator<(const IntervalBound<T> &that) {
    return (this->isNegativeInfinity() && !that.isNegativeInfinity()) ||
           (!this->isPositiveInfinity() && that.isPositiveInfinity()) ||
           (this->isRegular() && that.isRegular() && this->value < that.value);
}

template<typename T>
constexpr bool IntervalBound<T>::operator==(const IntervalBound<T> &that) {
    return this->type == that.type && this->value == that.value;
}

template<typename T>
constexpr bool Interval<T>::lhsLessThan(const Interval &that) {
    return this->lhs < that.lhs ||
           (this->lhs.isRegular() && that.rhs.isRegular() && this->lhs.value == that.lhs.value && this->lhs.isClose &&
            !that.lhs.isClose);
}

template<typename T>
constexpr std::optional<Interval<T>> Interval<T>::intersect(const Interval &that) const {
    // Lhs of this should be less than that
    if (!this->lhsLessThan(that)) return that.intersect(this);

    if (this->rhs < that.lhs) return std::nullopt;                          // No overlap
    if (this->rhs == that.lhs) {
        if (!this->rhs.isClose || !that.lhs.isClose)
            return std::nullopt;                                            // No overlap
        else return {this->lhs.value, this->lhs.value};                     // Overlap with only one point
    }
    if (this->rhs < that.rhs) return {that.lhs, this->rhs};                 // Overlap
    if (this->rhs == that.rhs && !this->rhs.isClose && that.rhs.isClose)
        return {that.lhs, this->rhs};                                       // Overlap on rhs
    return that;                                                            // Contain
}

template<typename T>
std::optional<Interval<T>> Interval<T>::intersect(const std::vector<Interval<T>> &intervals) {
    if (intervals.empty()) return std::nullopt;

    std::vector<Interval<T>> sortedIntervals = intervals;
    std::sort(sortedIntervals.begin(), sortedIntervals.end(),
              [](Interval<T> a, Interval<T> b) { return a.lhs < b.lhs; });

    Interval<T> result = sortedIntervals.front();
    for (auto intervalIter = sortedIntervals.cbegin() + 1; intervalIter < sortedIntervals.cend(); intervalIter++) {
        if (auto intersectResult = result.intersect(*intervalIter))
            result = intersectResult;
        else return std::nullopt;
    }
    return result;
}
