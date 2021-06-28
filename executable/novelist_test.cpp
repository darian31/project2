#include <catch.hpp>
#include "pages.hpp"

TEST_CASE("Test1"){
    CHECK(checkid("123") == true);
}