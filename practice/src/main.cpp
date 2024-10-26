// ************************************************************************************************************************************************************
// preprocessor
// ************************************************************************************************************************************************************
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <list>
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

template <typename T>
void print(const T &input);

template <typename T>
void print(T start, T end);

void quickSort(std::vector<uint32_t> &input, size_t start, size_t end);
bool binarySearch(const std::vector<uint32_t> &input, uint32_t key, size_t start, size_t end);

// ************************************************************************************************************************************************************
// definitions
// ************************************************************************************************************************************************************
int main()
{
#if 1
    std::unordered_set<T> ust;  // std::unordered_set<int> ust{"red", "green", "blue"};

    float lf   = ust.loadfactor();    // num_elements / num_buckets
    size_t bc  = ust.bucket_count();  // num num_buckets
    size_t bct = ust.bucket(val);     // bucket of value
#else
    std::vector<uint32_t> input(10);
    fillVector(input, 100);

    printVector(input);
    quickSort(input, 0, input.size());

    printVector(input);
    binarySearch(input, input.at(2), 0, input.size());
#endif
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

template <typename T>
void print(const T &input)
{
    for (const auto &element : input)
    {
        cout << element << " ";
    }
    cout << endl;
}

template <typename T>
void print(T start, T end)
{
    for (; start != end; ++start)
    {
        cout << *start << " ";
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

void mergeSort(std::vector<uint32_t> &input, size_t start, size_t end)
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