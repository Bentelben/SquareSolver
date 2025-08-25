#include "argument_parser.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void getFieldWidth(const Flag flags[], size_t nFlags, size_t *fullNameFieldWidth, size_t *aliasFieldWidth);

static bool IsEqualFlag(char *arg, const char *flagName) {
    assert(arg);
    assert(flagName);
    
    while (arg[0] == '-') arg++;
    return strcmp(arg, flagName) == 0;
}

static const Flag *GetFlag(char *arg, const Flag flags[], size_t nFlags) {
    assert(arg);
    assert(flags);
    
    for (size_t i = 0; i < nFlags; i++) {
        if (flags[i].fullName == NULL)
            continue;

        if (IsEqualFlag(arg, flags[i].fullName) || IsEqualFlag(arg, flags[i].alias))
            return flags+i;
    }
    return NULL;
}

ParseCode ParseFlags(char *argv[], int argc, const Flag flags[], size_t nFlags, void *context) {
    assert(argv != NULL);
    assert(argc > 0);
    assert(flags != NULL);

    for (int argumentIndex = 1; argumentIndex < argc; argumentIndex++) {
        const Flag *flag = GetFlag(argv[argumentIndex], flags, nFlags);
        if (flag == NULL)
            return PC_ERROR_UNKNOWN_FLAG;

        int nWords = 0;
        while (argumentIndex + nWords + 1 < argc) {
            if (argv[argumentIndex + nWords + 1][0] == '-')
                break;
            nWords++;
        }
        if (flag->nNextWords != -1 && nWords != flag->nNextWords)
            return PC_ERROR_WRONG_WORD_COUNT;

        if (!flag->func(argv + argumentIndex + 1, nWords, context))
            return PC_NO_ERROR;
        argumentIndex += nWords;
    }
    flags[0].func(NULL, 0, context); // Default command
    return PC_NO_ERROR;
}

void PrintArgumentInfo(const Flag flags[], size_t nFlags) {
    assert(flags != NULL);

    printf("\n%s\n\n", flags[0].description);

    size_t fullNameFieldWidth = 0;
    size_t aliasFieldWidth = 0;
    getFieldWidth(flags+1, nFlags-1, &fullNameFieldWidth, &aliasFieldWidth);

    for (size_t i = 1; i < nFlags; i++)
        printf(" --%-*s -%-*s %s\n", (int)fullNameFieldWidth, flags[i].fullName, (int)aliasFieldWidth, flags[i].alias, flags[i].description);
}

static void updateMaxFieldWidth(size_t *size, const char *name) {
    size_t len = strlen(name);
    if (*size < len) *size = len;
}

static void getFieldWidth(const Flag flags[], size_t nFlags, size_t *fullNameFieldWidth, size_t *aliasFieldWidth) {
    assert(flags);
    assert(fullNameFieldWidth);
    assert(aliasFieldWidth);

    for (size_t i = 0; i < nFlags; i++) {
        updateMaxFieldWidth(fullNameFieldWidth, flags[i].fullName);
        updateMaxFieldWidth(aliasFieldWidth, flags[i].alias);
    }
}
