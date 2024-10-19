// ************************************************************************************************************************************************************
// preprocessor
// ************************************************************************************************************************************************************
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

// ************************************************************************************************************************************************************
// types
// ************************************************************************************************************************************************************

// ************************************************************************************************************************************************************
// declarations
// ************************************************************************************************************************************************************
void fillVector(std::vector<uint32_t> &input, uint32_t max);
void printVector(const std::vector<uint32_t> &input);
void quickSort(std::vector<uint32_t> &input, size_t start, size_t end);
bool binarySearch(const std::vector<uint32_t> &input, uint32_t key, size_t start, size_t end);

// ************************************************************************************************************************************************************
// definitions
// ************************************************************************************************************************************************************
int main()
{
    std::vector<uint32_t> input(10);
    fillVector(input, 100);

    printVector(input);
    quickSort(input, 0, input.size());

    printVector(input);
    binarySearch(input, input.at(2), 0, input.size());

    return 0;
}

void fillVector(std::vector<uint32_t> &input, uint32_t max)
{
    std::srand(unsigned(std::time(nullptr)));
    std::generate(input.begin(), input.end(), std::rand);

    for (uint32_t &element : input)
    {
        element = element % max;
    }
}

void printVector(const std::vector<uint32_t> &input)
{
    for (const uint32_t &element : input)
    {
        cout << element << " ";
    }
    cout << endl;
}

void printVector(const std::vector<uint32_t> &input, size_t start_idx, size_t end_idx)
{
    assert(start_idx <= end_idx);

    for (size_t idx = start_idx; idx < end_idx; ++idx)
    {
        cout << input.at(idx) << " ";
    }
    cout << endl;
}

void quickSort(std::vector<uint32_t> &input, size_t start, size_t end)
{
    if (start < end)
    {
        uint32_t pivot = input.at(start);
        // cout << "pivot: " << pivot << " start: " << start << " end: " << end << endl;
        // printVector(input, start, end);
        size_t low = start, high = end;

        while (low < high)
        {
            do
            {
                low++;
            } while ((low < end) && (input.at(low) <= pivot));

            do
            {
                high--;
            } while ((high > start) && (input.at(high) >= pivot));

            if (low < high)
            {
                std::swap(input.at(low), input.at(high));
            }
        }

        std::swap(input.at(start), input.at(high));
        // printVector(input);

        quickSort(input, start, high);
        quickSort(input, high + 1, end);
    }
}

void mergeSort(std::vector<uint32_t>& input, size_t start, size_t end)
{

}

bool binarySearch(const std::vector<uint32_t> &input, uint32_t key, size_t start, size_t end)
{
    if (end >= start)
    {
        size_t mid         = start + (end - start) / 2;
        uint32_t mid_value = input.at(mid);

        if (key > mid_value)
        {
            return binarySearch(input, key, mid + 1, end);
        }
        else if (key < mid_value)
        {
            return binarySearch(input, key, start, mid - 1);
        }
        else
        {
            cout << "found key " << key << " at " << mid << endl;
            return true;
        }
    }

    cout << key << " not found" << endl;
    return false;
}