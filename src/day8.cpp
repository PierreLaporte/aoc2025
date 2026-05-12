#include <iostream>
#include "../include/utils.hpp"
#include "../include/days.hpp"

class Positions{
private:
    std::vector<uint32_t> x,y,z;
    size_t size;
    std::vector<std::vector<uint64_t>> distances;
    std::vector<std::vector<size_t>> groups;

public:
    Positions() = default;

    void add_position(uint32_t ix,uint32_t iy,uint32_t iz){
        x.push_back(ix);
        y.push_back(iy);
        z.push_back(iz);
        size++;
    }

    void connect_n_closest(size_t n){

    }

    
    std::vector<uint64_t> euclidean_distance(){
        std::vector<std::vector<uint64_t>> distances(size, std::vector<uint64_t>());
        #pragma omp simd
        for (size_t i=0; i<size; i++){
            for (size_t j=i; j<size; j++){
                uint64_t dx = static_cast<uint64_t>(x[i]) - static_cast<uint64_t>(x[j]);
                uint64_t dy = static_cast<uint64_t>(y[i]) - static_cast<uint64_t>(y[j]);
                uint64_t dz = static_cast<uint64_t>(z[i]) - static_cast<uint64_t>(z[j]);
            }
            
        }
        // results[dx*dx + dy*dy + dz*dz
    }
};


void Day7::solve(){
    std::vector<std::string> input = utils::read_input("inputs/7.txt");
    if (input.size() < 1)
    {
        std::cerr << "input is empty" << std::endl;
        std::exit(1);
    }

}