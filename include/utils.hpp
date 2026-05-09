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

    template <typename T>
    requires std::is_arithmetic_v<T>
    std::optional<T> to_number(std::string_view sv){
        T value;
        auto [ptr, err] = std::from_chars(sv.data(), sv.data() + sv.size(), value);

        // Vérification : 
        // 1. err == {} : Pas d'erreur (ni overflow, ni format)
        // 2. ptr == sv.data() + sv.size() : On a consommé toute la chaîne
        if (err == std::errc{} && ptr == sv.data() + sv.size()) {
            return value;
        } else if (err )

        return std::nullopt;
    }
}