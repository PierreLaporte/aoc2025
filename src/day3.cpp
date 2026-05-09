#include <iostream>
#include <set>
#include "../include/utils.hpp"
#include "../include/days.hpp"
#include <format>

size_t first_part(std::string_view bank){
    int max_val = 0;
    int max_val_index = -1;
    for (size_t i = 0; i < bank.size()-1; i++)
    {
        int val = bank[i] - '0';
        if (val > max_val){
            max_val = val;
            max_val_index = i;
        }
    }
    int next_max_val = -1;
    for (char c: bank.substr(max_val_index+1))
    {
        int val = c - '0';
        if (val > next_max_val){
            next_max_val = val;
        }
    }
    std::string result = std::format("{}{}", max_val, next_max_val);
    // std::cout << bank << "===>" << result << std::endl;
    return std::stoi(result);
}

struct IndexedVal{
    int val;
    int index;
};

IndexedVal find_max_in(std::string_view s, int start_index, int remaining_digits){
    int length_to_search = s.size() - start_index - remaining_digits;
    std::cout << "start index = " << start_index << "; remaining digits = " << remaining_digits << "; length = "<< length_to_search << std::endl;
    IndexedVal max_val = {.val = 0, .index = start_index};
    for(int i = start_index + 1; i < start_index + length_to_search; i++){
        int val = s[i] - '0';
        if (val > max_val.val) {
            max_val.val = val;
            max_val.index = i;
            std::cout << "new max = " << max_val.val << " (index " << max_val.index << ")" << std::endl;    
        }
    }
    return max_val; 
}


size_t second_part(std::string_view bank){
    std::cout << "=================================" << std::endl;
    std::cout << "BANK: " << bank << std::endl;
    std::cout << "=================================" << std::endl;
    int remaining_digits = 11;
    IndexedVal max_val = {.val=0, .index=-1}; 
    std::string max_val_str = "";
    while (remaining_digits >= 0){
        std::cout << "max val : [index: " << max_val.index << "; val: " << max_val.val << "]" << std::endl; 
        max_val = find_max_in(bank, max_val.index, remaining_digits);
        max_val_str = std::format("{}{}", max_val_str, max_val.val);
        std::cout << max_val_str << std::endl;
        remaining_digits--;
    }
    return std::stoll(max_val_str);
}


void Day3::solve(){
    std::vector<std::string> banks = utils::read_input("inputs/3.txt");
    if (banks.size() < 1)
    {
        std::cerr << "input is empty" << std::endl;
        std::exit(1);
    }
    size_t sum_first_part = 0;
    size_t sum_second_part = 0;
    for (std::string_view bank: banks){
        sum_first_part += first_part(bank);
        sum_second_part += second_part(bank);
    }
    std::cout << "part 1: sum = " << sum_first_part << std::endl;
    std::cout << "part 2: sum = " << sum_second_part << std::endl;
}