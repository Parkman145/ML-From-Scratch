#ifndef ARRAY_UTILITIES_H
#define ARRAY_UTILITIES_H

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ios>
#include <regex>
#include <string>

#include "ndarray.h"

template <typename T>
Ndarray<T> read_np(const std::string& path) {
    std::ifstream file(path);

    bool found = false;
    while (!found){
        if (file.peek() == '(') found = true;
        file.seekg(1, std::ios_base::cur);
    }
    
    std::vector<int> shape;
    int curr = 0;
    int mult = 1;
    bool done = false;

    while (!done){
        if (file.peek() == ')') {
            break;
        }
        
        std::string field;
        std::getline(file, field, ',');

        if (field.back() == ')') {
            done = true;
            field.pop_back();
        }

        shape.push_back(std::stoi(field));
        file.seekg(1, std::ios_base::cur);
    }

    return Ndarray<T>{{1}, {1.0}};
}



#endif