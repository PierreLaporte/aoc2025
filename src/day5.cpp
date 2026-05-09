#include <iostream>
#include "../include/utils.hpp"
#include "../include/days.hpp"
#include <charconv>
#include <algorithm>

class IngredientList{
    private:
        std::vector<std::pair<size_t,size_t>> m_ranges;
        std::vector<size_t> m_ingredients;

    public:
        IngredientList(std::vector<std::string> input){
            // handle ranges
            size_t break_index = 0;
            for(size_t i = 0; i < input.size(); i++){
                if (input[i].empty()) {break_index = i; break;}
                std::vector<std::string_view> split = utils::split_fast(input[i], '-');
                if (split.size() != 2){
                    std::cout << "incorrectly formatted range line: " << input[i] << '\n';
                    std::exit(1);
                }
                size_t range_start = utils::to_number<size_t>(split[0]);
                size_t range_end = utils::to_number<size_t>(split[1]);
                m_ranges.emplace_back(range_start, range_end);
            }

            for(size_t i = break_index+1; i < input.size(); i++){
                m_ingredients.push_back(utils::to_number<size_t>(input[i]));
            }
            std::ranges::sort(m_ranges);
        }

        void display_ranges() const{
            std::cout << "================== " << m_ranges.size() << " FRESH RANGES =================" << '\n';
            for (auto range: m_ranges){
                std::cout << utils::print_range(range) << "\n"; 
            }
            std::cout << '\n';
        }

        size_t nb_ranges(){
            return m_ranges.size();
        }

        void merge_ranges(){
            // std::cout << "=========== MERGING " << m_ranges.size() << " RANGES ==============" << std::endl; 
            std::vector<std::pair<size_t,size_t>> new_ranges;
            size_t i = 0;
            bool merged = false;
            while (i < m_ranges.size()-1){
                if (m_ranges[i].second >= m_ranges[i+1].first-1){
                    std::pair<size_t,size_t> new_range;
                    if (m_ranges[i].second >= m_ranges[i+1].second){
                        new_range = {m_ranges[i].first, m_ranges[i].second};
                    } else{
                        new_range = {m_ranges[i].first, m_ranges[i+1].second};
                    }
                    // std::cout << "merging ranges " << utils::print_range(m_ranges[i]) << " and " << utils::print_range(m_ranges[i+1]) << " ===> " << utils::print_range(new_range) << std::endl;
                    new_ranges.emplace_back(new_range);
                    i+=2;
                    merged = true;
                } else {
                    new_ranges.emplace_back(m_ranges[i]);
                    i++;
                    merged = false;
                }
            }
            if (!merged){
                new_ranges.emplace_back(m_ranges[m_ranges.size()-1]);
            }
            m_ranges = new_ranges;
            std::ranges::sort(m_ranges);
        }
        
        size_t count_fresh_ingredients(){
            size_t count = 0;
            for(auto ingredient: m_ingredients){
                if (is_fresh(ingredient)) {
                    count++;
                }
            }
            return count;
        }

        size_t count_all_possible_fresh_ingredients(){
            size_t count = 0;
            for(auto range: m_ranges){
                count += (range.second - range.first) + 1;
            }
            return count;
        }

        bool is_fresh(size_t ingredient){
            for (auto range: m_ranges){
                if (ingredient >= range.first && ingredient <= range.second){
                    return true;
                }
            }
            return false;
        }
};



void Day5::solve(){
    std::vector<std::string> input = utils::read_input("inputs/5.txt");
    if (input.size() < 1)
    {
        std::cerr << "input is empty" << std::endl;
        std::exit(1);
    }
    IngredientList ingredient_list = IngredientList(input);
    ingredient_list.display_ranges();
    size_t prev_nb_ranges = 0;
    while (ingredient_list.nb_ranges() != prev_nb_ranges){
        prev_nb_ranges = ingredient_list.nb_ranges();
        ingredient_list.merge_ranges();
    }
    ingredient_list.display_ranges();
    std::cout << "fresh ingredients = " << ingredient_list.count_fresh_ingredients() << std::endl;
    std::cout << "all possible fresh ingredients = " << ingredient_list.count_all_possible_fresh_ingredients() << std::endl;
}