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

template<typename T>
ComparisonCondition makeCondition(const std::string &name, BinaryOpearator op, T value) {
    return ComparisonCondition(name, op, Literal(value));
}

TEST_CASE("Intersect range conditions", "[condition:intersect]") {

    SECTION("regular ones") {
        auto result = RangeCondition::intersect(
                {
                        makeRange(4, true, 5, true),
                        makeRange(1, false, 6, true),
                        makeRange(4, false, 5, false),
                        makeRange(2, true, 8, true),
                        makeRange(3, true, 7, true),
                        makeRange(2, false, 7, false),
                });
        REQUIRE(result->lhs.value->intValue() == 4);
        REQUIRE(result->lhs.isOpen());
        REQUIRE(result->rhs.value->intValue() == 5);
        REQUIRE(result->rhs.isOpen());
    }

    SECTION("ones with open side") {
        auto result = RangeCondition::intersect(
                {
                        makeLessThan(5, true),
                        makeGreaterThan(1, false),
                        makeGreaterThan(4, false),
                        makeRange(2, true, 8, true),
                        makeLessThan(7, true),
                        makeRange(2, false, 5, false),
                });
        REQUIRE(result->lhs.value->intValue() == 4);
        REQUIRE(result->lhs.isOpen());
        REQUIRE(result->rhs.value->intValue() == 5);
        REQUIRE(result->rhs.isOpen());
    }

    SECTION("with string literal") {
        auto result = RangeCondition::intersect(
                {
                        makeLessThan("puppy", true),
                        makeGreaterThan("dog", false),
                        makeRange("cat", false, "wonder", true),
                });
        REQUIRE(result->lhs.value->stringValue() == "dog");
        REQUIRE(result->lhs.isOpen());
        REQUIRE(result->rhs.value->stringValue() == "puppy");
        REQUIRE(result->rhs.isClose());
    }
}

TEST_CASE("Combine comparison conditions", "[condition:combine]") {
    auto result = combineConditions(
            {
                    makeCondition("id", BinaryOpearator::GreaterThan, 3),
                    makeCondition("id", BinaryOpearator::LessThan, 8),
                    makeCondition("id", BinaryOpearator::Equal, 6),
                    makeCondition("id", BinaryOpearator::NotEqual, 5),
                    makeCondition("name", BinaryOpearator::GreaterThan, "cat"),
                    makeCondition("name", BinaryOpearator::Equal, "cat"),
                    makeCondition("height", BinaryOpearator::GreaterThanOrEqual, 10.0F),
                    makeCondition("height", BinaryOpearator::LessThan, 12.0F),
                    makeCondition("height", BinaryOpearator::Equal, 11.0F),
                    makeCondition("height", BinaryOpearator::NotEqual, 11.5F),
                    makeCondition("height", BinaryOpearator::NotEqual, 11.6F),
                    makeCondition("height", BinaryOpearator::NotEqual, 5.0F),
                    makeCondition("age", BinaryOpearator::Equal, 5),
                    makeCondition("age", BinaryOpearator::Equal, 6),
                    makeCondition("balance", BinaryOpearator::Equal, 500.0F),
                    makeCondition("balance", BinaryOpearator::NotEqual, 500.0F),
                    makeCondition("balance", BinaryOpearator::NotEqual, 600.0F),
                    makeCondition("cakeCount", BinaryOpearator::GreaterThanOrEqual, 3),
                    makeCondition("cakeCount", BinaryOpearator::LessThanOrEqual, 3),
            });

    SECTION("regular one") {
        REQUIRE(result["id"]);
        auto list = *result["id"];
        REQUIRE(list.size() == 2);
        REQUIRE(std::holds_alternative<RangeCondition>(list[0]));
        auto range = std::get<RangeCondition>(list[0]);
        REQUIRE(range.lhs.value->intValue() == 3);
        REQUIRE(range.rhs.value->intValue() == 8);
        auto point = std::get<PointCondition>(list[1]);
        REQUIRE(point.value.intValue() == 5);
        REQUIRE(point.isNotEqual());
    }

    SECTION("open range and a point at its end: empty") {
        REQUIRE(!result["name"]);
    }

    SECTION("regular one with many not-equals") {
        REQUIRE(result["height"]);
        auto list = *result["height"];
        REQUIRE(list.size() == 3);
        REQUIRE(std::holds_alternative<RangeCondition>(list[0]));
        auto range = std::get<RangeCondition>(list[0]);
        REQUIRE(range.lhs.value->floatValue() == 10.0F);
        REQUIRE(range.rhs.value->floatValue() == 12.0F);
        auto point1 = std::get<PointCondition>(list[1]);
        REQUIRE(point1.value.floatValue() == 11.5F);
        REQUIRE(point1.isNotEqual());
        auto point2 = std::get<PointCondition>(list[2]);
        REQUIRE(point2.value.floatValue() == 11.6F);
        REQUIRE(point2.isNotEqual());
    }

    SECTION("two different equals: empty") {
        REQUIRE(!result["age"]);
    }

    SECTION("equal and not equal: empty") {
        REQUIRE(!result["balance"]);
    }

    SECTION("two ranges intersect by one point") {
        REQUIRE(result["cakeCount"]);
        auto list = *result["cakeCount"];
        REQUIRE(list.size() == 1);
        auto point = std::get<PointCondition>(list[0]);
        REQUIRE(point.value.intValue() == 3);
        REQUIRE(point.isEqual());
    }
}
