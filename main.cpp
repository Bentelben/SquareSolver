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
    int err = ParseFlags(argv, FLAGS, FLAGS_LENGTH);
    if (err == -1) {
        printf("Unknown flag\n");
        PrintHelpCommand(NULL, 0);
    } else if (err == -2) {
        printf("Incorrect flag argument count\n");
        PrintHelpCommand(NULL, 0);
    }
    if (shouldRunDefault) DefaultCommand(NULL, 0);
    return 0;
}


