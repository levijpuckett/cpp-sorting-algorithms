#ifndef QUICK_SORT_HPP_
#define QUICK_SORT_HPP_
#include <vector>
#include <iostream>

// quick_sort sorts vector v using a modified quick sort algorithm, and returns when any change has been made to it.
// this implementation is an iterative (as opposed to recursive) quick sort. As each step in the sorting proccess
// is saved for display later, an iterative version makes recovery of each state easier.
// recursion is simulated using an array as a stack, looping until the stack is completely empty (and the 'recursion'
// is complete).
template <typename T>
auto quick_sort(std::vector<T> v)
{
    std::vector<std::vector<T>> snapshots;
    snapshots.push_back(v); // save the unsorted array

    int hi = v.size();
    int lo = 0;

    // Stack to simulate recursion
    int stack[v.size()];
    int index = -1;

    // Push the first range onto the stack
    stack[++index] = lo;
    stack[++index] = hi;
    while (index >= 0)
    {
        // Pop the next range off of the stack
        hi = stack[index--];
        lo = stack[index--];

        // Use a centered pivot
        T pivot = v[(hi+lo)/ 2];

        // Two indices (Hoare partition scheme)
        int i = lo;
        int j = hi - 1;

        // Position the pivot to the correct spot in the array, and ensure that all
        // lower entries are less than, and all higher entries are greater than the
        // value of the pivot.
        // Also, save a snapshot every time the array is accessed
        while (true)
        {
            while (v[i] < pivot) { ++i; snapshots.push_back(v); }
            while (v[j] > pivot) { --j; snapshots.push_back(v); }
            if (i >= j) { break; }
            std::iter_swap(v.begin() + i, v.begin() + j);
        }

        // If there is anything to the left of the pivot, push a new 'recursion' onto the stack
        if (j-1 > lo)
        {
            stack[++index] = lo;
            stack[++index] = j;
        }

        // If there is anything to the right of the pivot, push a new 'recursion' onto the stack
        if (j+1 < hi)
        {
            stack[++index] = j;
            stack[++index] = hi;
        }
    }

    return snapshots;
}
#endif /* QUICK_SORT_HPP_ */
