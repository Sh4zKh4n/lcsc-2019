#include <chrono>
#include <iostream>
#include <random>

#include "report.hpp"
#include "timer.hpp"

using namespace lcsc::data;
using namespace std::string_literals;

template <typename Engine>
void test_engine(report& table, std::string name) {
    auto r = std::random_device{};
    auto engine = Engine(r());
    auto dt = timer();

    auto sum = 0;
    for (int i = 0; i < 1'000'000; ++i) {
        sum += engine();
    }
    auto t1 = dt.get<std::milli>();

    // (we use sum to avoid the compiler optimizing it out)
    std::cout << "random sum: " << sum << "\n";

    table.row(name, "generate a million", std::to_string(t1));
}

int main() {
    auto table = report("<random> benchmarks");
    table.columns("engine", "test", "time");

    test_engine<std::minstd_rand0>(table, "park_miller");
    test_engine<std::mt19937>(table, "mersenne_twister");

    table.save_csv("data/benchmark_random.csv");

    std::cout << "Finished running benchmarks.\n";

    return 0;
}
