#include <cstdint>
#include <string_view>

class Day2
{
private:
    std::size_t sum_first_part = 0;
    std::size_t sum_second_part = 0;
    void compute_sums(std::string_view start_id, std::string_view end_id);

public:
    Day2() = default;
    void solve();
};