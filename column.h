// Creator: Natio & Wek
#ifndef PROJET_C_COLUMN_H
#define PROJET_C_COLUMN_H
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
int nbVal(COLUMN* col, int x);
int valInCol(COLUMN *col, int x);
int valPosX(COLUMN *col, int x);
int nbSupVal(COLUMN *col, int x);

int nbInfVal(COLUMN *col, int x);

int nbEqualVal(COLUMN *col, int x);
#endif //PROJET_C_COLUMN_H
