#include "catch2/catch.hpp"
#include "interpreter/Interpreter.hpp"

TEST_CASE("Interpret queries", "[interpreter:queries]") {
    Interpreter interpreter;

    SECTION("create table") {
        std::stringstream ss(
                "create table students \n(id int unique, name char(20), balance float, primary key (id));");
        interpreter.onCreateTableQuery([](QueryPointer<CreateTableQuery> query) {
            REQUIRE(query->tableName == "students");
            auto columns = query->columns;
            REQUIRE(columns.size() == 3);
            REQUIRE(columns[0].name == "id");
            REQUIRE(columns[0].type == LiteralType::Int);
            REQUIRE(columns[0].unique);
            REQUIRE(columns[1].name == "name");
            REQUIRE(columns[1].type == LiteralType::String);
            REQUIRE(columns[1].maxLength == 20);
            REQUIRE(columns[2].name == "balance");
            REQUIRE(columns[2].type == LiteralType::Float);
            REQUIRE(query->primaryKey == "id");
        });
        interpreter.parse(ss);
    }

    SECTION("create index") {
        std::stringstream ss("create index index_name_students on students(name);");
        interpreter.onCreateIndexQuery([](QueryPointer<CreateIndexQuery> query) {
            REQUIRE(query->tableName == "students");
            REQUIRE(query->columnName == "name");
            REQUIRE(query->indexName == "index_name_students");
        });
        interpreter.parse(ss);
    }

    SECTION("drop table") {
        std::stringstream ss("drop table students;");
        interpreter.onDropTableQuery([](QueryPointer<DropTableQuery> query) {
            REQUIRE(query->tableName == "students");
        });
        interpreter.parse(ss);
    }

    SECTION("drop index") {
        std::stringstream ss("drop index index_name_students;");
        interpreter.onDropIndexQuery([](QueryPointer<DropIndexQuery> query) {
            REQUIRE(query->indexName == "index_name_students");
        });
        interpreter.parse(ss);
    }

    SECTION("select") {
        std::stringstream ss("select * from students \nwhere id=1 and name>\"cobalt\" and balance<=200.0;");
        interpreter.onSelectQuery([](QueryPointer<SelectQuery> query) {
            REQUIRE(query->tableName == "students");
            auto conditions = query->conditions;
            REQUIRE(conditions.size() == 3);
            REQUIRE(conditions[0].columnName == "id");
            REQUIRE(conditions[0].binaryOperator == BinaryOpearator::Equal);
            REQUIRE(conditions[0].value.intValue() == 1);
            REQUIRE(conditions[1].columnName == "name");
            REQUIRE(conditions[1].binaryOperator == BinaryOpearator::GreaterThan);
            REQUIRE(conditions[1].value.stringValue() == "cobalt");
            REQUIRE(conditions[2].columnName == "balance");
            REQUIRE(conditions[2].binaryOperator == BinaryOpearator::LessThanOrEqual);
            REQUIRE(conditions[2].value.floatValue() == 200.0F);
        });
        interpreter.parse(ss);
    }

    SECTION("delete") {
        std::stringstream ss("delete from students \nwhere id=1 and name>\"cobalt\" and balance<=200.0;");
        interpreter.onDeleteQuery([](QueryPointer<DeleteQuery> query) {
            REQUIRE(query->tableName == "students");
            auto conditions = query->conditions;
            REQUIRE(conditions.size() == 3);
            REQUIRE(conditions[0].columnName == "id");
            REQUIRE(conditions[0].binaryOperator == BinaryOpearator::Equal);
            REQUIRE(conditions[0].value.intValue() == 1);
            REQUIRE(conditions[1].columnName == "name");
            REQUIRE(conditions[1].binaryOperator == BinaryOpearator::GreaterThan);
            REQUIRE(conditions[1].value.stringValue() == "cobalt");
            REQUIRE(conditions[2].columnName == "balance");
            REQUIRE(conditions[2].binaryOperator == BinaryOpearator::LessThanOrEqual);
            REQUIRE(conditions[2].value.floatValue() == 200.0F);
        });
        interpreter.parse(ss);
    }

    SECTION("insert") {
        std::stringstream ss("insert into students values \n(1, \"cobalt\", 200.0);");
        interpreter.onInsertQuery([](QueryPointer<InsertQuery> query) {
            REQUIRE(query->tableName == "students");
            auto values = query->values;
            REQUIRE(values.size() == 3);
            REQUIRE(values[0].intValue() == 1);
            REQUIRE(values[1].stringValue() == "cobalt");
            REQUIRE(values[2].floatValue() == 200.0F);
        });
        interpreter.parse(ss);
    }
}
