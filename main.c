#include "argument_parser.h"
#include <string.h>
#include <stdio.h>

int main(int argc, const char *argv[]) {
    int res1;
    char *res2[100];

    ArgumentOption options[3];  
    memset(options, 0, sizeof(options));

    options[0].short_name = "-h";
    options[0].type = ARG_STRING;
    options[0].result = res2;
    options[1].short_name = "-i";
    options[1].type = ARG_INT;
    options[1].result = &res1;
    options[2].type = ARG_END;


    argparser_parse(options, argc, argv);
    printf((const char *)options[0].result);
    printf("%d", *((int *)options[1].result));

    return 0;
}
