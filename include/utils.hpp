#pragma once
#include <vector>
#include <string>

namespace utils
{
    std::vector<std::string> read_input(const std::string &filename);
    std::vector<std::string_view> split_fast(std::string_view str, char delimiter);
}