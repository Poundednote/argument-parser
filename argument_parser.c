#include "argument_parser.h"
#include <stdlib.h>
#include <string.h>

/* TDOO: modify this into a generate help text function 
ArgParser argparser_create(const char *name, const char *description, const char *epilouge) {
    ArgParser parser = {0};
    parser.argp_name = name;
    parser.argp_description = description;
    parser.epilouge = epilouge;

    ArgumentOption help = {0};
    help.short_name = "-h";
    help.long_name = "help";
    help.argument_description = "shows this help text";
    help.type = ARG_BOOL;

    parser.args[0] = help;
    return parser;
}
*/

/* TODO Write a hash table to store everything from argv in see if its faster*/
void argparser_parse(ArgumentOption *args, int argc, const char *argv[]) {
    /* go over arguments and store where options are in argc in ArgumentOption with the argvalue as a map */
    for (ArgumentOption *i = args;i->type != ARG_END;i++) {
        switch (i->type) {
            case ARG_BOOL: {
                bool *result;
                *result = 0;
                for (int arg = 0;arg < argc;arg++) {
                    /* check if first character in arg is equal to ASCII for '-' */
                    if (*argv[arg] == 45) {
                        for (const char *option = argv[arg]; option != 0; ++option) {
                            if (option == i->short_name || option == i->long_name) {
                                *result = 1;
                            }
                        }
                    }
                }
                i->result = result;  
            } break;

            case ARG_INT: {
                int *result = (int *)(i->result);
                *result = 0;
                for (int arg = 0;arg < argc;arg++) {
                    if (strcmp(argv[arg], i->short_name) == 0) {
                        *result = strtol(argv[arg+1], NULL, 10);
                        break;
                    }
                } 
            } break;

            case ARG_FLOAT: {
                double *result = (double *)(i->result);     
                *result = 0;
                for (int arg = 0;arg < argc;arg++) {
                    if (strcmp(argv[arg], i->short_name) == 0) {
                        *result = strtod(argv[arg+1], NULL);
                        break;
                    }
                }
            } break;

            case ARG_STRING: {
                const char *result = (const char *)i->result;
                for (int arg = 0; arg < argc;arg++) {
                    if (strcmp(argv[arg], i->short_name) == 0) {
                        i->result = argv[arg+1];
                        break;
                    }
                }
            } break;

            default:
                break;
        }
    }
}
