#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <cstdio>

#include "sorting.h"
#include "reading.h"



volatile sig_atomic_t current_line = 0;
void handle_sigsegv(int signum) {
    printf("Segfault!!  In line %d.\n", current_line);
    exit(0); // Завершаем программу
}





void Print_Lines_To_File(TEXT_OBJECT file_constructor_ptr, FILE* file_ptr);

int main()
{
    if (signal(SIGSEGV, handle_sigsegv) == SIG_ERR) {
        perror("Ошибка при установке обработчика сигнала");
        return 1;
    }

    const char *file_name = "C:/Users/bobko/projects/second-project/run_dir/onegin.txt";


    struct stat information_about_file;
    stat(file_name, &information_about_file);
    size_t buflen = information_about_file.st_size + 1;

    int reverse = 1;
    int MODE = RIGHT_COMPLANATION_CONST;


    size_t number_of_lines = 0;
    char* buffer = (char*) calloc(buflen, sizeof(char));
    char** pointers_to_lines = NULL;

    struct TEXT_OBJECT onegin = {file_name, &buflen, buffer, &number_of_lines, pointers_to_lines};


    Read_Text_From_File(&onegin);
    Sort_Lines(&onegin, reverse, MODE);
    Print_Lines_To_File(onegin, stdout);


    return 0;
}








void Print_Lines_To_File(TEXT_OBJECT file_constructor_ptr, FILE* file_ptr)
{
    assert(file_ptr != NULL);
    assert(file_constructor_ptr.pointer_to_buf != NULL);
    assert(file_constructor_ptr.pointers_to_lines != NULL);


    for (size_t i = 0; i < *file_constructor_ptr.number_of_lines; i++)
    {

        fputs(file_constructor_ptr.pointers_to_lines[i], file_ptr);

        fputc('\n', file_ptr);
    }


}



