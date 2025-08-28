#include <stdio.h>
#include <string.h>
#include <math.h>

#include "commands.h"
#include "argument_parser.h"
#include "myassert.h"

extern const Flag FLAGS[] = {
    {NULL,                     NULL, 0, "Solves square equation",    DefaultCommand                    },
    {"help",                   "h",  0, "Prints this text",          PrintHelpCommand                  },
    {"test",                   "t",  0, "Runs test",                 TestCommand                       },
    {"test-filename",          "tf", 1, "Set name of file for test", SetTestFilenameCommand            },
    {"test-no-compare-nroots", "tc", 0, "Disable root count "
                                        "comparison for test",       SetTestShouldCompareNRootsCommand },
    {"test-verbose",           "tv", 0, "Set verbose output for "
                                        "test (default true)",       SetTestVerboseCommand             },
    {"test-ignore",            "ti", 0, "Ignore test result",        SetTestIgnoreCommand              },
    {"no-test",                "nt", 0, "Runs program without test", NoTestCommand                     },
    {"complex",                "c",  0, "Solves equation in "
                                        "complex values "
                                        "(default disabled)",        SetIsComplexCommand               }
};
extern const size_t FLAGS_LENGTH = sizeof(FLAGS)/sizeof(*FLAGS);

int main(int argc, char *argv[]) {
    printf("Meow! (c) Poltorashka\n\n");

    //myassert(0, "some text %s", argv[0]);

    FlagContext context = {
        .isComplex = false,
        .test = {
            .filename = "test.txt",
            .verbose = false,
            .shouldCompareNRoots = true,
            .ignore = false
        }
    };

    ParseCode err = ParseFlags(argv, argc, FLAGS, FLAGS_LENGTH, (void*)&context);
    switch (err) {
        case PC_NO_ERROR:
            break;
        case PC_ERROR_UNKNOWN_FLAG:
            printf("Unknown flag\n");
            PrintHelpCommand(NULL, 0, (void*)&context);
            break;
        case PC_ERROR_WRONG_WORD_COUNT:
            printf("Incorrect flag argument count\n");
            PrintHelpCommand(NULL, 0, (void*)&context);
            break;
        default:
            myassert(0, "");
            break;
    }

    printf("\n\nCOMMIT GITHUB\n");
    return 0;
}


