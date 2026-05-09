#include <iostream>
#include "../include/utils.hpp"
#include "../include/days.hpp"

class Positions{
    private:
        int m_nb_rows = 0;
        int m_nb_cols = 0;
        int m_accessible_sum = 0;
        std::vector<std::vector<bool>> grid;

    public:
        Positions(const std::vector<std::string> & raw_positions) {
            int nb_raw_lines = raw_positions.size();
            int nb_raw_cols = raw_positions[0].size();

            grid.assign(nb_raw_lines + 2, std::vector<bool>(nb_raw_cols + 2, false));
            m_nb_rows = nb_raw_lines + 2;
            m_nb_cols = nb_raw_cols + 2;

            for (int row = 0; row < nb_raw_lines; row++) {
                for(int col = 0; col < nb_raw_cols; col++){
                    if (raw_positions[row][col] == '@'){
                        grid[row+1][col+1] = true;
                    }
                } 
            }

            for (int i = 1; i < m_nb_rows-1; i++){
                for (int j = 1; j < m_nb_cols-1; j++){
                    if (grid[i][j] && is_accessible(i,j)) m_accessible_sum++;
                }
            }
        }

        bool is_accessible(int i, int j) const{
            int adjacent = grid[i-1][j-1] + grid[i-1][j] + grid[i-1][j+1] + 
            grid[i][j-1] + grid[i][j+1] + 
            grid[i+1][j-1] + grid[i+1][j] + grid[i+1][j+1];
            return adjacent < 4;
        }

        void display() const{
            for (int row = 0; row < m_nb_rows; row++){
                for(int col = 0; col < m_nb_cols; col++){
                    if (grid[row][col]) {
                        if (is_accessible(row,col)) std::cout << "A" ;else std::cout << "X";
                    } else {
                        std::cout << ".";
                    }
                }
                std::cout << std::endl;
            }
        }

        int accessible_sum() const{
            return m_accessible_sum;
        }
};


void Day4::solve(){
    std::vector<std::string> raw_positions = utils::read_input("inputs/4.txt");
    if (raw_positions.size() < 1)
    {
        std::cerr << "input is empty" << std::endl;
        std::exit(1);
    }

    Positions positions = Positions(raw_positions);
    positions.display();
    size_t sum_second_part = 0;
    std::cout << "part 1: sum = " << positions.accessible_sum() << std::endl;
    std::cout << "part 2: sum = " << sum_second_part << std::endl;
}