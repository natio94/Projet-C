// Creator: Natio & Wek
#ifndef PROJET_C_COLUMN_H
#define PROJET_C_COLUMN_H
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
///l
typedef enum
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
}ENUM_TYPE;

typedef union {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
}COL_TYPE;

typedef struct  {
    char* title;
    unsigned int TP;
    unsigned int TL;
    ENUM_TYPE column_type;
    COL_TYPE **data;
    unsigned long long int *index;
}COLUMN;

COLUMN *create_column(ENUM_TYPE type, char* title);
int insert_values(COLUMN* col, void* value);
void delete_column(COLUMN* col);
void print_col(COLUMN* col);
int nbVal(COLUMN* col, int x);
int valInCol(COLUMN *col, int x);
int valPosX(COLUMN *col, int x);
int nbSupVal(COLUMN *col, int x);

int nbInfVal(COLUMN *col, int x);

int nbEqualVal(COLUMN *col, int x);
#endif //PROJET_C_COLUMN_H
