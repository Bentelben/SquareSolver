#ifndef MYASSERT_H
#define MYASSERT_H


#ifndef NDEBUG
    #define myassert(statement, format, ...) _myassert((__FILE__), (__LINE__), (__func__), (#statement), (statement), (format), ##__VA_ARGS__)
#else
    #define myassert(...)
#endif

void _myassert(const char *filename, const int line, const char *func, const char *stringStatement, const bool statement, const char *format, ...);

#endif
