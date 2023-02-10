#include "argument_parser.h"
#include <string.h>
#include <stdio.h>

int main(int argc, const char *argv[]) {
    ArgParserArgOption options[3];  
    memset(options, 0, sizeof(options));

    int result_int;
    int result_bool;
    options[0].name = "-h";
    options[0].type = ARG_STRING;
    options[1].name = "-i";
    options[1].type = ARG_INT;
    options[1].result = &result_int;
    options[2].name = "-b";
    options[2].type = ARG_BOOL;
    options[2].result = &result_bool;

    argparser_parse(options, 3, argc, argv);
    if (options[0].result) {
        printf("%s\n", (const char *)options[0].result);
    }
    else {
        printf("no argument supplied for %s\n", options[0].name);
    }
    if (options[1].result) {
        printf("%d\n", result_int);
    }
    else {
        printf("no argument supplied for %s\n", options[1].name);
    }

    if (result_bool) {
        printf("argument set for %s\n", options[2].name);
    }
    else {
        printf("argument not set for %s\n", options[2].name);
    }

    return 0;
}
