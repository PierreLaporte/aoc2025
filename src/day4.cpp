#include <iostream>
#include "../include/utils.hpp"
#include "../include/days.hpp"

class Positions{
    private:
        size_t m_nb_rows = 0;
        size_t m_nb_cols = 0;
        size_t m_accessible_sum = 0;
        size_t m_removable_sum  = 0;
        std::vector<bool> m_grid;

        [[nodiscard]] size_t idx(int row, int col) const {
            return row*m_nb_cols + col;
        }

    public:
        Positions(const std::vector<std::string> & raw_positions) :
        m_nb_rows(raw_positions.size()+2), 
        m_nb_cols(raw_positions[0].size()+2) 
        {
            m_grid.assign(m_nb_rows*m_nb_cols,  false);

            for (size_t row = 0; row < raw_positions.size(); row++) {
                for(size_t col = 0; col < raw_positions[0].size(); col++){
                    if (raw_positions[row][col] == '@'){
                        m_grid[idx(row+1, col+1)] = true;
                    }
                } 
            }

            compute_accessible_sum();
        }

        void compute_accessible_sum(){
            for (size_t i = 1; i < m_nb_rows-1; i++){
                for (size_t j = 1; j < m_nb_cols-1; j++){
                    if (is_accessible(i,j)) m_accessible_sum++;
                }
            }
        }

        bool is_accessible(size_t i, size_t j) const{
            if (!m_grid[idx(i,j)]) return false;
            int adjacent = m_grid[idx(i-1, j-1)] + m_grid[idx(i-1,j)] + m_grid[idx(i-1, j+1)] + 
            m_grid[idx(i, j-1)] + m_grid[idx(i,j+1)] + 
            m_grid[idx(i+1, j-1)] + m_grid[idx(i+1,j)] + m_grid[idx(i+1, j+1)];
            return adjacent < 4;
        }

        void display() const{
            for (size_t row = 0; row < m_nb_rows; row++){
                for(size_t col = 0; col < m_nb_cols; col++){
                    if (m_grid[idx(row, col)]) {
                        std::cout << (is_accessible(row, col) ? "A" : "X") ;
                    } else {
                        std::cout << ".";
                    }
                }
                std::cout << '\n';
            }
        }

        size_t accessible_sum() const{
            return m_accessible_sum;
        }

        size_t removable_sum() const{
            return m_removable_sum;
        }

        void remove_accessible_rolls(){
            for (size_t i = 1; i < m_nb_rows-1; i++){
                for (size_t j = 1; j < m_nb_cols-1; j++){
                    if (is_accessible(i,j)) 
                    {
                        m_grid[idx(i,j)] = false; 
                        m_removable_sum++;
                    }
                }
            }
        }
};


void Day4::solve(){
    std::vector<std::string> raw_positions = utils::read_input("inputs/4.txt");
    if (raw_positions.size() < 1)
    {
        std::cerr << "input is empty" << '\n';
        std::exit(1);
    }

    Positions positions = Positions(raw_positions);
    positions.display();
    std::cout << "initially accessible rolls = " << positions.accessible_sum() << '\n';

    size_t previous_nb_removable = 0;
    positions.remove_accessible_rolls();
    while (positions.removable_sum() != previous_nb_removable){
        std::cout << "=================================" << '\n';
        positions.display();
        previous_nb_removable = positions.removable_sum();
        positions.remove_accessible_rolls();
    }

    std::cout << "number of removable rolls = " << positions.removable_sum() << '\n';
}