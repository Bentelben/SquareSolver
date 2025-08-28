#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <stdlib.h>

enum ParseCode {
    PC_NO_ERROR                    = 0,
    PC_ERROR_UNKNOWN_FLAG          = 1,
    PC_ERROR_WRONG_WORD_COUNT      = 2,
    PC_ERROR_FLAG_FUNCTION_FAILURE = 3
};

typedef bool (*FlagFunction_t)(char *[], int, void *);

struct Flag {
    const char *fullName;
    const char *alias;
    int nNextWords;
    bool isModeFlag;
    const char *description;
    FlagFunction_t func;
};

//! Parses flags for command line and executes functions corresponding to them
//!
//! @param[in] argv    Command line argv
//! @param[in] argc    Command line argc
//! @param[in] flags   Array of available flags
//! @param[in] nFlags  Length of flags array
//! @param[in] context Volatile context of program
//!
//! @return Result code
//!
//! @note Context can be changed and used by flag functions as settings
//! @note Each flag function must return true if parser should continue
//! @note parsing and false if this flag function should be executed
//! @note last
//! @note Default flag function must be first in flags array
ParseCode ParseFlags(char *argv[], int argc, const Flag flags[], size_t nFlags, void *context);

//! Prints in stdout info about flags
//!
//! @param[in] flags  Array of available flags
//! @param[in] nFlags Length of flags array
void PrintArgumentInfo(const Flag flags[], size_t nFlags);

#endif
