#ifndef NDARRAY
#define NDARRAY

#include <vector>
#include "vectorutils.h"

template <typename T> class Ndarray {
private:
  std::vector<T> data;
  std::vector<int> shape;

  int compute_index(const std::vector<int> &location) const;

public:
  Ndarray(const std::vector<int>& shape);
  

  T &operator[](const std::vector<int> &location);
  
  void reshape();
  const std::vector<int> get_shape() const { return shape; };
};


template <typename T>
Ndarray<T>::Ndarray(const std::vector<int>& shape) {
    int size = vector_utils::product(shape);
    
    data.resize(size);
    this->shape = shape;
}





#endif