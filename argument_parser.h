#ifndef ARGUMENT_PARSER_H_
#define ARGUMENT_PARSER_H_

typedef enum ArgumentArgType {
    ARG_BOOL,
    ARG_INT,
    ARG_FLOAT,
    ARG_STRING,
} ArgumentArgType;

/* Argument
 * short_name: name of argument begining with '-'
 * long_name: --long-name of argument omiting the '--' 
 * argument_description: the description used in the help text
 * ArgType: enum member of ArgType
 */

typedef struct ArgumentOption {
    const char *name;
    ArgumentArgType type;
    void *result;
} ArgumentOption;

extern void argparser_parse(ArgumentOption *args, int args_array_size, int argc, const char *argv[]); 
/* parses argument and returns value into result */

#endif
