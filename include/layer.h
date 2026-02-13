#ifndef LAYER
#define LAYER

#include "CNDA/ndarray.h"
#include "CNDA/vectorutils.h"
#include <algorithm>
#include <iterator>
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

template<typename T>
class Dense : public Layer<T> {
    private: 
    int input_features;
    int output_features;
    Ndarray<T> weights; 
    public:

    
    Dense(int inp_features, int out_features) : input_features{inp_features}, output_features{out_features}, weights{{input_features, output_features}}{
        
    }

    // TODO
    Ndarray<T> operator()(const Ndarray<T> &arr) const {
        // Size of each sample
        int batch_step_size = arr.get_data().size()/arr.get_shape()[0];
        int n = arr.get_shape()[0];

        auto output = Ndarray<T>::matmul(arr, weights);

        return output;
    }
};


#endif