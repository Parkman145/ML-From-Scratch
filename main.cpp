#include <iostream>
#include <vector>

#include "vectorutils.h"

int main() {

    std::vector<int> vec_int{1, 2, 3};
    std::vector<int> vec1{3};
    std::vector<int> vec_empty{};
    std::vector<float> vec_float{2.1, 3.9, 4.6, 6.1};
    std::cout << vector_utils::product(vec_int) << "\n";
    std::cout << vector_utils::product(vec1) << "\n";
    std::cout << vector_utils::product(vec_empty) << "\n";
    std::cout << vector_utils::product(vec_float) << "\n";

    return 0;
}