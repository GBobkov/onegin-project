#include "sorting.h"



int Left_Str_Comparator(LINE s1_, LINE s2_)
{   
    char *s1 = (char *) s1_.ptr_to_line;
    char *s2 = (char *) s2_.ptr_to_line;
    
    while (*s1 != '\0' && *s2 != '\0')
        if (*s1++ != *s2++) return *(--s1) - *(--s2);
    return *s1 - *s2;
}

int Right_Str_Comparator(LINE s1_, LINE s2_)
{
    char *s1 = (char *) s1_.ptr_to_line;
    char *s2 = (char *) s2_.ptr_to_line;

    int first = s1_.len_of_line;
    int second = s2_.len_of_line;


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

int Multy_Compare(LINE s1, LINE s2, int mode, int reverse)
{

    if (mode == LEFT_COMPLANATION_CONST)
    {
        return (reverse * Left_Str_Comparator(s1, s2) > 0)? 1 : 0;
    }
    if (mode == RIGHT_COMPLANATION_CONST)
    {
        return (reverse * Right_Str_Comparator(s1,s2) > 0)? 1 : 0;
    }
    printf("Unpredictable situation:\nmode = %d, expected mode = %d or mode = %d.\n", mode, LEFT_COMPLANATION_CONST, RIGHT_COMPLANATION_CONST);
    return 0;
}


void Sort_Lines(TEXT_OBJECT *file_constructor_ptr, int reverse, int mode)
{
    size_t number_of_lines = *file_constructor_ptr->number_of_lines;
    for (int i = 0; i < number_of_lines; i++)
    {
        for (int j = 1; j < number_of_lines; j++)
        {

            if (Multy_Compare(file_constructor_ptr->lines_ptrs[j - 1], file_constructor_ptr->lines_ptrs[j], mode, reverse))
            {
                LINE tmp = file_constructor_ptr->lines_ptrs[j-1];
                file_constructor_ptr->lines_ptrs[j - 1] = file_constructor_ptr->lines_ptrs[j];
                file_constructor_ptr->lines_ptrs[j] = tmp;
            }
        }
    }
}



