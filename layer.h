#ifndef LAYER
#define LAYER

#include "ndarray.h"
#include <algorithm>
#include <vector>
template<typename T>
class Layer {
    public:
    virtual Ndarray<T> operator()(const Ndarray<T> &arr) const = 0;
};

template <typename T> 
class Passthrough : public Layer<T> {
    public:
    Ndarray<T> operator()( const Ndarray<T> &arr) const {
        return arr;
    }
};

template <typename T> 
class ReLU : public Layer<T> {
    public:
    Ndarray<T> operator()(const Ndarray<T> &arr) const {
        
        auto data = arr.get_data();
        std::vector<T> result(data.size());
        std::transform(data.begin(), data.end(), result.begin(), [](T& val) { return val < 0 ? 0 : val;});
        return result;
    }

};


#endif