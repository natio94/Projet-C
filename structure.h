
#ifndef PROJET_C_STRUCTURE_H
#define PROJET_C_STRUCTURE_H
#include <stdio.h>
#include <stdlib.h>
typedef struct  {
    char* title;
    int* data;
    int TP;
    int TL;
}COLUMN;
COLUMN *create_column(char* title);
int insert_values(COLUMN* col, int value);
void delete_column(COLUMN* col);
void print_col(COLUMN* col);
#endif //PROJET_C_STRUCTURE_H
