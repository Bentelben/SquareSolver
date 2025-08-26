#ifndef COMMANDS_H
#define COMMANDS_H

struct FlagContext {
    bool isComplex;
    struct {
        const char *filename;
        bool verbose;
        bool shouldCompareNRoots;
        bool ignore;
    } test;
};

bool DefaultCommand(char *args[], int nArgs, void *context);
bool PrintHelpCommand(char *args[], int nArgs, void *context);
bool TestCommand(char *args[], int nArgs, void *context);
bool Test_set_filenameCommand(char *args[], int nArgs, void *context);
bool Test_set_shouldCompareNRootsCommand(char *args[], int nArgs, void *context);
bool Test_set_verboseCommand(char *args[], int nArgs, void *context);
bool Test_set_ignoreCommand(char *args[], int nArgs, void *context);
bool NoTestCommand(char *args[], int nArgs, void *context);
bool Set_isComplexCommand(char *args[], int nArgs, void *context);

#endif
