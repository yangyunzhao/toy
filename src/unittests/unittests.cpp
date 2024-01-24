#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <spdlog/spdlog.h>

struct GlobalSetup {
    GlobalSetup() {
        spdlog::set_level(spdlog::level::warn);
    }

    ~GlobalSetup() {
        spdlog::info("Global cleanup");
    }
};
GlobalSetup setup;

TEST_CASE("Factorials are computed", "[factorial]") {
    REQUIRE(1 == 1);
    REQUIRE(2 == 2);
    REQUIRE(6 == 6);
}