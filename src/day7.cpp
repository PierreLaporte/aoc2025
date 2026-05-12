#include <iostream>
#include "../include/utils.hpp"
#include "../include/days.hpp"
#include <format>
#include <algorithm>
#include <set>
#include <map>

void Day7::solve(){
    std::vector<std::string> input = utils::read_input("inputs/7.txt");
    if (input.size() < 1)
    {
        std::cerr << "input is empty" << std::endl;
        std::exit(1);
    }

    int start = 0;
    for (size_t i=0; i<input[0].size(); i++){
        if (input[0][i] == 'S'){
            start = i;
        }
    }
    std::vector<std::set<int>> splitters(input.size()/2 - 1);  
    size_t pos_index = 0;
    for (size_t i=2; i<input.size(); i+=2){
        for (size_t j=0; j<input[i].size(); j++){
            if (input[i][j] == '^'){
                splitters[pos_index].insert(j);
            }
        }
        pos_index++;
    }
    
    std::cout << "================================= POSITIONS ===========================" << std::endl;
    for (auto& line: splitters){
        for (auto& pos: line){
            std::cout << pos << ' ';
        }
        std::cout << std::endl;
    }

    int nb_splits = 0;  
    std::map<int,uint64_t> beams{{start,1}};
    for (size_t i=0; i<splitters.size(); i++){
        std::set<int> to_delete;
        std::cout << "================ line " << i << "===============" << std::endl;
        for(const auto& [col,nb_beams]: beams){
            if (std::binary_search(splitters[i].begin(), splitters[i].end(), col)){
                nb_splits++;
                beams[col-1]+=nb_beams;
                beams[col+1]+=nb_beams;
                beams[col] = 0;
            }
        }
        for(int beam_to_delete: to_delete){
            beams.erase(beam_to_delete);
        }
        std::cout << "beams = ";
        for (const auto& [col,nb_beams]: beams){
            std::cout << "[" << col << ": " << nb_beams << "] ";
        }
        std::cout << std::endl;
    }

    std::cout << "number of splits: " << nb_splits << std::endl;
    int64_t timeline_sum = 0;
    for (const auto& [col,nb_beams]: beams){
        timeline_sum+=nb_beams;
    }
    std::cout << "possible worlds: " << timeline_sum << std::endl;
}