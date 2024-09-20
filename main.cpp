#include "constants.h"
#include "read.h"
#include "sort.h"
#include "write.h"


#include <stdio.h>




int main(int argc, char** argv)
{
    int reverse = TRUE_FLAG_CONST; 
    int mode = RIGHT_COMPLANATION_CONST;

    const char* input_file_name = "onegin_test.txt";
    const char* output_file_name = "onegin_output.txt";
    
    TEXT_OBJECT onegin = {input_file_name};
     

    Read_Text_From_File(&onegin);
    Sort_Lines(&onegin, reverse, mode);
    Print_Lines_To_File(onegin, output_file_name );

    return 0;
    
}

