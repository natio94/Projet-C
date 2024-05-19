// Creator: Natio & Wek
#include <string.h>
#include "column.h"
#define REALOC_SIZE 256
// Crée une nouvelle colonne
COLUMN *create_column(ENUM_TYPE type, char* title) {
    COLUMN *new_column = malloc(sizeof(COLUMN));
    new_column->title = title;
    new_column->data = NULL;
    new_column->TL=0;
    new_column->TP=0;
    new_column->column_type = type;
    new_column->index = NULL;
    return new_column;
}

void swap(unsigned long long int* a, unsigned long long int* b) {
    unsigned long long int t = *a;
    *a = *b;
    *b = t;
}

int partition(COLUMN* col, int low, int high) {
    unsigned long long int* index = col->index;
    void* pivot = col->data[index[high]];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        switch (col->column_type) {
            case UINT:
                if (*(unsigned int*)col->data[index[j]] < *(unsigned int*)pivot) {
                    i++;
                    swap(&index[i], &index[j]);
                }
                break;
            case INT:
                if (*(int*)col->data[index[j]] < *(int*)pivot) {
                    i++;
                    swap(&index[i], &index[j]);
                }
                break;
            case CHAR:
                if (*(char*)col->data[index[j]] < *(char*)pivot) {
                    i++;
                    swap(&index[i], &index[j]);
                }
                break;
            case FLOAT:
                if (*(float*)col->data[index[j]] < *(float*)pivot) {
                    i++;
                    swap(&index[i], &index[j]);
                }
                break;
            case DOUBLE:
                if (*(double*)col->data[index[j]] < *(double*)pivot) {
                    i++;
                    swap(&index[i], &index[j]);
                }
                break;
            case STRING:
                if ((char*)col->data[index[j]]< (char*)pivot) {
                    i++;
                    swap(&index[i], &index[j]);
                }
                break;
                // Add other cases for different column types
        }
    }
    swap(&index[i + 1], &index[high]);
    return (i + 1);
}

void quicksort(COLUMN* col, int low, int high) {
    if (low < high) {
        int pi = partition(col, low, high);
        quicksort(col, low, pi - 1);
        quicksort(col, pi + 1, high);
    }
}


void sort_col(COLUMN *col,int sort_dir){
    if (col->TL==0 || col->valid_index==1){
        return;
    }
    else if (col->valid_index==0) {
        // Initialize index array
        for(unsigned long long int i = 0; i < col->TL; i++) {
            col->index[i] = i;
        }
        quicksort(col, 0, col->TL-1);
    }
    else if (col->valid_index==-1){
        quicksort(col, 0, col->TL-1);
    }
}

