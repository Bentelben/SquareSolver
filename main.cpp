#include "commands.h"
#include "argument_parser.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>


extern const Flag FLAGS[] = {
    {"h",  0, "Prints this text",          PrintHelpCommand                    },
    {"T",  0, "Runs test",                 TestCommand                         },
    {"Tf", 1, "Set name of file for test", Test_set_filenameCommand            },
    {"Tc", 1, "Set should compare root \
count for test (default true)",            Test_set_shouldCompareNRootsCommand },
    {"Tv", 1, "Set verbose output for \
test (default true)",                      Test_set_verboseCommand             },
    {"Ti", 0, "Ignore test result",        Test_set_ignoreCommand              },
    {"NT", 0, "Runs program without test", NoTestCommand                       }
};
extern const int FLAGS_LENGTH = sizeof(FLAGS)/sizeof(*FLAGS);

const char *test_filename = "test.txt";
bool test_shouldCompareNRoots = true;
bool test_verbose = true;
bool test_ignore = false;

int main(int argc, char *argv[]) {
    ParseCode err = ParseFlags(argv, argc, FLAGS, FLAGS_LENGTH);
    switch (err) {
        case PC_NO_ERROR_CONTINUE:
            DefaultCommand(NULL, 0);
            break;
        case PC_NO_ERROR_STOP:
            break;
        case PC_ERROR_UNKNOWN_FLAG:
            printf("Unknown flag\n");
            PrintHelpCommand(NULL, 0);
            break;
        case PC_ERROR_WRONG_WORD_COUNT:
            printf("Incorrect flag argument count\n");
            PrintHelpCommand(NULL, 0);
            break;
        default:
            assert(0);
            break;
    }
    return 0;
}


