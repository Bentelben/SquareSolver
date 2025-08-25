#include "argument_parser.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static int getMaxFlagNameLength(Flag flags[], int nFlags);

static bool IsEqualFlag(char *arg, const char *flagName) {
    int i = 0;
    for (; arg[i+1] != '\0' && flagName[i] != '\0'; i++)
        if (arg[i+1] != flagName[i]) return false;
    return arg[i+1] == flagName[i];
}

static Flag *ParseFlag(char *arg, Flag flags[], int nFlags) {
    for (int i = 0; i < nFlags; i++)
        if (IsEqualFlag(arg, flags[i].name)) return flags+i;
    return NULL;
}

ParseCode ParseFlags(char *argv[], Flag flags[], int nFlags) {
    assert(argv != NULL);
    assert(flags != NULL);

    for (int i = 1; argv[i] != NULL; i++) {
        Flag *flag = ParseFlag(argv[i], flags, nFlags);
        if (flag == NULL)
            return PC_ERROR_UNKNOWN_FLAG;

        int j = 0;
        while (argv[i+j+1] != NULL) {
            if (argv[i+j+1][0] == '-') break;
            j++;
        }
        if (flag->nNextWords != -1 && j != flag->nNextWords)
            return PC_ERROR_WRONG_WORD_COUNT;

        flag->func(argv + i + 1, j);
        i += j;
    }
    return PC_NO_ERROR;
}

void PrintArgumentInfo(Flag flags[], int nFlags) {
    assert(flags != NULL);

    int fieldWidth = getMaxFlagNameLength(flags, nFlags);
    for (int i = 0; i < nFlags; i++)
        printf(" -%-*s  %s\n", (int)fieldWidth, flags[i].name, flags[i].description);
}

static int getMaxFlagNameLength(Flag flags[], int nFlags) {
    size_t maxWidth = 0;
    for (int i = 0; i < nFlags; i++)
        if (maxWidth < strlen(flags[i].name))
            maxWidth = strlen(flags[i].name);
    return (int)maxWidth;
}
