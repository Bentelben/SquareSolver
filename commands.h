#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdlib.h>

bool DefaultCommand(char *args[], int nArgs);
bool PrintHelpCommand(char *args[], int nArgs);
bool TestCommand(char *args[], int nArgs);
bool NoTestCommand(char *args[], int nArgs);

#endif
