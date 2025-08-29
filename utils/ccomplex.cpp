#include "ccomplex.h"

#include <math.h>
#include <stdio.h>
#include <ctype.h>

#include "myassert.h"
#include "double_comparator.h"
#include "../io/buffer_cleaner.h"

void FPrintComplex(FILE *const stream, ccomplex value) {
    myassert(stream, "Ptr to stream is NULL");

    const bool hasReal = !IsZero(value.real);
    const bool hasImag = !IsZero(value.imag);

    if (!hasReal && !hasImag) {
        fprintf(stream, "0");
        return;
    }

    if (hasReal && hasImag)
        fprintf(stream, "(");

    if (hasReal)
        fprintf(stream, "%lg", value.real);

    if (hasReal && hasImag) fprintf(stream, " ");

    if (hasImag) {
        fprintf(stream, (value.imag) < 0 ? "-" : "+");
        
        if (hasReal && hasImag) fprintf(stream, " ");
        
        if (!IsEqual(fabs(value.imag), 1))
            fprintf(stream, "%lg", fabs(value.imag));
        fprintf(stream, "i");
    }
    
    if (hasReal && hasImag)
        fprintf(stream, ")");
}

void PrintComplex(const ccomplex value) {
    FPrintComplex(stdout, value);
}

int FScanComplex(FILE *const stream , ccomplex *resultValue) {
    myassert(stream, "Ptr to stream is NULL");
    myassert(resultValue, "Ptr for out value is NULL");
    
    int scanfCode = 0;
    double value = 0;
    
    const int firstChar = getc(stream);
    ungetc(firstChar, stream);
    if (firstChar == 'i')
        value = 1;    
    else if ((scanfCode = fscanf(stream, "%lg", &value)) != 1)
        return scanfCode;

    const int sign = getc(stream);
    switch (sign) {
        case 'i':
            resultValue->real = 0;
            resultValue->imag = value;
            break;
        case '+':
        case '-':
        {
            const int nextChar = getc(stream);
            ungetc(nextChar, stream);
            if (!isdigit(nextChar) && nextChar != 'i' && nextChar != '.')
                return 0;

            resultValue->real = value;

            if (nextChar == 'i')
                resultValue->imag = 1;
            else
                if ((scanfCode = fscanf(stream, "%lg", &resultValue->imag)) != 1)
                    return scanfCode;

            if (sign == '-') resultValue->imag *= -1;
            
            const int lastChar = getc(stream);
            if (lastChar == EOF)
                return EOF;
            if (lastChar != 'i') {
                ungetc(lastChar, stream);
                return 0;
            }
            break;
        }
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

ccomplex ComplexSqrt(const ccomplex value) {
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

ccomplex ComplexDivide(const ccomplex divident, const ccomplex divider) {
    double dividerNorm = divider.real*divider.real + divider.imag*divider.imag;
    ccomplex result = {
        .real = (divident.real*divider.real + divident.imag*divider.imag)/dividerNorm,
        .imag = (-divident.real*divider.imag + divident.imag*divider.real)/dividerNorm
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
