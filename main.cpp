#include <iostream>
#include <vector>

#include "vectorutils.h"
#include "ndarray.h"
#include "array_utilities.h"

int main() {
    // Ndarray<int> arr{std::vector<int>{2, 2}};

    Ndarray<double> arr = read_np<double>("array.npy");

    std::cout << arr;

    
    return 0;
}