#include <iostream>
#include <set>
#include "../include/utils.hpp"
#include <charconv>
#include "../include/day2.hpp"

bool is_fake_first_criteria(std::string_view id)
{
    size_t half_size = id.size() / 2;

    if (id.size() % 2 != 0)
    {
        return false;
    }
    else
    {
        std::string_view first_half = id.substr(0, half_size);
        std::string_view second_half = id.substr(half_size, half_size);
        if (first_half == second_half)
        {
            // std::cout << "first half: " << first_half << "; second half " << second_half << std::endl;
            return true;
        }
    }
    return false;
}

bool is_fake_second_criteria(std::string_view id)
{
    // std::cout << "================= " << id << "==================" << std::endl;
    for (size_t window = 1; window <= id.size() / 2; window++)
    {
        // std::cout << "window = " << window << " ==> ";
        std::set<std::string_view> chunks;
        for (size_t i = 0; i < id.size(); i += window)
        {
            std::string_view chunk = id.substr(i, window);
            // std::cout << chunk << "; ";
            chunks.insert(chunk);
        }
        // std::cout << std::endl;
        if (chunks.size() == 1)
        {
            return true;
        }
    }
    return false;
}

void Day2::compute_sums(std::string_view start_id, std::string_view end_id)
{
    // std::cout << "========= range [" << start_id << "; " << end_id << "] ========" << std::endl;
    size_t start_id_int, end_id_int;
    std::from_chars(start_id.data(), start_id.data() + start_id.size(), start_id_int);
    std::from_chars(end_id.data(), end_id.data() + end_id.size(), end_id_int);
    for (size_t id = start_id_int; id <= end_id_int; id++)
    {
        std::string string_id = std::to_string(id);
        if (is_fake_first_criteria(string_id))
        {
            // std::cout << id << " is fake (first criteria)" << std::endl;
            this->sum_first_part += id;
            // std::cout << "sum first = " << sum << std::endl;
        }
        if (is_fake_second_criteria(string_id))
        {
            // std::cout << id << " is fake (second criteria)" << std::endl;
            this->sum_second_part += id;
            // std::cout << "sum second = " << this->sum_second_part << std::endl;
        }
    }
}

void Day2::solve()
{
    std::vector<std::string> lines = utils::read_input("inputs/2.txt");
    if (lines.size() < 1)
    {
        std::cerr << "input is empty" << std::endl;
        std::exit(1);
    }
    std::vector<std::string_view> id_ranges = utils::split_fast(lines[0], ',');
    for (std::string_view range : id_ranges)
    {
        std::vector<std::string_view> ids = utils::split_fast(range, '-');
        if (ids.size() != 2)
        {
            std::cerr << "should be only 2 ids per range but we have " << ids.size() << std::endl;
        }
        this->compute_sums(ids[0], ids[1]);
    }

    std::cout << "first part answer = " << this->sum_first_part << std::endl;
    std::cout << "second part answer = " << this->sum_second_part << std::endl;
}
