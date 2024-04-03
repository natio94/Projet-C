//
// Created by Wagner on 29/03/2024.
//

#include "structure.h"



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
        if (col->data==NULL){
            return 0;
        }
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
}//
// Created by Wagner on 29/03/2024.
//
