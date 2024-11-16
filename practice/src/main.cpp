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
#include "neon.h"
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

    int src1[10] = {1, 2, 3, 4, 5, 6, 7, 8};
    int src2[10] = {10, 20, 30, 40, 50, 60, 70, 80};
    int dst[10]  = {};
    array_sum(src1, src2, dst, 8);

    for (int i = 0; i < 8; i++)
    {
        cout << dst[i] << " ";
    }
    cout << endl;

    return 0;
}