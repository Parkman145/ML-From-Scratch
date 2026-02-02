#ifndef ARRAY_UTILITIES_H
#define ARRAY_UTILITIES_H

#include <algorithm>
#include <cstring>
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

    found = false;
    while (!found){
        if (file.peek() == '\n') found = true;
        file.seekg(1, std::ios_base::cur);
    }

    auto begin = file.tellg();
    file.seekg(0, std::ios_base::end);
    auto end = file.tellg();
    int size = end - begin;
    file.seekg(begin);
    int count = size/sizeof(T);

    std::vector<T> data(count);

    file.read(reinterpret_cast<char*>(data.data()), size);
    
    Ndarray<T> result{shape, data};

    return result;
}



#endif