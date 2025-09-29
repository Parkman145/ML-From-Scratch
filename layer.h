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

template<typename T>
class Flatten : public Layer<T> {

    public:
    Ndarray<T> operator()(const Ndarray<T> &arr) const {
        if (arr.get_shape().size() < 2) {
            throw typename Ndarray<T>::IncompatibleDimensions();
        }
        
        auto result = arr;

        auto new_shape = std::vector<int>(2);

        new_shape[0] = result.get_shape()[0];

        int prod = 1;

        new_shape[1] = vector_utils::product(result.get_shape())/result.get_shape()[0];

        result.reshape(new_shape);
        
        return result;

    }
};


#endif