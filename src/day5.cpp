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
        IngredientList(const std::vector<std::string> & input){
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
            for (const auto & range: m_ranges){
                std::cout << utils::print_range(range) << "\n"; 
            }
            std::cout << '\n';
        }

        size_t nb_ranges() const {
            return m_ranges.size();
        }

        void merge_ranges(){
            std::ranges::sort(m_ranges, [](const auto& a, const auto& b) {
                if (a.first != b.first) return a.first < b.first;
                return a.second > b.second; 
            });
            std::vector<std::pair<size_t,size_t>> new_ranges;
            new_ranges.reserve(m_ranges.size());
            new_ranges.push_back(m_ranges[0]);    
        
            for (size_t i = 1; i < m_ranges.size(); i++){
                auto& last = new_ranges.back();
                auto& current = m_ranges[i];

                if (current.first <= last.second + 1){
                    last.second = std::max(last.second, current.second);
                } else{
                    new_ranges.push_back(current);
                }
            }
            m_ranges = std::move(new_ranges);
        }
        
        size_t count_fresh_ingredients() const {
            size_t count = 0;
            for(const auto & ingredient: m_ingredients){
                if (is_fresh(ingredient)) {
                    count++;
                }
            }
            return count;
        }

        size_t count_all_possible_fresh_ingredients() const{
            size_t count = 0;
            for(const auto & range: m_ranges){
                count += (range.second - range.first) + 1;
            }
            return count;
        }

        bool is_fresh(size_t ingredient) const{
            // Trouve le premier intervalle dont la fin >= ingredient
            auto it = std::lower_bound(m_ranges.begin(), m_ranges.end(), ingredient, 
                [](const std::pair<size_t, size_t>& range, size_t val) {
                    return range.second < val;
                });

            return it != m_ranges.end() && ingredient >= it->first;
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
    ingredient_list.merge_ranges();
    ingredient_list.display_ranges();
    std::cout << "fresh ingredients = " << ingredient_list.count_fresh_ingredients() << std::endl;
    std::cout << "all possible fresh ingredients = " << ingredient_list.count_all_possible_fresh_ingredients() << std::endl;
}