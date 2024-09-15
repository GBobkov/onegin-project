#ifndef SORTING_H
#define SORTING_H
#include "constants.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>




int Left_Str_Comparator(char* s1, char* s2);
int Right_Str_Comparator(char* s1, char* s2);
int Multy_Compare(char* s1, char* s2, int mode);
void Sort_Lines(TEXT_OBJECT *file_constructor_ptr, int reverse, int mode);

#endif