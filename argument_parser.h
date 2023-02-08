#ifndef ARGUMENT_PARSER_H_
#define ARGUMENT_PARSER_H_

typedef char bool;
typedef enum ArgumentArgType {
    ARG_BOOL,
    ARG_INT,
    ARG_FLOAT,
    ARG_STRING,
    ARG_END,
} ArgumentArgType;

/* Argument
 * short_name: name of argument begining with '-'
 * long_name: --long-name of argument omiting the '--' 
 * argument_description: the description used in the help text
 * ArgType: enum member of ArgType
 */

typedef struct ArgumentOption {
    const char *short_name;
    const char *long_name;
    const char *argument_description;
    ArgumentArgType type;
    void *result;
    int argument_position;
} ArgumentOption;

/* ArgParser 
 * argp_name: name used in --help 
 * argp_description: description used in --help
 * args: pointer to an array of arguments if ArgParser was created using create function first one is always --help; 
 */

typedef struct ArgParser {
    ArgumentOption *args; /* Pointer to an array of args */
} ArgParser;

extern ArgParser argparser_init(ArgParser *parser); /* creates parser struct with help arg */
extern void argparser_parse(ArgumentOption *arg, int argc, const char *argv[]); /* parses argument and returns value into result */

#endif
