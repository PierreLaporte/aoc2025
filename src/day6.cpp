#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/utils.hpp"
#include "../include/days.hpp"
#include <format>
#include <cstring>

class Operator{
    protected: 
        std::span<const int64_t> values;
        int64_t res;
    public:
        virtual ~Operator() {};
        int64_t op() {
            return res;
        }
};

class Multiplier: public Operator{
    public:
        Multiplier(std::span<const int64_t> v){
            res = 1;
            values = v;
            for (size_t i=0; i<v.size(); i++){
                res *= values[i];
            }
        }

        std::string print(){
            std::string to_print = std::format("Multiplier : {}",values[0]);
            for (size_t i=1; i<values.size(); i++){
                to_print.append(std::format("*{}", values[i]));
            }
            to_print.append(std::format(" = {}", res));
            return to_print;
        }
};

class Adder: public Operator{
    public:
        Adder(std::span<const int64_t> v){
            res = 0;
            values = v;
            for (size_t i=0; i<v.size(); i++){
                res += values[i];
            }
        }

        std::string print(){
            std::string to_print = std::format("Adder : {}",values[0]);
            for (size_t i=1; i<values.size(); i++){
                to_print.append(std::format("+{}", values[i]));
            }
            to_print.append(std::format(" = {}", res));
            return to_print;
        }
};

int64_t op(std::span<const int64_t> values, std::string_view oper){
    if (oper == "*"){
        Multiplier mult(values);
        std::cout << mult.print() << std::endl;
        return mult.op();
    } else if (oper == "+"){
        Adder add(values);
        std::cout << add.print() << std::endl;
        return add.op();
    } else{
        std::cerr << "invalid operation: " << oper << std::endl;
        std::exit(1);
    }
}

std::vector<int64_t> transpose_numbers(std::array<std::string, 4> input){
    size_t max_size = 0;
    for (size_t i = 0 ; i<input.size(); i++){
        if (input[i].size() > max_size){
            max_size = input[i].size();
        }
    }
    std::vector<std::string> transposed(max_size);
    for(size_t i=0; i<input.size(); i++){ 
        for (size_t j=0; j<input[i].size(); j++){
            std::cout << "je pushe " << input[i][j] << " dans " << j+max_size-input[i].size() << std::endl;
            transposed[j+max_size-input[i].size()].push_back(input[i][j]);
        }
    }
    std::vector<std::int64_t> transposed_int;
    transposed_int.reserve(transposed.size());

    for(size_t i=0; i<transposed.size(); i++){
        transposed_int.push_back(utils::to_number<int64_t>(transposed[i]));
    }

    return transposed_int;
}

void Day6::solve(){
    std::vector<std::string> input = utils::read_input("inputs/6.txt");
    if (input.size() < 1)
    {
        std::cerr << "input is empty" << std::endl;
        std::exit(1);
    }
    
    std::vector<std::vector<std::string>> values(input.size());

    for(size_t i=0; i<input.size(); i++){
        std::stringstream ss(input[i]);
        std::string val;
        while (ss >> val){
            values[i].push_back(val);
        }
    }

    int64_t sum_first_part = 0;
    int64_t sum_second_part = 0;
    for(size_t i=0; i<values[0].size(); i++){
        std::cout << "=======================================================" << std::endl;
        std::array<int64_t, 4> grouped_vals = {
            utils::to_number<int64_t>(values[0][i]), 
            utils::to_number<int64_t>(values[1][i]),
            utils::to_number<int64_t>(values[2][i]),
            utils::to_number<int64_t>(values[3][i])
        };
        for(auto grouped_val:grouped_vals){
            std::cout << grouped_val << std::endl;
        }
        std::string_view oper = values[4][i];
        sum_first_part += op(grouped_vals, oper);
        std::array<std::string, 4> grouped_vals_str = {
            values[0][i], 
            values[1][i],
            values[2][i],
            values[3][i]
        };
        std::vector<int64_t> transposed_values = transpose_numbers(grouped_vals_str);
        sum_second_part += op(transposed_values, oper);
        std::cout << "sum first part = " << sum_first_part << std::endl;
        std::cout << "sum second part = " << sum_second_part << std::endl;
    }
}