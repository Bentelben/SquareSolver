#include "commands.h"
#include "argument_parser.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>


extern const Flag FLAGS[] = {
    {"help",                "h",  0, "Prints this text",          PrintHelpCommand                    },
    {"test",                "T",  0, "Runs test",                 TestCommand                         },
    {"test-filename",       "Tf", 1, "Set name of file for test", Test_set_filenameCommand            },
    {"test-compare-nroots", "Tc", 1, "Set should compare root \
count for test (default true)",                                   Test_set_shouldCompareNRootsCommand },
    {"test-verbose",        "Tv", 1, "Set verbose output for \
test (default true)",                                             Test_set_verboseCommand             },
    {"test-ignore",         "Ti", 0, "Ignore test result",        Test_set_ignoreCommand              },
    {"no-test",             "NT", 0, "Runs program without test", NoTestCommand                       }
};
extern const size_t FLAGS_LENGTH = sizeof(FLAGS)/sizeof(*FLAGS);

int main(int argc, char *argv[]) {
    
    FlagContext context = {
        .test = {
            .filename = "test.txt",
            .verbose = true,
            .shouldCompareNRoots = true,
            .ignore = false
        }
    };

    ParseCode err = ParseFlags(argv, argc, FLAGS, FLAGS_LENGTH, (void*)&context);
    switch (err) {
        case PC_NO_ERROR_CONTINUE:
            DefaultCommand(NULL, 0, (void*)&context);
            break;
        case PC_NO_ERROR_STOP:
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
            assert(0);
            break;
    }
    return 0;
}


