#include <iostream>
#include <set>
#include "../include/utils.hpp"
#include "../include/day.hpp"

class Day2 : public Solver<Day2>
{
private:
    size_t sum_first_part;
    size_t sum_second_part;

    void compute_sums(std::string_view start_id, std::string_view end_id)
    {
    }

public:
    Day2() : Solver<Day2>()
    {
        this->sum_first_part = 0;
        this->sum_second_part = 0;
    }

    void solve()
    {
        std::vector<std::string> lines = utils::read_input("inputs/3.txt");
        if (lines.size() < 1)
        {
            std::cerr << "input is empty" << std::endl;
            std::exit(1);
        }
        size_t sum_first_part = 0;

        std::cout << "first part answer = " << sum_first_part << std::endl;
        // std::cout << "second part answer = " << sum_second_part << std::endl;
    }
};