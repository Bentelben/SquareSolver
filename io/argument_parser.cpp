#include "argument_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/myassert.h"

static void GetFieldWidth(const Flag flags[], const size_t nFlags, size_t *const fullNameFieldWidth, size_t *const aliasFieldWidth);

static bool IsEqualFlag(const char *arg, const Flag *const flag) {
    myassert(arg, "Argument is NULL");
    myassert(flag, "Ptr to flag is NULL");

    size_t minusCount = 0;
    while (arg[0] == '-' && minusCount <= 2) {
        minusCount++;
        arg++;
    }

    if (minusCount == 1)
        return strcmp(arg, flag->alias) == 0;
    else if (minusCount == 2)
        return strcmp(arg, flag->fullName) == 0;

    return false;
}

static const Flag *GetFlag(const char *arg, const Flag flags[], const size_t nFlags) {
    myassert(arg, "Ptr to argument is NULL");
    myassert(flags, "Ptr to flag name is NULL");

    for (size_t i = 1; i < nFlags; i++)
        if (IsEqualFlag(arg, flags + i))
            return flags+i;

    return NULL;
}

static int CountNextWords(char *argv[], const int argc) {
    myassert(argv, "Argv is NULL");
    myassert(argc >= 0, "Argument count is negative");

    int nWords = 0;
    for (;nWords + 1 < argc && argv[nWords + 1][0] != '-' ; nWords++);
    return nWords;
}

ParseCode ParseFlags(char *argv[], const int argc, const Flag flags[], const size_t nFlags, void *context) {
    myassert(argv, "Argv is NULL");
    myassert(argc > 0, "Wrong argument count");
    myassert(flags, "Ptr to flags array is NULL");
    myassert(nFlags > 0, "Flag count must be bigger than zero");

    myassert(flags[0].fullName == NULL && flags[0].alias == NULL, "Default flag function must not have name");
    FlagFunction_t modeFunction = flags[0].func;

    for (int argumentIndex = 1; argumentIndex < argc; argumentIndex++) {
        const Flag *const flag = GetFlag(argv[argumentIndex], flags, nFlags);
        if (flag == NULL)
            return PC_ERROR_UNKNOWN_FLAG;

        myassert(!(flag->isModeFlag && flag->nNextWords != 0), "Mode flag has arguments");

        const int nWords = CountNextWords(argv + argumentIndex, argc - argumentIndex);

        if (flag->nNextWords != -1 && nWords != flag->nNextWords)
            return PC_ERROR_WRONG_WORD_COUNT;

        if (flag->isModeFlag) {
            modeFunction = flag->func;
            continue;
        }

        if (!flag->func(argv + argumentIndex + 1, nWords, context))
            return PC_ERROR_FLAG_FUNCTION_FAILURE;

        argumentIndex += nWords;
    }

    if (!modeFunction(NULL, 0, context))
        return PC_ERROR_FLAG_FUNCTION_FAILURE;

    return PC_NO_ERROR;
}

void PrintArgumentInfo(const Flag flags[], const size_t nFlags) {
    myassert(flags, "Ptr to flags array in NULL");

    printf("\n%s\n\n", flags[0].description);

    size_t fullNameFieldWidth = 0;
    size_t aliasFieldWidth = 0;
    GetFieldWidth(flags+1, nFlags-1, &fullNameFieldWidth, &aliasFieldWidth);

    for (size_t i = 1; i < nFlags; i++)
        printf(" --%-*s -%-*s %s\n", (int)fullNameFieldWidth, flags[i].fullName, (int)aliasFieldWidth, flags[i].alias, flags[i].description);
}

static void UpdateMaxFieldWidth(size_t *const size, const char *const name) {
    myassert(size, "Ptr for out value is NULL");
    myassert(name, "name is NULL");
    size_t len = strlen(name);
    if (*size < len) *size = len;
}

static void GetFieldWidth(const Flag flags[], const size_t nFlags, size_t *const fullNameFieldWidth, size_t *const aliasFieldWidth) {
    myassert(flags, "Ptr to flags array is NULL");
    myassert(fullNameFieldWidth, "Ptr for out value is NULL");
    myassert(aliasFieldWidth, "Ptr for out value is NULL");

    for (size_t i = 0; i < nFlags; i++) {
        UpdateMaxFieldWidth(fullNameFieldWidth, flags[i].fullName);
        UpdateMaxFieldWidth(aliasFieldWidth, flags[i].alias);
    }
}
