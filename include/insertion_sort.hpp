#ifndef INSERTION_SORT_HPP_
#define INSERTION_SORT_HPP_
#include <vector>

// insertion_sort sorts vector v using the insertion sort algorithm, and saves a 'snapshot' at each iteration
template <typename T>
auto insertion_sort(std::vector<T> v)
{
    std::vector<std::vector<T>> snapshots;
    snapshots.push_back(v); // save the unsorted array

    std::size_t i = 1;
    while (i < v.size())
    {
        T x  = v[i];
        int j = i-1;
        while ((j >= 0) && (v[j] > x))
        {
            v[j+1] = v[j];
            snapshots.push_back(v); // save v every time it is accessed
            --j;
        }
        v[j+1] = x;
        snapshots.push_back(v); // save v every time it is accessed
        ++i;
    }
    return snapshots;
}
#endif /* INSERTION_SORT_HPP_ */
