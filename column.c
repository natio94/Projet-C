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
    new_column->valid_index=0;
    return new_column;
}

void swap(unsigned long long int* a, unsigned long long int* b) {
    unsigned long long int t = *a;
    *a = *b;
    *b = t;
}

int partition(COLUMN* col, int low, int high) {
    unsigned long long int* index = col->index;
    void* pivot = col->data[index[high]]; // Use the data at the index position for the pivot
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
                if (strcmp((char*)col->data[index[j]], (char*)pivot) < 0) {
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

void insertion_sort(COLUMN* col,int sort_dir){
    if(sort_dir==ASC) {
        for (int i = 1; i < col->TL; i++) {
            unsigned long long int key = col->index[i];
            int j = i - 1;
            while (j >= 0 && col->data[col->index[j]] > col->data[key]) {
                col->index[j + 1] = col->index[j];
                j = j - 1;
            }
            col->index[j + 1] = key;
        }
    }
    else{
        for (int i = 1; i < col->TL; i++) {
            unsigned long long int key = col->index[i];
            int j = i - 1;
            while (j >= 0 && col->data[col->index[j]] < col->data[key]) {
                col->index[j + 1] = col->index[j];
                j = j - 1;
            }
            col->index[j + 1] = key;
        }
    }
}

int partition_desc(COLUMN* col, int low, int high) {
    unsigned long long int* index = col->index;
    void* pivot = col->data[index[high]];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        switch (col->column_type) {
            case UINT:
                if (*(unsigned int*)col->data[index[j]] > *(unsigned int*)pivot) {
                    i++;
                    swap(&index[i], &index[j]);
                }
                break;
            case INT:
                if (*(int*)col->data[index[j]] > *(int*)pivot) {
                    i++;
                    swap(&index[i], &index[j]);
                }
                break;
            case CHAR:
                if (*(char*)col->data[index[j]] > *(char*)pivot) {
                    i++;
                    swap(&index[i], &index[j]);
                }
                break;
            case FLOAT:
                if (*(float*)col->data[index[j]] > *(float*)pivot) {
                    i++;
                    swap(&index[i], &index[j]);
                }
                break;
            case DOUBLE:
                if (*(double*)col->data[index[j]] > *(double*)pivot) {
                    i++;
                    swap(&index[i], &index[j]);
                }
                break;
            case STRING:
                if(strcmp((char*)col->data[index[j]], (char*)pivot) > 0) {
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

void quicksort_desc(COLUMN* col, int low, int high) {
    if (low < high) {
        int pi = partition_desc(col, low, high);
        quicksort_desc(col, low, pi - 1);
        quicksort_desc(col, pi + 1, high);
    }
}
void sort_col(COLUMN *col,int sort_dir) {
    if (col->sort_dir!=sort_dir){
        col->valid_index=0;
    }
    else if (col->TL == 0 || col->valid_index == 1) {
        printf("Sort function exited early: TL=%d, valid_index=%d\n", col->TL, col->valid_index);
        return;
    }
    if (sort_dir == ASC) {
         if (col->valid_index == 0) {
            // Initialize index array
            for (unsigned long long int i = 0; i < col->TL; i++) {
                col->index[i] = i;
            }

            quicksort(col, 0, col->TL - 1);
        } else if (col->valid_index == -1) {
            quicksort(col, 0, col->TL - 1);
        }
    } else {
        if (col->valid_index == 0) {
            // Initialize index array
            for (unsigned long long int i = 0; i < col->TL; i++) {
                col->index[i] = i;
            }

            quicksort_desc(col, 0, col->TL - 1);
        }
        quicksort_desc(col, 0, col->TL - 1);
    }
    col->valid_index = 1;
    col->sort_dir = sort_dir;
}
// Insère des valeurs dans une colonne
int insert_values(COLUMN* col, void* value){
    void* newValue;
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
                newValue = malloc(sizeof(unsigned int));
                *(unsigned int*)newValue = *(unsigned int*)value;
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

                }
                newValue = malloc(sizeof(int));
                *((int*)newValue) = *((int*)value);
                col->TP += REALOC_SIZE;
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
                newValue = malloc(sizeof(char));
                *(char*)newValue = *(char*)value;
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
                newValue = malloc(sizeof(float));
                *(float*)newValue = *(float*)value;
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
                newValue = malloc(sizeof(double));
                *(double*)newValue = *(double*)value;
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
                newValue = malloc(strlen(value) + 1);
                strcpy(newValue, value);
                break;
            case STRUCTURE:
                return 0;
                break;
            case NULLVAL:
                return 0;
                break;
        }
    }
    col->data[col->TL]=newValue;
    col->TL++;
    col->index = realloc(col->index, col->TL * sizeof(unsigned long long int));
    col->index[col->TL-1] = col->TL-1;
    if (col->valid_index==1){
        col->valid_index=-1;
        sort_col(col,col->sort_dir);
    }
    if (col->data==NULL || col->data[col->TL]!=value){
        return 0;
    }

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
        printf("La colonne %s est vide\n",col->title);
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
    return NULL;
}
// Vérifie si une valeur est présente dans une colonne
int valInCol(COLUMN *col, void* x) {
    for(int i=0;i<col->TL;i++){
        switch (col->column_type) {
            case UINT:
                if (*(unsigned int*)col->data[i] == *(unsigned int*)x){
                    return 1;
                }
                break;
            case INT:
                if (*(int*)col->data[i] == *(int*)x){
                    return 1;
                }
                break;
            case CHAR:
                if (*(char*)col->data[i] == *(char*)x){
                    return 1;
                }
                break;
            case FLOAT:
                if (*(float*)col->data[i] == *(float*)x){
                    return 1;
                }
                break;
            case DOUBLE:
                if (*(double*)col->data[i] == *(double*)x){
                    return 1;
                }
                break;
            case STRING:
                if (strcmp((char*)col->data[i], (char*)x) == 0){
                    return 1;
                }
                break;
                // Add other cases for different column types
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
    if (col->index!=NULL){
    free(col->index);
    col->index=NULL;
    col->valid_index=0;
}}

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

int search_value_in_column(COLUMN* col, void* value){
    if (col->data==NULL){
        return 0;
    }
    if (col->valid_index==0 || col->valid_index==-1){
        return -1;
    }
    int low = 0;
    int high = col->TL - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        switch (col->column_type) {
            case UINT:
                if (*(unsigned int*)col->data[mid] == *(unsigned int*)value){
                    return 1;
                }
                if (*(unsigned int*)col->data[mid] < *(unsigned int*)value){
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                break;
            case INT:
                if (*(int*)col->data[mid] == *(int*)value){
                    return 1;
                }
                if (*(int*)col->data[mid] < *(int*)value){
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                break;
            case CHAR:
                if (*(char*)col->data[mid] == *(char*)value){
                    return 1;
                }
                if (*(char*)col->data[mid] < *(char*)value){
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                break;
            case FLOAT:
                if (*(float*)col->data[mid] == *(float*)value){
                    return 1;
                }
                if (*(float*)col->data[mid] < *(float*)value){
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                break;
            case DOUBLE:
                if (*(double*)col->data[mid] == *(double*)value){
                    return 1;
                }
                if (*(double*)col->data[mid] < *(double*)value){
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                break;
            case STRING:
                if (strcmp((char*)col->data[mid], (char*)value) == 0){
                    return 1;
                }
                if (strcmp((char*)col->data[mid], (char*)value) < 0){
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                break;
                // Add other cases for different column types
        }
    }}
    void afficher_index(COLUMN* col){
        for (int i=0;i<col->TL;i++){
            printf("%d ",col->index[i]);
        }
        printf("\n");
    }
void test_column(){
    printf("Choisissez le type de colonne à tester\n 1: UINT\n 2: INT\n 3: CHAR\n 4: FLOAT\n 5: DOUBLE\n 6: STRING\n ");
    ENUM_TYPE type;
    scanf("%d",&type);
    printf("Vous avez choisi le type %d\n",type);
    printf("Choisissez le titre de la colonne à tester\n");
    char title[100];
    scanf("%s",title);
    COLUMN *col=create_column(type,title);
    printf("Choisissez le nombre de valeurs à insérer\n");
    int nb;
    scanf("%d",&nb);
    for (int i=0;i<nb;i++){
        printf("Choisissez la valeur à insérer\n");
        int value;
        scanf("%d",&value);
        insert_values(col,(void*)&value);
    }
    printf("Affichage de la colonne\n");
    print_col_by_index(col);

    while(1) {
        printf("Choisissez une option:\n 1: Voir le nombre de fois qu'une valeur est dans la colonne\n 2: Voir la valeur à une position\n 3: Vérifier si une valeur est dans la colonne\n 4: Voir le nombre de valeurs supérieures/inférieures à une valeur\n 5: Trier la colonne\n 6: Quitter\n");
        int option;
        scanf("%d", &option);
        switch(option) {
            case 1: {
                printf("Entrez la valeur à chercher:\n");
                int value;
                scanf("%d", &value);
                printf("La valeur %d apparaît %d fois dans la colonne.\n", value, nbVal(col, &value));
                break;
            }
            case 2: {
                printf("Entrez la position à chercher:\n");
                int pos;
                scanf("%d", &pos);
                void* value = valPosX(col, pos);
                if (value == NULL) {
                    printf("Position invalide.\n");
                } else {
                    switch (col->column_type) {
                        case UINT:
                            printf("La valeur à la position %d est %d.\n", pos, *(unsigned int*)value);
                            break;
                        case INT:
                            printf("La valeur à la position %d est %d.\n", pos, *(int*)value);
                            break;
                        case CHAR:
                            printf("La valeur à la position %d est %c.\n", pos, *(char*)value);
                            break;
                        case FLOAT:
                            printf("La valeur à la position %d est %f.\n", pos, *(float*)value);
                            break;
                        case DOUBLE:
                            printf("La valeur à la position %d est %lf.\n", pos, *(double*)value);
                            break;
                        case STRING:
                            printf("La valeur à la position %d est %s.\n", pos, (char*)value);
                            break;
                    }
                }
            }
                break;
            case 3: {
                printf("Entrez la valeur à vérifier:\n");
                int value;
                scanf("%d", &value);
                if (valInCol(col, &value)) {
                    printf("La valeur %d est dans la colonne.\n", value);
                } else {
                    printf("La valeur %d n'est pas dans la colonne.\n", value);
                }

                break;
            }
            case 4: {
                printf("Entrez la valeur de référence:\n");
                int value;
                scanf("%d", &value);
                printf("Il y a %d valeurs supérieures et %d valeurs inférieures à %d dans la colonne.\n", nbSupVal(col, &value), nbInfVal(col, &value), value);
                break;
            }
            case 5: {
                printf("Trier la colonne.\n");
                afficher_index(col);
                sort_col(col, ASC);
                print_col_by_index(col);
                break;
            }
            case 6: {
                printf("Au revoir!\n");
                return;
            }
            default: {
                printf("Option non reconnue. Veuillez réessayer.\n");
                break;
            }
        }
    }
}