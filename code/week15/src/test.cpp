#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "ranges.hpp"

using namespace ranges;

TEST_CASE("Basic range", "[range]")
{
    auto xs = std::vector<int>();
    for (auto x : range(4)) {
        xs.push_back(x);
    }
    REQUIRE(xs == std::vector<int>{0, 1, 2, 3});
}

TEST_CASE("Benchmark", "[benchmark]")
{
    auto ws = std::vector<int>(1'000'000);
    ws.reserve(1'000'000);
    BENCHMARK("Iterate a large range")
    {
        for (auto x : range(1'000'000)) {
            ws.push_back(x);
        }
    }
    REQUIRE(ws[ws.size() - 1] == 999'999);
}
