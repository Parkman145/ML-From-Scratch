#include "vectorutils.h"

bool vector_utils::compatible_shape(std::vector<int> a, std::vector<int> b){
    if (a.size() != b.size()){
        return false;
    }

    for (int i = 0; i < a .size(); i++){
        if (a[i] == -1 || b[i] == -1) continue;

        if (a[i] != b[i]) return false;
    }

    return true;
}