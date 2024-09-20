#include "write.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

void fputs2(char* symbol, FILE* file_ptr);

void Print_Lines_To_File(TEXT_OBJECT file_constructor_ptr, const char* output_file_name)
{
    FILE *file_ptr = NULL;

    file_ptr = fopen(output_file_name, "w");

    if(file_ptr == NULL)
    {
        printf("Can't open output_file. name=%s.\n", output_file_name);
        exit(1);
    }
    if (file_constructor_ptr.buffer_ptr == NULL || file_constructor_ptr.lines_ptrs == NULL)
    {
        printf("Error of reading file. NULL buffer or NULL ptr to lines.\n");
        exit(1);
    }

    
    
    for (size_t i = 0; i < file_constructor_ptr.num_lines; i++)
    {
        file_constructor_ptr.lines_ptrs[i].line_ptr[file_constructor_ptr.lines_ptrs[i].line_len + 1] = '\0';
        fputs(file_constructor_ptr.lines_ptrs[i].line_ptr, file_ptr);
    }

    fclose(file_ptr);
}
