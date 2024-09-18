#include <stdio.h>

int main() {
    FILE* file = fopen("onegin_output.txt", "w");
    fputs("TEST\n", file);
    fclose(file);
}