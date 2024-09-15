#include "constants.h"
#include "reading.h"


void Read_Text_From_File(TEXT_OBJECT *file_constructor_ptr)
{
    Fill_Buffer(file_constructor_ptr);
    Recycle_Buffer(file_constructor_ptr);
    Creat_Jagged_Array_Lines(file_constructor_ptr);

}


void Fill_Buffer(TEXT_OBJECT *file_constructor_ptr)
{
    FILE *file_ptr = fopen(file_constructor_ptr->file_name, "rb");
    assert(file_ptr != NULL);

    int number_buf_symbols = 0;
    number_buf_symbols = fread(file_constructor_ptr->pointer_to_buf, sizeof(char), *(file_constructor_ptr->buflen) + 1, file_ptr);
    file_constructor_ptr->pointer_to_buf[number_buf_symbols] = EOF;
    *file_constructor_ptr->number_of_lines = 0;
    fclose(file_ptr);
}



void Recycle_Buffer(TEXT_OBJECT *file_constructor_ptr)
{

    char *s = file_constructor_ptr->pointer_to_buf;

    while (*s != EOF)
    {
        if (*s == '\n' || *s == '\r')
        {
            (*file_constructor_ptr->number_of_lines)++;
            *s = '\0';
            s++;
            while (*s == '\n' || *s == '\r')
            {
                *s = '\0';
                s++;
            }
            continue;
        }
        s++;
    }

    if (s[-1] != '\n' && s[-1] != '\r')
    {
        (*file_constructor_ptr->number_of_lines)++;
    }

}




void Creat_Jagged_Array_Lines(TEXT_OBJECT *file_constructor_ptr)
{
    if (*file_constructor_ptr->number_of_lines == 0)
    {
        printf("Zero number of lines was sent in FUNCTION: Creat_Jagged_Array_Lines.");
        return;
    }
    file_constructor_ptr->pointers_to_lines = (char **) calloc(*file_constructor_ptr->number_of_lines, sizeof(char *));
    int counter = 0;
    file_constructor_ptr->pointers_to_lines[counter] = file_constructor_ptr->pointer_to_buf;
    char *s = file_constructor_ptr->pointer_to_buf;


    while (*s != EOF)
    {
        bool flag = false;
        while (*(++s) == '\0') flag = true;
        if (flag)
        {
            file_constructor_ptr->pointers_to_lines[++counter] = s;
        }
    }
}
