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
    help.name = "-h";
    help.long_name = "help";
    help.argument_description = "shows this help text";
    help.type = ARG_BOOL;

    parser.args[0] = help;
    return parser;
}
*/

/* TODO Write a hash table to store everything from argv in and see if its faster*/
int parse_argoption_name_isvalid(const char * arg_option_name, 
        const char **argv, 
        int argc, int arg) {
   
    /* if no next argument return false */
    if (arg+1 == argc) {
        return 0;
    }   
    
    /* if next argument is the start of another retunrn false */
    if (*argv[arg+1] == 45) {
        return 0;
    }

    if (strcmp(arg_option_name, argv[arg]) == 0) {
        return 1;
    }

    return 0;
}

void argparser_parse(ArgParserArgOption *args, 
        int args_array_size, 
        int argc, const char *argv[]) {

    for (int i = 0;i < args_array_size;i++)  {
        switch (args[i].type) {
            case ARG_BOOL: {
                int *result = (int *)(args[i].result);
                *result = 0;
                for (int arg = 0;arg < argc;++arg) {
                    if (strcmp(args[i].name, argv[arg]) == 0) {
                        *result = 1;
                        args[i].result = result;
                        break;
                    }
                } 
            } break;

            case ARG_INT: {
                long *result = (long *)(args[i].result);
                args[i].result = NULL;
                for (int arg = 0;arg < argc;++arg) {
                    if (parse_argoption_name_isvalid(args[i].name, argv, argc, arg)) {
                        *result = strtol(argv[++arg], NULL, 10);
                        args[i].result = result;
                        break;
                    }
                }
            } break; 

            case ARG_FLOAT: {
                double *result = (double *)(args[i].result);     
                args[i].result = NULL;
                for (int arg = 0;arg < argc;++arg) {

                    if (parse_argoption_name_isvalid(args[i].name, argv, argc, arg)) {
                        *result = strtod(argv[++arg],NULL);
                        args[i].result = result;
                        break;
                    }
                }
            } break;

            case ARG_STRING: {
                args[i].result = NULL;
                for (int arg = 0; arg < argc;++arg) {
                    if (parse_argoption_name_isvalid(args[i].name, argv, argc, arg)) {
                        args[i].result = argv[++arg];
                        break;
                    }
                }
            } break;

            default:
                break;
        }
    }
}
