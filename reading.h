#ifndef READING_H
#define READING_H
#include <stdio.h>
#include <assert.h>
#include "constants.h"

void Read_Text_From_File(TEXT_OBJECT *file_constructor_ptr);
void Creat_Jagged_Array_Lines(TEXT_OBJECT *file_constructor_ptr);
void Recycle_Buffer(TEXT_OBJECT *file_constructor_ptr);
void Fill_Buffer(TEXT_OBJECT *file_constructor_ptr);

#endif