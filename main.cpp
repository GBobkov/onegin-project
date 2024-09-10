#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>


int cmpln_str(char* s1, char* s2);
void reading_text_from_file(FILE* file_pointer, char* symbols, char** lines, int* lines_counter);
void sort_lines(char **lines, int num_of_lines, int flag);
void print_lines_to_file(FILE* fp, char **lines, int num_of_lines);
int main(int argc, char** argv)
{   
    printf("%d\n", argc);
    const int buf = 1024;
    FILE *file_ptr =  fopen("run_dir/check.txt", "r");
    assert(file_ptr != NULL);

    char* symbols_in_file = (char*) calloc(buf, sizeof(char));
    char** pointer_to_beginning_lines = (char**) calloc(buf, sizeof(char *));
    pointer_to_beginning_lines[0] = symbols_in_file;
    int lines_counter = 0;
    int flag = -1;

    reading_text_from_file(file_ptr, symbols_in_file, pointer_to_beginning_lines, &lines_counter);
 
    sort_lines(pointer_to_beginning_lines, lines_counter, flag);

    print_lines_to_file(stdout, pointer_to_beginning_lines, lines_counter);



    return 0;
}



int cmpln_str(char* s1, char* s2)
{
    while (*s1 != '\0' && *s2 != '\0')
        if (*s1++ != *s2++) return *(--s1) - *(--s2);
    return *s1 - *s2;
}



void reading_text_from_file(FILE* file_pointer, char* symbols, char** lines, int* lines_counter)
{
    int sym_counter = 0;
    char c = EOF;
    c = fgetc(file_pointer);
    while (c != EOF)
    {
        if (c == '\n')
        {
            symbols[sym_counter++] = '\0';
            lines[++(*lines_counter)] = symbols + sym_counter;
            c = fgetc(file_pointer);

            continue;
        }
        symbols[sym_counter++] = c;
        c = fgetc(file_pointer);
    }
    *lines_counter += 1;
}


void sort_lines(char **lines, int num_of_lines, int flag)
{
    for (int i = 0; i < num_of_lines; i++)
    {
        for (int j = 1; j < num_of_lines - i; j++)
        {
            if (flag * cmpln_str(lines[j - 1], lines[j]) > 0)
            {
                char* tmp = NULL;
                tmp = lines[j-1];
                lines[j - 1] = lines[j];
                lines[j] = tmp;
            }
        }
    }
}



void print_lines_to_file(FILE* fp, char **lines, int num_of_lines)
{
    for (int i = 0; i < num_of_lines; i++)
    {
        fputs(lines[i], fp);
        fputc('\n', fp);
    }
}
