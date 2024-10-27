#pragma once

// ************************************************************************************************************************************************************
// preprocessor
// ************************************************************************************************************************************************************
#include "utils.h"
#include <iostream>
#include <iterator>
#include <vector>

using std::cout;
using std::endl;

// ************************************************************************************************************************************************************
// definitions
// ************************************************************************************************************************************************************
template <typename T>
void quick_sort(std::vector<T> &input, typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
{
    if (start < end)
    {
        T pivot = *start;
        cout << "pivot:" << pivot << "  start:" << *start << "  end:" << *(end - 1) << endl;
        cout << std::vector<T>(start, end) << endl;
        auto low = start, high = end;

        while (low < high)
        {
            do
            {
                low++;
            } while ((low < end) && (*low <= pivot));

            do
            {
                high--;
            } while ((high > start) && (*high >= pivot));

            if (low < high)
            {
                std::swap(*low, *high);
            }
        }

        std::swap(*start, *high);
        cout << input << endl
             << endl;

        quick_sort(input, start, high);
        quick_sort(input, high + 1, end);
    }
}

template <typename T>
bool binary_search(const std::vector<T> &input, T key, typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
{
    cout << std::vector<T>(start, end) << endl;

    if (end >= start)
    {
        typename std::vector<T>::iterator mid = start + (end - start) / 2;
        T mid_value                           = *mid;

        if (key > mid_value)
        {
            return binary_search(input, key, mid + 1, end);
        }
        else if (key < mid_value)
        {
            return binary_search(input, key, start, mid - 1);
        }
        else
        {
            cout << "found key " << key << " at " << mid - input.begin() << endl;
            return true;
        }
    }

    cout << key << " not found" << endl;
    return false;
}

template <typename T>
std::vector<T> operator+(std::vector<T> &left, std::vector<T> &right)
{
    std::vector<T> result;
    result.reserve(left.size() + right.size());

    while (left.size() || right.size())
    {
        if (left.size() == 0)
        {
            result.push_back(right.at(0));
            right.erase(right.begin());
            continue;
        }

        if (right.size() == 0)
        {
            result.push_back(left.at(0));
            left.erase(left.begin());
            continue;
        }

        if (left.at(0) < right.at(0))
        {
            result.push_back(left.at(0));
            left.erase(left.begin());
        }
        else
        {
            result.push_back(right.at(0));
            right.erase(right.begin());
        }
    }

    return result;
}

template <typename T>
void merge_sort(std::vector<T> &input, typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
{
    cout << std::vector<T>(start, end) << endl;

    size_t size = end - start;
    if (size == 2)
    {
        if (*start > *(end - 1))
        {
            uint32_t temp = *start;
            *start        = *(end - 1);
            *(end - 1)    = temp;
        }
    }
    else if (size == 1)
    {
    }
    else
    {
        size_t half_size = size / 2;
        std::vector<T> left(start, start + half_size);
        std::vector<T> right(start + half_size, end);

        merge_sort(left, left.begin(), left.end());
        merge_sort(right, right.begin(), right.end());

        input.clear();
        input = left + right;
        cout << input << endl;
    }
}