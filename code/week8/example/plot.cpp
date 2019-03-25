#include <chrono>
#include <iostream>

#include "report.hpp"
#include "timer.hpp"

using namespace lcsc::data;

double f(double x) { return x * x; }

int main() {
    auto dt = timer();
    auto table = report("graph of f(x) = x * x");
    table.columns("x", "f(x)");

    for (double x = -10.0; x <= 10.0; x += 1.0) {
        table.row(std::to_string(x), std::to_string(f(x)));
    }

    table.save_json("data/fx.json");

    std::cout << "Generating plot took: " << dt.get<std::micro>() << " us\n";
    return 0;
}
