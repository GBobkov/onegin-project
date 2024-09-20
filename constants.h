#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stddef.h>
struct LINE
{
    char* line_ptr;
    size_t line_len;
};

struct TEXT_OBJECT
{
    const char *file_name;
    size_t buflen;
    char* buffer_ptr;
    size_t num_lines;
    LINE *lines_ptrs;
};

const char LEFT_COMPLANATION_CONST = 'l';
const char RIGHT_COMPLANATION_CONST = 'r';
const int TRUE_FLAG_CONST = 1;
const int FALSE_FLAG_CONST = 0;

#endif