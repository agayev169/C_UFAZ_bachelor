#include "printer.hpp"

void printPhase(unsigned int step, unsigned int steps, time_t time) {
    unsigned int loadNum = 40;
    std::cout << step << "/" << steps << "|";
    unsigned int complete = step * loadNum / steps;
    for (auto i = 0u; i < complete; ++i) {
        std::cout << ">";
    }
    for (auto i = complete; i < loadNum; ++i) {
        std::cout << "=";
    }
    std::cout << "|";
    std::cout << std::to_string(time);
    std::cout << std::endl;
}