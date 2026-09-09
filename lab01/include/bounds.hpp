#pragma once

#include <cstddef>
#include <vector>

template<typename T>
std::size_t my_lower_bound(const std::vector<T> &a, const T &x) {
  //(void)x;
    std::size_t low = 0;
    std::size_t high = a.size();

    while (low < high){
        std::size_t min = low + (high - low ) / 2;
        if (a[mid] >= x) 
            high = mid;
        else
            low = mid + 1;
    }
  // TODO: primera posición i tal que a[i] >= x.
  // Debe usar O(log n) comparaciones y puede asumir que a está ordenado.
  return low;
}

template<typename T>
std::size_t my_upper_bound(const std::vector<T> &a, const T &x) {
  //(void)x;
  
    std::size_t low = 0;
    std::size_t = a.size();
    while (low < high){
        std::size_t mid = low + (high - low) / 2;
        if (a[mid] > x)
            high = mid;
        else
            low = mid + 1;
    }

  // TODO: primera posición i tal que a[i] > x.
  // Debe usar O(log n) comparaciones y puede asumir que a está ordenado.
  return low;
}
