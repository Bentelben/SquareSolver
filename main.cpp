#include <math.h>
#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "io/error.h"
#include "io/argument_parser.h"
#include "utils/myassert.h"

extern const Flag FLAGS[] = {
    {NULL,                     NULL, 0, true,  "Solves square equation",    DefaultCommand                    },
    {"help",                   "h",  0, true,  "Prints this text",          PrintHelpCommand                  },
    {"test",                   "t",  0, true,  "Runs test",                 TestCommand                       },
    {"test-filename",          "tf", 1, false, "Set name of file for test", SetTestFilenameCommand            },
    {"test-no-compare-nroots", "tc", 0, false, "Disable root count "
                                               "comparison for test",       SetTestShouldCompareNRootsCommand },
    {"test-verbose",           "tv", 0, false, "Set verbose test output",   SetTestVerboseCommand             },
    {"test-ignore",            "ti", 0, false, "Ignore test result",        SetTestIgnoreCommand              },
    {"no-test",                "nt", 0, true,  "Runs program without test", NoTestCommand                     },
    {"complex",                "c",  0, false, "Solves equation in "
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
            PrintError("unknown flag");
            PrintHelpCommand(NULL, 0, (void*)&context);
            break;
        case PC_ERROR_WRONG_WORD_COUNT:
            PrintError("wrong argument count for flag");
            PrintHelpCommand(NULL, 0, (void*)&context);
            break;
        case PC_ERROR_FLAG_FUNCTION_FAILURE:
            PrintError("Stopping program...");
            break;
        default:
            myassert(0, "Unhandled argument parser code");
            break;
    }

    printf("\n\nCOMMIT GITHUB\n");
    return 0;
}


