#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <ctype.h>

struct LINE 
{
    char* ptr_to_line;
    size_t len_of_line;
};

struct TEXT_OBJECT 
{
    const char *file_name;
    size_t* buflen;
    char *pointer_to_buf;
    size_t* number_of_lines;
    LINE *lines_ptrs;
};

const int LEFT_COMPLANATION_CONST = -1;
const int RIGHT_COMPLANATION_CONST = 1;

#endif