// Insère des valeurs dans une colonne
int insert_values(COLUMN* col, void* value){
    if (value==NULL){
        if (col->data==NULL){
            col->data= malloc(REALOC_SIZE*sizeof(NULL));
            col->TP=REALOC_SIZE;
        }
        else if (col->TL+1>col->TP){
            col->data = realloc(col->data,col->TP+REALOC_SIZE*sizeof(unsigned int));
            if (col->data==NULL){
                return 0;
            }
            col->TP+=REALOC_SIZE;
        }
    }
    else {
        switch (col->column_type) {
            case UINT:
                if (col->data == NULL) {
                    col->data = malloc(REALOC_SIZE * sizeof(unsigned int));
                    col->TP = REALOC_SIZE;
                } else if (col->TL + 1 > col->TP) {
                    col->data = realloc(col->data, col->TP + REALOC_SIZE * sizeof(unsigned int));
                    if (col->data==NULL){
                        return 0;
                    }
                    col->TP += REALOC_SIZE;
                }
                break;
            case INT:
                if (col->data == NULL) {
                    col->data = malloc(REALOC_SIZE * sizeof(int));
                    col->TP = REALOC_SIZE;
                } else if (col->TL + 1 > col->TP) {
                    col->data = realloc(col->data, col->TP + REALOC_SIZE * sizeof(int));
                    if (col->data==NULL){
                        return 0;
                    }
                    col->TP += REALOC_SIZE;
                }
                break;
            case CHAR:
                if (col->data == NULL) {
                    col->data = malloc(REALOC_SIZE * sizeof(char));
                    col->TP = REALOC_SIZE;
                } else if (col->TL + 1 > col->TP) {
                    col->data = realloc(col->data, col->TP + REALOC_SIZE * sizeof(char));
                    if (col->data==NULL){
                        return 0;
                    }
                    col->TP += REALOC_SIZE;
                }
                break;
            case FLOAT:
                if (col->data == NULL) {
                    col->data = malloc(REALOC_SIZE * sizeof(float));
                    col->TP = REALOC_SIZE;
                } else if (col->TL + 1 > col->TP) {
                    col->data = realloc(col->data, col->TP + REALOC_SIZE * sizeof(float));
                    if (col->data==NULL){
                        return 0;
                    }
                    col->TP += REALOC_SIZE;
                }
                break;
            case DOUBLE:
                if (col->data == NULL) {
                    col->data = malloc(REALOC_SIZE * sizeof(double));
                    col->TP = REALOC_SIZE;
                } else if (col->TL + 1 > col->TP) {
                    col->data = realloc(col->data, col->TP + REALOC_SIZE * sizeof(double));
                    if (col->data==NULL){
                        return 0;
                    }
                    col->TP += REALOC_SIZE;
                }
                break;
            case STRING:
                if (col->data == NULL) {
                    col->data = malloc(REALOC_SIZE * strlen(value)*sizeof(char*)+1);
                    col->TP = REALOC_SIZE;
                } else if (col->TL + 1 > col->TP) {
                    col->data = realloc(col->data, col->TP + REALOC_SIZE * sizeof(char*));
                    if (col->data==NULL){
                        return 0;
                    }
                    col->TP += REALOC_SIZE;
                }
                break;
            case STRUCTURE:
                return 0;
                break;
            case NULLVAL:
                break;
        }
    }
    col->data[col->TL]=value;
    col->TL++;
    col->index = realloc(col->index, col->TL * sizeof(unsigned long long int));
    col->index[col->TL-1] = col->TL-1;
    if (col->data==NULL || col->data[col->TL]!=value){
        return 0;
    }
    update_index(col);
    return 1;
}
// Supprime une colonne
void delete_column(COLUMN* col){
    printf("Suppression de la colonne %s\n",col->title);
    free(col->data);
    col->data = NULL;
    col->TL=0;
    col->TP=0;
}
// Convertit une colonne en chaîne de caractères
void convertCol(COLUMN* col, unsigned long long int i, char *str,unsigned int size){
    if (col->data[i]==NULL){

        sprintf(str,"NULL");
        return;
    }
    else{
    switch (col->column_type) {
        case NULLVAL:
            sprintf(str,"NULL");
            break;
        case UINT:
            sprintf(str,"%d",*((unsigned int*)col->data[i]));
            break;
        case INT:
            sprintf(str,"%d",*((int*)col->data[i]));
            break;
        case CHAR:
            *(str)=*((char*)col->data[i]);
            break;
        case FLOAT:
            sprintf(str,"%f",*((float*)col->data[i]));
            break;
        case DOUBLE:
            sprintf(str,"%lf",*((double*)col->data[i]));
            break;
        case STRING:
            sprintf(str,"%s",(char*)col->data[i]);
            break;
        case STRUCTURE:
            break;

    }
    if(*(str)=='\0'){
        sprintf(str,"NULL");
    }
    }
}
// Affiche une colonne
void print_col(COLUMN* col){
    if (col->data==NULL || col->TL==0){
        printf("La colonne est vide\n");
        return;
    }
    printf("Colonne %s\n",col->title);
    for(int i=0;i<col->TL-1;i++){
        char str[10];
        convertCol(col,i,str,col->TL);
        printf("[%d] : %s,",i, str);
    }
    char str[10];
    convertCol(col,col->TL-1,str,col->TL);
    printf("[%d] : %s\n",col->TL-1,str );
}
void print_col_by_index(COLUMN* col){
    if (col->data==NULL || col->TL==0){
        printf("La colonne est vide\n");
        return;
    }
    printf("Colonne %s\n",col->title);
    for(int i=0;i<col->TL-1;i++){
        char str[10];
        convertCol(col,col->index[i],str,col->TL);
        printf("[%d] : %s,",i, str);
    }
    char str[10];
    convertCol(col,col->index[col->TL-1],str,col->TL);
    printf("[%d] : %s\n",col->TL-1,str );
}
// Compte le nombre de fois qu'une valeur apparaît dans une colonne
int nbVal(COLUMN *col, void* x) {
    int nb=0;
    for(int i=0;i<col->TL;i++){
        switch (col->column_type) {
            case UINT:
                if (*(unsigned int*)(col->data[i]) == *(unsigned int*)x){
                    nb++;
                }
                break;
            case INT:
                if (*(int*)(col->data[i]) == *(int*)x){
                    nb++;
                }
                break;
            case CHAR:
                if (*(char*)(col->data[i]) == *(char*)x){
                    nb++;
                }
                break;
            case FLOAT:
                if (*(float*)(col->data[i]) == *(float*)x){
                    nb++;
                }
                break;
            case DOUBLE:
                if (*(double*)(col->data[i]) == *(double*)x){
                    nb++;
                }
                break;
            case STRING:
                if (*(char**)(col->data[i])==*(char**)x){
                    nb++;
                }
                break;
    }}
    return nb;
}
// Récupère une valeur à une position donnée dans une colonne
void* valPosX(COLUMN *col, int x) {
    if (x<col->TL){
        return (void*) col->data[x];
    }
    return (void*)-1;
}
// Vérifie si une valeur est présente dans une colonne
int valInCol(COLUMN *col, void* x) {
    for(int i=0;i<col->TL;i++){
        if (col->data[i]==x){
            return 1;
        }
    }
    return 0;
}
// Compte le nombre de valeurs supérieures à x dans une colonne
int nbSupVal(COLUMN *col, void* x) {
    int nb = 0;
    for(int i = 0; i < col->TL; i++){
        switch (col->column_type) {
            case UINT:
                if (*(unsigned int*)(col->data[i]) > *(unsigned int*)x){
                    nb++;
                }
                break;
            case INT:
                if (*(int*)(col->data[i]) > *(int*)x){
                    nb++;
                }
                break;
            case CHAR:
                if (*(char*)(col->data[i]) > *(char*)x){
                    nb++;
                }
                break;
            case FLOAT:
                if (*(float*)(col->data[i]) > *(float*)x){
                    nb++;
                }
                break;
            case DOUBLE:
                if (*(double*)(col->data[i]) > *(double*)x){
                    nb++;
                }
                break;
            case STRING:
                if (strcmp((char*)(col->data[i]), (char*)x) > 0){
                    nb++;
                }
                break;
                // Add other cases for different column types
        }
    }
    return nb;
}
// Compte le nombre de valeurs inférieures à x dans une colonne
int nbInfVal(COLUMN *col, void* x) {
    int nb = 0;
    for(int i = 0; i < col->TL; i++){
        switch (col->column_type) {
            case UINT:
                if (*(unsigned int*)(col->data[i]) < *(unsigned int*)x){
                    nb++;
                }
                break;
            case INT:
                if (*(int*)(col->data[i]) < *(int*)x){
                    nb++;
                }
                break;
            case CHAR:
                if (*(char*)(col->data[i]) < *(char*)x){
                    nb++;
                }
                break;
            case FLOAT:
                if (*(float*)(col->data[i]) < *(float*)x){
                    nb++;
                }
                break;
            case DOUBLE:
                if (*(double*)(col->data[i]) < *(double*)x){
                    nb++;
                }
                break;
            case STRING:
                if (strcmp((char*)(col->data[i]), (char*)x) < 0){
                    nb++;
                }
                break;
                // Add other cases for different column types
        }
    }
    return nb;
}

void erase_index(COLUMN* col){
    free(col->index);
    col->index=NULL;
    col->valid_index=0;
}

int check_index(COLUMN* col){
    if (col->index==NULL){
        return 0;
    }
    else if (col->valid_index==1){
        return 1;
    }
    else if (col->valid_index==-1){
        return -1;
    }
    return 0;
}

void update_index(COLUMN* col){
    sort_col(col,col->sort_dir);
}
