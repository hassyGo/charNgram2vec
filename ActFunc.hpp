#pragma once

#include "Matrix.hpp"

class ActFunc{
public:
  static Real logistic(const Real x);
};

//f(x) = sigm(x)
inline Real ActFunc::logistic(const Real x){
  return 1.0/(1.0+::exp(-x));
}
