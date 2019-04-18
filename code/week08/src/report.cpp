#include <fstream>
#include <sstream>

#include "nlohmann/json.hpp"
#include "report.hpp"

namespace lcsc::data {

report::report(std::string title) {}

void report::save_json(std::string filename) {
    auto j = nlohmann::json();
    j["columns"] = columns_;
    j["rows"] = rows_;

    auto fout = std::ofstream(filename);
    fout << j.dump() << "\n";
}

void report::save_csv(std::string filename) {
    auto fout = std::ofstream(filename);

    auto comma_separated = [](std::vector<std::string> xs) -> std::string {
        auto ss = std::stringstream();
        auto sep = std::string("");
        for (auto x : xs) {
            ss << sep << x;
            sep = ",";
        }
        ss << "\n";

        return ss.str();
    };

    fout << comma_separated(columns_);
    for (auto row : rows_) {
        fout << comma_separated(row);
    }
}

} // namespace lcsc::data
