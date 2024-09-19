#include "constants.h"
#include "reading.h"




int Is_Unnecessary_Symbol(char sym);
void Clean_Unnecessary_Symbols_From_Buffer(TEXT_OBJECT *ptr_file);
void Realloc_Buffer(char **pointer_to_buf);

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

    Clean_Unnecessary_Symbols_From_Buffer(file_constructor_ptr);

    Realloc_Buffer(&file_constructor_ptr->pointer_to_buf);


}




void Creat_Jagged_Array_Lines(TEXT_OBJECT *file_constructor_ptr)
{
    if (*file_constructor_ptr->number_of_lines == 0)
    {
        printf("Zero number of lines was sent in FUNCTION: Creat_Jagged_Array_Lines.");
        return;
    }


    file_constructor_ptr->lines_ptrs = (LINE *) calloc(*file_constructor_ptr->number_of_lines, sizeof(LINE));
    int counter = 0;
    file_constructor_ptr->lines_ptrs[counter].ptr_to_line = file_constructor_ptr->pointer_to_buf;
    file_constructor_ptr->lines_ptrs[counter].len_of_line = 0;
    char *string = file_constructor_ptr->pointer_to_buf;



    while (*string != EOF)
    {
        bool flag = false;
        while (*(++string) == '\0') flag = true;
        if (flag)
        {
            file_constructor_ptr->lines_ptrs[++counter].ptr_to_line = string;
            file_constructor_ptr->lines_ptrs[counter].len_of_line = 0;
            file_constructor_ptr->lines_ptrs[counter - 1].len_of_line = strlen(file_constructor_ptr->lines_ptrs[counter - 1].ptr_to_line);
        }
    }
    char *last_line = file_constructor_ptr->lines_ptrs[counter].ptr_to_line;
    file_constructor_ptr->lines_ptrs[counter].ptr_to_line = last_line;
    file_constructor_ptr->lines_ptrs[counter].len_of_line = strlen(last_line);

}


int Is_Unnecessary_Symbol(char sym)
{
    return ((sym == '\n' || sym == '\r' || sym == ' ' || sym == '\t') && sym != EOF) ? 1 : 0;
}

void Clean_Unnecessary_Symbols_From_Buffer(TEXT_OBJECT *ptr_file)
{

    char *s = ptr_file->pointer_to_buf;
    while (*s != EOF)
    {
        if (*s == '\n' || *s == '\r')
        {
            (*ptr_file->number_of_lines) += 1;
            *s = '\0';
            s++;
            while (Is_Unnecessary_Symbol(*s))
            {
                *s = '\0';
                s++;
            }
            if (*s == EOF) break;
        }
        s++;
    }

    if (s[-1] != '\0')
    {
        (*ptr_file->number_of_lines) += 1;
    }
}


void Realloc_Buffer(char **pointer_to_buf)
{
    char *s = *pointer_to_buf;
    char *uk_on_left = *pointer_to_buf;

    while (*s != EOF)
    {
        *uk_on_left = *s;
        uk_on_left++;
        if (*s == '\0')
        {
            s++;
            while (*s == '\0' && *s != EOF)
            {
                s++;
            }
            continue;
        }
        s++;
    }

    *uk_on_left = EOF;

    *pointer_to_buf = (char *) realloc(*pointer_to_buf, (uk_on_left - *pointer_to_buf + 2) * sizeof(char));

}
