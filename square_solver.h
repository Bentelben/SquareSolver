#ifndef SQUARE_SOLVER_H
#define SQUARE_SOLVER_H

#include "utils/ccomplex.h"

enum RootCount {
    RC_INF  = -1,
    RC_ZERO =  0,
    RC_ONE  =  1,
    RC_TWO  =  2
};

//! Solve square equation a*x^2 + b*x + c = 0
//!
//! @param[in]  a         a-coefficient
//! @param[in]  b         b-coefficient
//! @param[in]  c         c-coefficient
//! @param[out] x1        First root
//! @param[out] x2        Second root
//! @param[in]  isComplex Should solve equation in complex values
//!
//! @return Number of roots 
RootCount SolveSquareEquation(double a, double b, double c, ccomplex *x1, ccomplex *x2, bool isComplex);

#endif
