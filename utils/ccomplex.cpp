#include "ccomplex.h"

#include <stdio.h>
#include <math.h>
#include "../myassert.h"
#include <ctype.h>

#include "double_comparator.h"
#include "buffer_cleaner.h"

void FPrintComplex(FILE *stream, ccomplex value) {
    myassert(stream, "");

    if (IsZero(value.real)) value.real = 0;

    if (IsZero(value.imag)) {
        fprintf(stream, "%lg", value.real);
    } else if (IsZero(value.real)) {
        fprintf(stream, "i%lg", value.imag);
    } else {
        fprintf(stream,
            "(%lg %c i%lg)",
            value.real, (value.imag < 0) ? '-' : '+', fabs(value.imag)
        );
    }
}

void PrintComplex(ccomplex value) {
    FPrintComplex(stdout, value);
}

// TODO implement
//int FScanComplex(FILE *stream , ccomplex *resultValue) {
//}

//int ScanComplex(ccomplex *resultValue) {
//    return FScanComplex(stdin, resultValue);
//}

bool IsComplexEqual(ccomplex value1, ccomplex value2) {
    return IsEqual(value1.real, value2.real) && IsEqual(value1.imag, value2.imag);
}

bool IsComplexZero(ccomplex value) {
    return IsZero(value.real) && IsZero(value.imag);
}

bool IsComplexNan(ccomplex value) {
    return isnan(value.real) || isnan(value.imag);
}

void ZeroizeComplex(ccomplex *value) {
    if (IsComplexZero(*value)) {
        value->real = 0;
        value->imag = 0;
    }
}
