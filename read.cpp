#include "read.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static void Fill_Struct(TEXT_OBJECT* file_struct_ptr);
static void Fill_Buffer(TEXT_OBJECT *file_struct_ptr);
static void Recycle_Buffer_Create_Lines_Array(TEXT_OBJECT *file_struct_ptr);
static int Is_Unnecessary_Symbol(char sym);


void Read_Text_From_File(TEXT_OBJECT *file_struct_ptr)
{
    Fill_Struct(file_struct_ptr);
    Fill_Buffer(file_struct_ptr);
    Recycle_Buffer_Create_Lines_Array(file_struct_ptr);
}



static void Fill_Struct(TEXT_OBJECT* file_struct_ptr)
{
    struct stat information_about_file;
    stat(file_struct_ptr->file_name, &information_about_file);
    size_t buflen = information_about_file.st_size + 1;
    size_t number_of_lines = 0;
    char* buffer = (char*) calloc(buflen, sizeof(char));
    file_struct_ptr->buflen = buflen;
    file_struct_ptr->buffer_ptr = buffer;
}



static void Fill_Buffer(TEXT_OBJECT *file_struct_ptr)
{
    FILE *file_ptr = fopen(file_struct_ptr->file_name, "rb");
    
    if (file_ptr == NULL)
    {
        printf("File was not found. file_name=\"%s\"\nStop program!\n", file_struct_ptr->file_name);
        exit(1);
    }
    
    int number_buf_symbols  = fread(file_struct_ptr->buffer_ptr, sizeof(char), file_struct_ptr->buflen + 1, file_ptr);
    file_struct_ptr->buffer_ptr[number_buf_symbols] = EOF;
    file_struct_ptr->num_lines = 0;
    fclose(file_ptr);
    
    
}

static void Recycle_Buffer_Create_Lines_Array(TEXT_OBJECT *file_struct_ptr)
{

    LINE *lines_ptrs = (LINE *)calloc(file_struct_ptr->buflen / 2 + 1, sizeof(LINE));
    size_t num_lines = 0;
    lines_ptrs[num_lines++].line_ptr = file_struct_ptr->buffer_ptr;
    char *sym = file_struct_ptr->buffer_ptr;
    while (true)
    {
        if (*sym == '\n' || *sym == '\r')
        {   
            lines_ptrs[num_lines - 1].line_len = sym - lines_ptrs[num_lines - 1].line_ptr;
            while (Is_Unnecessary_Symbol(*sym))
            {
                sym++;
            }
            if (*sym == EOF) break;
            lines_ptrs[num_lines++].line_ptr = sym;
        }
        sym++;
        if (*sym == EOF)
        {
            *(sym - 2) = '\r';
            *(sym - 1) = '\n';
            lines_ptrs[num_lines - 1].line_len = sym - lines_ptrs[num_lines - 1].line_ptr;
            break;
        }
    }
    file_struct_ptr->num_lines = num_lines;
    lines_ptrs = (LINE *) realloc(lines_ptrs, (num_lines + 1) * sizeof(LINE));
    lines_ptrs[num_lines].line_ptr = NULL;
    file_struct_ptr->lines_ptrs = lines_ptrs;
}



static int Is_Unnecessary_Symbol(char sym)
{
    return ((sym == '\n' || sym == '\r' || sym == ' ' || sym == '\t') && sym != EOF) ? 1 : 0;
}