#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

int f() {
    return 1;
}

TEST_CASE("compilation check", "[comp]") {
    REQUIRE(f() == 1);
}