// ************************************************************************************************************************************************************
// preprocessor
// ************************************************************************************************************************************************************
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>

#include "dsa.h"
#include "utils.h"

using std::cout;
using std::endl;

// ************************************************************************************************************************************************************
// definitions
// ************************************************************************************************************************************************************
int main()
{
    // init
    std::vector<uint16_t> input(10);
    std::srand(unsigned(std::time(nullptr)));

    std::generate(input.begin(), input.end(), std::rand);

    // quick_sort(input, input.begin(), input.end());
    merge_sort(input, input.begin(), input.end());
    binary_search(input, input.at(std::rand() % input.size()), input.begin(), input.end());

    return 0;
}