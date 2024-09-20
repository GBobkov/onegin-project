#include "sort.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>






static int Left_Str_Comparator(LINE s1_, LINE s2_);
static int Right_Str_Comparator(LINE s1_, LINE s2_);
static int Comparator(LINE s1, LINE s2, int mode, int flag);


int dbgi = 0, dbgj = 0;

void Sort_Lines(TEXT_OBJECT *file_constructor_ptr, int reverse, int mode)
{
    size_t number_of_lines = file_constructor_ptr->num_lines;
    for (size_t i = 0; i < number_of_lines; i++)
    {

        dbgi = i;

        for (size_t j = 1; j < number_of_lines; j++)
        {
            dbgj = j;
            if (Comparator(file_constructor_ptr->lines_ptrs[j - 1], file_constructor_ptr->lines_ptrs[j], mode, reverse))
            {
                LINE tmp = file_constructor_ptr->lines_ptrs[j-1];
                file_constructor_ptr->lines_ptrs[j - 1] = file_constructor_ptr->lines_ptrs[j];
                file_constructor_ptr->lines_ptrs[j] = tmp;
            }
        }
    }

}

static int Comparator(LINE s1, LINE s2, int mode, int reverse)
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



static int Left_Str_Comparator(LINE s1_, LINE s2_)
{   
    char *s1 = s1_.line_ptr;
    char *s2 = s2_.line_ptr;
    
    while (*s1 != '\r' && *s2 != '\r')
        if (*s1++ != *s2++) return *(--s1) - *(--s2);
    return *s1 - *s2;
}

static int Right_Str_Comparator(LINE s1_, LINE s2_)
{
    char *s1 = s1_.line_ptr;
    char *s2 = s2_.line_ptr;

    int first = s1_.line_len - 1;
    int second = s2_.line_len - 1;

    // if (dbgi == 144 && dbgj == 1)
    //     {
    //         printf("first=%d. s1[first]=%d\n", first, s1[first]);
    //         printf("second=%d. s2[first]=%d\n", second, s2[second]);
    //         printf("s1=%.41s\ns2=%.41s\n", s2,s2);
    //     }
    while (first >= 0 && second >= 0)
    {
        
        while (!isalpha(s1[first]) && first > 0)  first--;
        while (!isalpha(s2[second]) && second > 0) second--;
        // if (dbgi == 144 && dbgj == 1)
        // {
        //     printf("first=%d. s1[first]=%d\n", first, s1[first]);
        //     printf("second=%d. s2[first]=%d\n", second, s2[second]);
        //     printf("tolower(s1[first--])=%c, tolower(s2[second--])=%c\n\n\n",tolower(s1[first--]), tolower(s2[second--]));
        // }
        //printf("word1: %s\nword2: %s\nfirst=%d\nsecond=%d\n%c != %c\n\n",s1,s2,first,second,(s1[first--]), tolower(s2[second--]), tolower(s1[first--]) != tolower(s2[second--]));
        if (tolower(s1[first--]) != tolower(s2[second--]))
            return s1[++first] - s2[++second];
    }
    
    if (first == second) return 0;
    if (first < 0) return -1;
    return 1;
}




