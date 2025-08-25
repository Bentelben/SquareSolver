#include "commands.h"
#include "argument_parser.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>


Flag FLAGS[] = {
    {"help",   0, "Prints this text", PrintHelpCommand},
    {"test",   0, "Runs test", TestCommand},
    {"notest", 0, "Runs program without test", NoTestCommand}
};
int FLAGS_LENGTH = sizeof(FLAGS)/sizeof(*FLAGS);


bool shouldRunDefault = true;

int main(int argc, char *argv[]) {
    ParseCode err = ParseFlags(argv, FLAGS, FLAGS_LENGTH);
    switch (err) {
        case PC_NO_ERROR:
            DefaultCommand(NULL, 0);
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


