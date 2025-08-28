#include "ccomplex.h"

#include <math.h>
#include <stdio.h>

#include "myassert.h"
#include "double_comparator.h"
#include "../io/buffer_cleaner.h"

void FPrintComplex(FILE *const stream, ccomplex value) {
    myassert(stream, "Ptr to stream is NULL");

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

void PrintComplex(const ccomplex value) {
    FPrintComplex(stdout, value);
}

int FScanComplex(FILE *const stream , ccomplex *resultValue) {
    myassert(stream, "Ptr to stream is NULL");
    myassert(resultValue, "Ptr for out value is NULL");
    
    int scanfCode = 0;
    double value = 0;
    
    if ((scanfCode = fscanf(stream, "%lg", &value)) != 1)
        return scanfCode;

    CleanBufferSpaces(stream);

    int sign = getc(stream);
    switch (sign) {
        case 'i':
            resultValue->real = 0;
            resultValue->imag = value;
            break;
        case '+':
        case '-':
            resultValue->real = value;
            CleanBufferSpaces(stream);

            if ((scanfCode = fscanf(stream, "%lg", &resultValue->imag)) != 1)
                return scanfCode;

            if (sign == '-') resultValue->imag *= -1;

            sign = getc(stream);
            if (sign == EOF)
                return EOF;
            if (sign != 'i') {
                ungetc(sign, stream);
                return 0;
            }
            break;
        case EOF:
            return EOF;
        default:
            ungetc(sign, stream);
            resultValue->real = value;
            resultValue->imag = 0;
            break;
    }
    return 1;
}

int ScanComplex(ccomplex *resultValue) {
    return FScanComplex(stdin, resultValue);
}

bool IsComplexEqual(const ccomplex value1, const ccomplex value2) {
    return IsEqual(value1.real, value2.real) && IsEqual(value1.imag, value2.imag);
}

bool IsComplexZero(const ccomplex value) {
    return IsZero(value.real) && IsZero(value.imag);
}

bool IsComplexNan(const ccomplex value) {
    return isnan(value.real) || isnan(value.imag);
}

void ZeroizeComplex(ccomplex *value) {
    if (IsComplexZero(*value)) {
        value->real = 0;
        value->imag = 0;
    }
}

double getComplexNorm(const ccomplex value) {
    return sqrt(value.real*value.real + value.imag*value.imag);
}

double getComplexAngle(const ccomplex value) {
    if (IsZero(value.real)) {
        if (value.imag < 0) return -M_PI/2;
        else return M_PI/2;
    }

    return atan(value.imag/value.real) + ((value.real < 0) ? M_PI : 0);
}

ccomplex ComplexRoot(const ccomplex value) {
    double norm = sqrt(getComplexNorm(value));
    double angle = getComplexAngle(value)*0.5;
    ccomplex result = {
        .real = norm*cos(angle),
        .imag = norm*sin(angle)
    };
    return result;
}

ccomplex ComplexMultiply(const ccomplex value1, const ccomplex value2) {
    ccomplex result = {
        .real = value1.real*value2.real - value1.imag*value2.imag,
        .imag = value1.real*value2.imag + value1.imag*value2.real
    };
    return result;
}

ccomplex ComplexDivide(const ccomplex value1, const ccomplex value2) {
    double squareNorm2 = value2.real*value2.real + value2.imag*value2.imag;
    ccomplex result = {
        .real = (value1.real*value2.real + value1.imag*value2.imag)/squareNorm2,
        .imag = (-value1.real*value2.imag + value1.imag*value2.real)/squareNorm2
    };
    return result;
}

ccomplex ComplexAdd(const ccomplex value1, const ccomplex value2) {
    ccomplex result = {
        .real = value1.real + value2.real,
        .imag = value1.imag + value2.imag
    };
    return result;
}

ccomplex ComplexSubtract(const ccomplex value1, const ccomplex value2) {
    ccomplex result = {
        .real = value1.real - value2.real,
        .imag = value1.imag - value2.imag
    };
    return result;
}
