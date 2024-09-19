#include "writing.h"
#include <string.h>

void Print_Lines_To_File(TEXT_OBJECT file_constructor_ptr, const char* output_file_name)
{
    FILE *file_ptr = NULL;
    if (strcmp(output_file_name, "stdout") == 0) file_ptr = stdout;
    else file_ptr = fopen64(output_file_name, "w");

    assert(file_ptr != NULL);
    assert(file_constructor_ptr.pointer_to_buf != NULL);
    assert(file_constructor_ptr.lines_ptrs != NULL);


    
    for (size_t i = 0; i < *file_constructor_ptr.number_of_lines; i++)
    {
        printf("%s\n", file_constructor_ptr.lines_ptrs[i].ptr_to_line);

        fputs(file_constructor_ptr.lines_ptrs[i].ptr_to_line, file_ptr);
        fputc('\n', file_ptr);
    }

    fclose(file_ptr);
}
