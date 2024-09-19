#ifndef SORTING_H
#define SORTING_H
#include "constants.h"



void Quick_Sort(TEXT_OBJECT *file_constructor_ptr);

int Left_Str_Comparator(LINE s1_, LINE s2_);
int Right_Str_Comparator(LINE s1_, LINE s2_);
int Multy_Compare(LINE s1, LINE s2, int mode, int flag);
void Sort_Lines(TEXT_OBJECT *file_constructor_ptr, int reverse, int mode);

#endif