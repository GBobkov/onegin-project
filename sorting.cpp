#include "sorting.h"




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

