//#include "C:\CodeBlocks\MinGW\include\TXlib.h"

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

#include "sorting.h"
#include "reading.h"
#include "writing.h"


sig_atomic_t current_line = 0;
void handle_sigsegv(int signum) {
    printf("Segfault!!  In line %d.\n", current_line);
    exit(0); // Завершаем программу
}




int main()
{
    if (signal(SIGSEGV, handle_sigsegv) == SIG_ERR) {
        perror("Ошибка при установке обработчика сигнала");
        return 1;
    }
    const char *input_file_name = "onegin_test.txt";
    const char *output_file_name = "onegin_output.txt";


    struct stat information_about_file;
    stat(input_file_name, &information_about_file);
    size_t buflen = information_about_file.st_size + 1;

    int reverse = 1;
    int MODE = RIGHT_COMPLANATION_CONST;


    size_t number_of_lines = 0;
    char* buffer = (char*) calloc(buflen, sizeof(char));


    TEXT_OBJECT onegin = {input_file_name, &buflen, buffer, &number_of_lines, NULL};


    Read_Text_From_File(&onegin);


    Sort_Lines(&onegin, reverse, MODE);
    Print_Lines_To_File(onegin, output_file_name);


    free((void *)onegin.pointer_to_buf);
    free((void *)onegin.lines_ptrs);

    printf("\n\nPROGRAM COMPLETE!!!\n");
    return 0;
}









