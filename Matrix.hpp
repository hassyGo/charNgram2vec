#pragma once

#include <Eigen/Core>

#ifdef USE_FLOAT
typedef float Real;
typedef Eigen::MatrixXf MatD;
typedef Eigen::VectorXf VecD;
#else
typedef double Real;
typedef Eigen::MatrixXd MatD;
typedef Eigen::VectorXd VecD;
#endif

typedef Eigen::Ref<MatD> RefMatD;
typedef Eigen::Ref<VecD> RefVecD;
typedef const Eigen::Ref<const MatD>& ConstRefMatD;
typedef const Eigen::Ref<const VecD>& ConstRefVecD;

typedef Eigen::MatrixXi MatI;
typedef Eigen::VectorXi VecI;
#define REAL_MAX std::numeric_limits<Real>::max()
