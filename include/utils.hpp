#pragma once
#include <vector>
#include <string>
#include <charconv>
#include <string_view>
#include <optional>
#include <concepts> 

namespace utils
{
    std::vector<std::string> read_input(const std::string &filename);
    std::vector<std::string_view> split_fast(std::string_view str, char delimiter);
    std::string print_range(const std::pair<size_t, size_t>& range);

    template <typename T>
    requires std::is_arithmetic_v<T>
    T to_number(std::string_view sv){
        T value;
        auto [ptr, err] = std::from_chars(sv.data(), sv.data() + sv.size(), value);

        if (err == std::errc{} && ptr != sv.data() + sv.size()){
                throw std::runtime_error("cannot convert " + std::string(sv) + " to number: string is not entirely numerical" + '\n');
        } else if (err != std::errc{}){
            std::error_code code = std::make_error_code(err);
            throw std::runtime_error("cannot convert " + std::string(sv) + " to number: " + code.message() + '\n'); 
        }
        return value;
    }
}