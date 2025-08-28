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

bool DefaultCommand                    (char *[], int, void *);
bool PrintHelpCommand                  (char *[], int, void *);
bool TestCommand                       (char *[], int, void *);
bool SetTestFilenameCommand            (char *[], int, void *);
bool SetTestShouldCompareNRootsCommand (char *[], int, void *);
bool SetTestVerboseCommand             (char *[], int, void *);
bool SetTestIgnoreCommand              (char *[], int, void *);
bool NoTestCommand                     (char *[], int, void *);
bool SetIsComplexCommand               (char *[], int, void *);

#endif
