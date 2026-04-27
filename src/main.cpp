#include <iostream>
#include "../include/utils.hpp"
#include "../include/day2.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "usage is : ./aoc_exec <day_number>" << std::endl;
    }

    int day_number = std::stoi(argv[1]);

    switch (day_number)
    {
    case 2:
    {
        Day2 solver;
        solver.solve();
        break;
    }
    default:
        std::cout << "this day is not implemented yet :(" << std::endl;
    }
}
