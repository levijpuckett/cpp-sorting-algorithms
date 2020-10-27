#ifndef BUBBLE_SORT_HPP_
#define BUBBLE_SORT_HPP_
#include <vector>
#include <iostream>

// bubble_sort sorts vector v using the bubble sort alorithm, and saves a 'snapshot' at each iteration
template <typename T>
auto bubble_sort(std::vector<T> v)
{
    std::vector<std::vector<T>> snapshots;
    snapshots.push_back(v); // save the unsorted array

    int n = 0;
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (auto it = v.begin() + 1; it != v.end() - n; ++it)
        {
            if (*(it-1) > *it)
            {
                std::iter_swap(it-1, it);
                swapped = true;;
            }
            snapshots.push_back(v); // save v every time it is accessed
        }
        ++n;
    }
    return snapshots;
}
#endif /* BUBBLE_SORT_HPP_ */
