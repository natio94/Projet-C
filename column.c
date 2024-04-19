// Creator: Natio & Wek
#include "column.h"
#define REALOC_SIZE 256

COLUMN *create_column(char* title) {
    COLUMN *new_column = malloc(sizeof(COLUMN));
    new_column->title = title;
    new_column->data = NULL;
    new_column->TL=0;
    new_column->TP=0;
    return new_column;
}

int insert_values(COLUMN* col, int value){
    if (col->data==NULL){
        col->data= malloc(REALOC_SIZE*sizeof(int));
        col->TP=REALOC_SIZE;
        if (col->data==NULL){
            return 0;
        }
    }
    else if (col->TL+1>col->TP){
        realloc(col->data,col->TP+REALOC_SIZE*sizeof(int));
        col->TP+=REALOC_SIZE;
    }
    col->data[col->TL]=value;
    col->TL++;
    return 1;
}
void delete_column(COLUMN* col){
    free(col->data);
    col->data = NULL;
    col->TL=0;
    col->TP=0;
}
void print_col(COLUMN* col){
    if (col->data==NULL){
        printf("Column is empty\n");
        return;
    }
    for(int i=0;i<col->TL;i++){
        printf("[%d] %d\n",i,col->data[i]);
    }
}

int nbVal(COLUMN *col, int x) {
    int nb=0;
    for(int i=0;i<col->TL;i++){
        if (col->data[i]==x){
            nb++;
        }
    }
    return nb;
}

int valPosX(COLUMN *col, int x) {
    if (x<col->TL){
        return col->data[x];
    }
    return -1;
}

int valInCol(COLUMN *col, int x);

int valInCol(COLUMN *col, int x) {
    for(int i=0;i<col->TL;i++){
        if (col->data[i]==x){
            return 1;
        }
    }
    return 0;
}

int nbSupVal(COLUMN *col, int x) {
    int nb=0;
    for(int i=0;i<col->TL;i++){
        if (col->data[i]>x){
            nb++;
        }
    }
    return nb;
}

int nbInfVal(COLUMN *col, int x) {
    int nb=0;
    for(int i=0;i<col->TL;i++){
        if (col->data[i]<x){
            nb++;
        }
    }
    return nb;
}

int nbEqualVal(COLUMN *col, int x) {
    int nb=0;
    for(int i=0;i<col->TL;i++){
        if (col->data[i]==x){
            nb++;
        }
    }
    return nb;
}


