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


const int LEFT_COMPLANATION_CONST = -1;
const int RIGHT_COMPLANATION_CONST = 1;

struct TEXT_OBJECT 
{
    const char *file_name;
    size_t* buflen;
    char *pointer_to_buf;
    size_t* number_of_lines;
    char **pointers_to_lines;
};

struct LINE
{
    char *pointer_to_lines;
    int linelen;
};


volatile sig_atomic_t current_line = 0;
void handle_sigsegv(int signum) {
    printf("Segfault!!  In line %d.\n", current_line);
    exit(0); // Завершаем программу
}




int Left_Str_Comparator(char* s1, char* s2);
int Right_Str_Comparator(char* s1, char* s2);
int Multy_Compare(char* s1, char* s2, int mode);



    

void Read_Text_From_File(TEXT_OBJECT *file_constructor_ptr);
void Sort_Lines(TEXT_OBJECT *file_constructor_ptr, int reverse, int mode);
void Print_Lines_To_File(TEXT_OBJECT file_constructor_ptr, FILE* file_ptr);
void Creat_Jagged_Array_Lines(TEXT_OBJECT *file_constructor_ptr);
void Recycle_Buffer(TEXT_OBJECT *file_constructor_ptr);
void Fill_Buffer(TEXT_OBJECT *file_constructor_ptr);



int main()
{   
    if (signal(SIGSEGV, handle_sigsegv) == SIG_ERR) {
        perror("Ошибка при установке обработчика сигнала");
        return 1;
    }


    
    const char *file_name = "onegin.txt";

    

    struct stat information_about_file;
    stat(file_name, &information_about_file);
    size_t buflen = information_about_file.st_size + 1;
    
    int reverse = 1;
    int MODE = LEFT_COMPLANATION_CONST;
    
    
    size_t number_of_lines = 0;
    char* buffer = (char*) calloc(buflen, sizeof(char));
    char** pointers_to_lines = NULL;
    
    struct TEXT_OBJECT onegin = {file_name, &buflen, buffer, &number_of_lines, pointers_to_lines};
    

    Read_Text_From_File(&onegin);
    Sort_Lines(&onegin, reverse, MODE);
    Print_Lines_To_File(onegin, stdout);



    return 0;
}



int Left_Str_Comparator(char* s1, char* s2)
{
    while (*s1 != '\0' && *s2 != '\0')
        if (*s1++ != *s2++) return *(--s1) - *(--s2);
    return *s1 - *s2;
}

int Right_Str_Comparator(char* s1, char* s2)
{

    int first = 0;
    while (s1[++first] != '\0');

    int second = 0;
    while (s2[second] != '\0')
    {
        second++;
    }
    

    while (first >= 0 && second >= 0)
    {

        while (!isalpha(s1[first]) && first > 0)  first--;
        while (!isalpha(s2[second]) && second > 0) second--;
        
        //printf("word1: %s\nword2: %s\nfirst=%d\nsecond=%d\n%c != %c\n\n",s1,s2,first,second,(s1[first--]), tolower(s2[second--]), tolower(s1[first--]) != tolower(s2[second--]));
        if (tolower(s1[first--]) != tolower(s2[second--]))
            return s1[++first] - s2[++second];
    }
    if (first == second) return 0;
    if (first < 0) return -1;
    return 1;
    
}

int Multy_Compare(char* s1, char* s2, int mode)
{
    
    if (mode == LEFT_COMPLANATION_CONST)
    {
        return Left_Str_Comparator(s1,s2);
    }
    if (mode == RIGHT_COMPLANATION_CONST)
    {
        return Right_Str_Comparator(s1, s2);
    }
    return 0;
}




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




void Sort_Lines(TEXT_OBJECT *file_constructor_ptr, int reverse, int mode)
{
    size_t number_of_lines = *file_constructor_ptr->number_of_lines;
    for (int i = 0; i < number_of_lines; i++)
    {
        for (int j = 1; j < number_of_lines; j++)
        {
            if (reverse * Multy_Compare(file_constructor_ptr->pointers_to_lines[j - 1], file_constructor_ptr->pointers_to_lines[j], mode) > 0)
            {
                char* tmp = NULL;
                tmp = file_constructor_ptr->pointers_to_lines[j-1];
                file_constructor_ptr->pointers_to_lines[j - 1] = file_constructor_ptr->pointers_to_lines[j];
                file_constructor_ptr->pointers_to_lines[j] = tmp;
            }
        }
    }
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


