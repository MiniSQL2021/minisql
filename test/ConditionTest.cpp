#include "catch2/catch.hpp"
#include "api/helper/Interval.hpp"
#include "api/helper/Condition.hpp"

template<typename T>
RangeCondition makeRange(T left, bool leftClose, T right, bool rightClose) {
    return RangeCondition(LiteralIntervalBound(Literal(left), leftClose ? BoundType::Close : BoundType::Open),
                          LiteralIntervalBound(Literal(right), rightClose ? BoundType::Close : BoundType::Open));
}

template<typename T>
RangeCondition makeGreaterThan(T value, bool close) {
    return RangeCondition(LiteralIntervalBound(Literal(value), close ? BoundType::Close : BoundType::Open),
                          LiteralIntervalBound::positiveInfinity());
}

template<typename T>
RangeCondition makeLessThan(T value, bool close) {
    return RangeCondition(LiteralIntervalBound::negativeInfinity(),
                          LiteralIntervalBound(Literal(value), close ? BoundType::Close : BoundType::Open));
}

TEST_CASE("Intersect range conditions", "[condition:intersect]") {

    SECTION("regular ones") {
        auto i1 = makeRange(4, true, 5, true);
        auto i2 = makeRange(1, false, 6, true);
        auto i3 = makeRange(4, false, 5, false);
        auto i4 = makeRange(2, true, 8, true);
        auto i5 = makeRange(3, true, 7, true);
        auto i6 = makeRange(2, false, 7, false);

        auto result = RangeCondition::intersect({i1, i2, i3, i4, i5, i6});
        REQUIRE(result->lhs.value->intValue() == 4);
        REQUIRE(result->lhs.isOpen());
        REQUIRE(result->rhs.value->intValue() == 5);
        REQUIRE(result->rhs.isOpen());
    }

    SECTION("ones with open side") {
        auto i1 = makeLessThan(5, true);
        auto i2 = makeGreaterThan(1, false);
        auto i3 = makeGreaterThan(4, false);
        auto i4 = makeRange(2, true, 8, true);
        auto i5 = makeLessThan(7, true);
        auto i6 = makeRange(2, false, 5, false);

        auto result = RangeCondition::intersect({i1, i2, i3, i4, i5, i6});
        REQUIRE(result->lhs.value->intValue() == 4);
        REQUIRE(result->lhs.isOpen());
        REQUIRE(result->rhs.value->intValue() == 5);
        REQUIRE(result->rhs.isOpen());
    }

    SECTION("with string literal") {
        auto i1 = makeLessThan("puppy", true);
        auto i2 = makeGreaterThan("dog", false);
        auto i3 = makeRange("cat", false, "wonder", true);

        auto result = RangeCondition::intersect({i1, i2, i3});
        REQUIRE(result->lhs.value->stringValue() == "dog");
        REQUIRE(result->lhs.isOpen());
        REQUIRE(result->rhs.value->stringValue() == "puppy");
        REQUIRE(result->rhs.isClose());
    }
}
