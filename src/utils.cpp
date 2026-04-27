#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace utils
{
    std::vector<std::string> read_input(const std::string &filename)
    {
        std::ifstream input_file{filename};

        if (!input_file)
        {
            std::cerr << "could not open file " << filename << std::endl;
            std::exit(1);
        }

        std::vector<std::string> lines{};
        std::string line{};
        while (input_file >> line)
        {
            lines.push_back(line);
        }

        return lines;
    }

    std::vector<std::string_view> split_fast(std::string_view str, char delimiter)
    {
        std::vector<std::string_view> output;
        size_t first = 0;

        while (first < str.size())
        {
            size_t second = str.find(delimiter, first);
            if (second == std::string_view::npos)
                second = str.size();
            output.emplace_back(str.substr(first, second - first));
            first = second + 1;
        }

        return output;
    }
}