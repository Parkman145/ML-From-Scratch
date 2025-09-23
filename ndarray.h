#ifndef NDARRAY
#define NDARRAY

#include "vectorutils.h"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class Ndarray
{
private: // Private
  std::vector<T> data;
  std::vector<int> shape;

  int compute_index(const std::vector<int> &location) const;

public:
  Ndarray(const std::vector<int> &shape);
  Ndarray(const std::vector<int> &shape, const std::vector<T> &data);

  void write_data(const std::vector<T>& new_data);

  T &operator[](const std::vector<int> &location);

  Ndarray<T> operator+(const Ndarray<T> &other) const;
  Ndarray<T> operator-(const Ndarray<T> &other) const;
  Ndarray<T> operator*(const Ndarray<T> &other) const;
  Ndarray<T> operator/(const Ndarray<T> &other) const;

  template <typename T2>
  Ndarray<T> operator+(const T2 &other) const;
  template <typename T2>
  Ndarray<T> operator-(const T2 &other) const;
  template <typename T2>
  Ndarray<T> operator*(const T2 &other) const;
  template <typename T2>
  Ndarray<T> operator/(const T2 &other) const;

  friend std::ostream& operator<<(std::ostream& os, const Ndarray<T>& array) {

    std::vector<int> checkpoints(array.shape.size());

    int mult = 1;
    
    for (int i = checkpoints.size()-1; i >= 0; i--) {
      mult *= array.shape[i];
      checkpoints[i] = mult;
    }

    for (int i = 0; i < array.data.size(); i++) {
      for (auto checkpoint : checkpoints) {
        if (i % checkpoint == 0) {
          os << "[";
        }  
        
      }
      os << " " << array.data[i] << ", ";
      
      int newlines = 0;
      for (auto checkpoint : checkpoints) {
        if (i % checkpoint == checkpoint-1) {
          os << "]";
          newlines++;
        }
      }
      os << std::string(newlines, '\n');
    }
    return os;
  }

  void reshape();
  const std::vector<int> get_shape() const { return shape; };
  const std::vector<T>& get_data() const { return data; };
  class InvalidShapeException : public std::exception
  {
    virtual const char *what() const throw() { return "Invalid Shape"; }
  };

  class IncompatibleShape : public std::exception
  {
    virtual const char *what() const throw() { return "Incompatible Shape"; }
  };
  class IncompatibleDimensions : public std::exception
  {
    virtual const char *what() const throw()
    {
      return "Incompatible Dimensions";
    }
  };
};

template <typename T>
Ndarray<T>::Ndarray(const std::vector<int> &shape)
{
  int size = vector_utils::product(shape);

  data.resize(size);
  this->shape = shape;
}

template <typename T>
Ndarray<T>::Ndarray(const std::vector<int> &shape, const std::vector<T> &data)
{
  int size = vector_utils::product(shape);

  if (data.size() != vector_utils::product(shape))
  {
    throw InvalidShapeException();
  }

  this->data = data;
  this->shape = shape;
}

// No bounds checking. Use with caution.
template <typename T>
int Ndarray<T>::compute_index(const std::vector<int> &location) const
{
  int mult = 1;
  int pos = 0;

  for (int i = shape.size() - 1; i >= 0; i--)
  {
    pos += location[i] * mult;
    mult *= shape[i];
  }

  return pos;
}

template <typename T>
void Ndarray<T>::write_data(const std::vector<T> &new_data){
  if (data.size() != new_data.size()) {
    throw std::invalid_argument("Vectors size must match");
  }

  data = new_data;
}

template <typename T>
T &Ndarray<T>::operator[](const std::vector<int> &location)
{
  if (location.size() != shape.size())
  {
    throw IncompatibleDimensions();
  }

  for (int i = 0; i < shape.size(); i++)
  {
    if (location[i] > shape[i])
    {
      throw std::out_of_range("Location out of bounds");
    }
  }

  return data[compute_index(location)];
}

template <typename T>
Ndarray<T> Ndarray<T>::operator+(const Ndarray<T> &other) const
{
  if (shape != other.shape)
  {
    throw IncompatibleShape();
  }

  Ndarray<T> result(shape);

  for (int i = 0; i < data.size(); i++)
  {
    result.data[i] = data[i] + other.data[i];
  }

  return result;
}

template <typename T>
Ndarray<T> Ndarray<T>::operator-(const Ndarray<T> &other) const
{
  if (shape != other.shape)
  {
    throw IncompatibleShape();
  }

  Ndarray<T> result(shape);

  for (int i = 0; i < data.size(); i++)
  {
    result.data[i] = data[i] - other.data[i];
  }

  return result;
}

template <typename T>
Ndarray<T> Ndarray<T>::operator*(const Ndarray<T> &other) const
{
  if (shape != other.shape)
  {
    throw IncompatibleShape();
  }

  Ndarray<T> result(shape);

  for (int i = 0; i < data.size(); i++)
  {
    result.data[i] = data[i] * other.data[i];
  }

  return result;
}

template <typename T>
Ndarray<T> Ndarray<T>::operator/(const Ndarray<T> &other) const
{
  if (shape != other.shape)
  {
    throw IncompatibleShape();
  }

  Ndarray<T> result(shape);

  for (int i = 0; i < data.size(); i++)
  {
    result.data[i] = data[i] / other.data[i];
  }

  return result;
}


template <typename T>
template <typename T2>
Ndarray<T> Ndarray<T>::operator+(const T2 &other) const
{
  Ndarray<T> result(shape);

  for (int i = 0; i < data.size(); i++)
  {
    result.data[i] = data[i] + other;
  }

  return result;
}

template <typename T>
template <typename T2>
Ndarray<T> Ndarray<T>::operator-(const T2 &other) const
{
  Ndarray<T> result(shape);

  for (int i = 0; i < data.size(); i++)
  {
    result.data[i] = data[i] - other;
  }

  return result;
}

template <typename T>
template <typename T2>
Ndarray<T> Ndarray<T>::operator*(const T2 &other) const
{
  Ndarray<T> result(shape);

  for (int i = 0; i < data.size(); i++)
  {
    result.data[i] = data[i] * other;
  }

  return result;
}

template <typename T>
template <typename T2>
Ndarray<T> Ndarray<T>::operator/(const T2 &other) const
{
  Ndarray<T> result(shape);

  for (int i = 0; i < data.size(); i++)
  {
    result.data[i] = data[i] / other;
  }

  return result;
}

#endif