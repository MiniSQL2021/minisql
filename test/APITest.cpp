#include "catch2/catch.hpp"

#include "api/API.hpp"

TEST_CASE("API", "[api]") {
    Interpreter interpreter;
    BufferManager bufferManager;
    CatalogManager catalogManager(bufferManager);
    RecordManager recordManager(bufferManager);
    API api(interpreter, catalogManager, recordManager);

    SECTION("create table") {
        REQUIRE_NOTHROW([&]() {
            api.directlyInput("create table person ( \n"
                              "\theight float unique,\n"
                              "\tpid int,\n"
                              "\tname char(32),\n"
                              "\tidentity char(128) unique,\n"
                              "\tage int unique,\n"
                              "\tprimary key(pid)\n"
                              ");");
        });
    }

    SECTION("insert") {

    }

    SECTION("delete") {

    }

    SECTION("create index when table is empty") {

    }

    SECTION("create index when table is not empty") {

    }

    SECTION("drop table") {
        REQUIRE_NOTHROW([&]() {
            api.directlyInput("drop table person;");
        });
    }
}
