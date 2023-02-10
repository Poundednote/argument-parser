# ArgumentParser

ArgumentParser - A very basic argument parsing library written in C

## Description

This project was created in my need to be able to parse command line arguments 
in another project however i didnt want to use `getopt`. As of now it supports 
only 4 types of arguments.

* Boolean - `ARG_BOOL`
* Integer - `ARG_INT`
* Float - `ARG_FLOAT`
* String - `ARG_STRING`


I may expand this project in the future

## Interface

### ArgumentOption

```C
typedef struct ArgParserArgOption {
    const char *name;
    ArgParserArgOptionType type;
    void *result;
} ArgParserArgOption;
```
This is the options struct to be filled out so that arguments may be parsed in
the command line according to their name the struct looks as follows 

### ArgumentArgType

```C
typedef enum ArgParserArgOptionType {
    ARG_BOOL,
    ARG_INT,
    ARG_FLOAT,
    ARG_STRING,
} ArgParserArgOptionType;
```
This is the enum type to be used for the `type` field in `ArgumentOption`

* `name` - the name of the argument all `ArgumentOption` types except 
`ARG_BOOL` expect an argument directly after the `name` in `argv[]`

* `type` - a member of the enum `ArgumentOptionArgType` 

* `result` - a pointer to a user supplied varaible in which it will place the 
    results to the parsed arguments after caling `argparser_parse`. If no argument 
    was given result is always a nullpointer except for `ARG_BOOL` in which case it 
    will set the value of the user variable to zero


### argparser_parse

``` C
extern void argparser_parse(
        ArgParserArgOption *args, 
        int args_array_size, 
        int argc, 
        const char *argv[]); 
```
This function parses all of the arguments supplied by the user and place
them inside the `result` field of `ArgParserArgOption`

* `ArgParserArgOption *args` - a pointer to an array of `ArgParserArgOption` 
structs
* `int args_array_size` - the number of elements in the array
* `int argc` - argc from main
* `const char *argv[]` - argv from main

The return types are as you would expect for the types inside of 
`ArgParserArgOption`

* `ARG_BOOL` - returns a long integer 1 or 0
* `ARG_INT` - returns a long integer
* `ARG_FLOAT` - returns a double
* `ARG_STRING` - returns a char pointer to the string inside of argv

NOTE: because `ARG_STRING` is the only one that returns a pointer to a string
inside argv this type does't require the user to supply the `result` field with
a pointer to a varaible

If `argparser_parse` cannot find an argument it will return a null pointer

### Example Program

```C
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
```

## Future Improvements
* add a generate help function that takes descriptions and automaticaly generates a
    helptext and a `--help` option
