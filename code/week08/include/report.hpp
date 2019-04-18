#include <map>
#include <string>
#include <vector>

namespace lcsc::data {
class report {
  public:
    report(std::string title);

    template <typename... Ts>
    void columns(std::string x, Ts... rest) {
        columns_.push_back(x);
        columns(rest...);
    }
    void columns() {}

    template <typename... Ts>
    void row(Ts... entries) {
        auto r = std::vector<std::string>{entries...};
        rows_.push_back(r);
    }

  void save_json(std::string filename);
  void save_csv(std::string filename);

  private:
    std::vector<std::string> columns_;
    std::vector<std::vector<std::string>> rows_;
};

} // namespace lcsc::data
