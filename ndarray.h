#ifndef NDARRAY
#define NDARRAY

#include "vectorutils.h"
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

  T &operator[](const std::vector<int> &location);

  Ndarray<T> operator+(const Ndarray<T> &other) const;
  Ndarray<T> operator-(const Ndarray<T> &other) const;
  Ndarray<T> operator*(const Ndarray<T> &other) const;
  Ndarray<T> operator/(const Ndarray<T> &other) const;

  void reshape();
  const std::vector<int> get_shape() const { return shape; };

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

#endif