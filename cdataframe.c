#include "cdataframe.h"

// Fonction pour créer un nouveau dataframe
CDataframe* create_dataframe(){
    CDataframe* new_dataframe = malloc(sizeof(CDataframe));
    new_dataframe->columns = NULL;
    new_dataframe->numb_columns=0;
    return new_dataframe;
}

// Fonction pour remplir un dataframe avec les entrées de l'utilisateur
void fill_dataframe(CDataframe* df) {
    printf("Entrez le nombre de colonnes: ");
    scanf("%d", &(df->numb_columns));
    df->columns = malloc(df->numb_columns * sizeof(COLUMN*));

    for(int i = 0; i < df->numb_columns; i++) {
        printf("Entrez le titre pour la colonne %d: ", i+1);
        char* title = malloc(256 * sizeof(char));
        ENUM_TYPE type;
        scanf("%s", title);
        printf("Entrez le type pour la colonne %d: ", i+1);
        scanf("%d", &type);

        df->columns[i] = create_column(type, title);

        printf("Entrez le nombre de valeurs pour la colonne %d: ", i+1);
        int num_values;
        scanf("%d", &num_values);
        free(title);

        for(int j = 0; j < num_values; j++) {
            printf("Entrez la valeur %d pour la colonne %d: ", j+1, i+1);
            int value;
            scanf("%d", &value);

            insert_values(df->columns[i], &value);
        }
    }
}

// Fonction pour afficher un dataframe
void print_dataframe(CDataframe* df) {
    if(df->numb_columns == 0) {
        printf("Dataframe vide\n");
        return;
    }
    for(int i = 0; i < df->numb_columns; i++) {
        printf("Colonne %d: ", i+1);
        print_col(df->columns[i]);
    }
}

// Fonction pour afficher une ligne spécifique d'un dataframe
void print_dataframe_ligne(CDataframe* df, int ligne) {
    for(int i = 0; i < df->numb_columns; i++) {
        printf("Colonne %d: ", i+1);
        for(int j = 0; j < ligne && j < df->columns[i]->TL; j++) {
            printf("[%d] %d\n", j, df->columns[i]->data[j]);
        }
    }
}

// Fonction pour afficher une colonne spécifique d'un dataframe
void print_dataframe_column(CDataframe* df, int column) {
    print_col(df->columns[column]);
}

// Fonction pour ajouter une ligne à un dataframe
void add_row_dataframe(CDataframe* df, int* row_values) {
    for(int i = 0; i < df->numb_columns; i++) {
        insert_values(df->columns[i],  &row_values[i]);
    }
}

// Fonction pour supprimer une ligne d'un dataframe
void delete_row_dataframe(CDataframe* df, int row_index) {
    for(int i = 0; i < df->numb_columns; i++) {
        if(row_index < df->columns[i]->TL) {
            for(int j = row_index; j < df->columns[i]->TL - 1; j++) {
                df->columns[i]->data[j] = df->columns[i]->data[j + 1];
            }
            df->columns[i]->TL--;
        }
    }
}

// Fonction pour ajouter une colonne à un dataframe
void add_column_dataframe(CDataframe* df,ENUM_TYPE type, char* title) {
    df->numb_columns++;
    df->columns = realloc(df->columns, df->numb_columns * sizeof(COLUMN*));
    df->columns[df->numb_columns-1] = create_column(type, title);
}

// Fonction pour supprimer une colonne d'un dataframe
void delete_column_dataframe(CDataframe* df, int column_index) {
    if(column_index < df->numb_columns) {
        delete_column(df->columns[column_index]);
        for(int i = column_index; i < df->numb_columns - 1; i++) {
            df->columns[i] = df->columns[i + 1];
        }
        df->numb_columns--;
    }
}

// Fonction pour renommer une colonne dans un dataframe
void rename_column_dataframe(CDataframe* df, int column_index, char* new_title) {
    if(column_index < df->numb_columns) {
        df->columns[column_index]->title = new_title;
    }
}

// Fonction pour vérifier si une valeur existe dans un dataframe
int value_exists_in_dataframe(CDataframe* df, void* value) {
    for(int i = 0; i < df->numb_columns; i++) {
        if (valInCol(df->columns[i], value) != -1) {
            return 1;
        }
    }
    return 0;
}

// Fonction pour obtenir une valeur d'un dataframe en fonction de son adresse
void* get_value_from_dataframe(CDataframe* df, int row, int col) {
    if(col < df->numb_columns && row < df->columns[col]->TL) {
        return (void*) df->columns[col]->data[row];
    }
    return (void*)-1;
}

// Fonction pour définir une valeur dans un dataframe
void set_value_in_dataframe(CDataframe* df, int row, int col, void* new_value) {
    if(col < df->numb_columns && row < df->columns[col]->TL) {
        switch(df->columns[col]->column_type) {
            case NULLVAL:
                break;
            case UINT:
                df->columns[col]->data[row]->uint_value = *((unsigned int*)new_value);
                break;
            case INT:
                print_col(df->columns[col]);
                char str[10];
                convertCol(df->columns[col],row,str,df->columns[col]->TL);
                printf("%s",str );
                df->columns[col]->data[row] = new_value;
                char str1[10];
                sprintf(str1,"%d",*((int*)new_value));
                printf("%s",str1 );

                break;
            case CHAR:
                df->columns[col]->data[row]->char_value = *((char*)new_value);
                break;
            case FLOAT:
                df->columns[col]->data[row]->float_value = *((float*)new_value);
                break;
            case DOUBLE:
                df->columns[col]->data[row]->double_value = *((double*)new_value);
                break;
            case STRING:
                df->columns[col]->data[row]->string_value = (char*)new_value;

                break;
            case STRUCTURE:
                df->columns[col]->data[row]->struct_value = new_value;
                break;
        }
    }
}

// Fonction pour obtenir le nombre de lignes dans un dataframe
int get_number_rows(CDataframe* df) {
    int max_rows = 0;
    for(int i = 0; i < df->numb_columns; i++) {
        if(df->columns[i]->TL > max_rows) {
            max_rows = df->columns[i]->TL;
        }
    }
    return max_rows;
}

// Fonction pour obtenir le nombre de colonnes dans un dataframe
int get_number_columns(CDataframe* df) {
    return df->numb_columns;
}

// Fonction pour compter le nombre de cellules dans un dataframe qui sont égales à une valeur
int count_cells_equal(CDataframe* df, void* x) {
    int count = 0;
    for(int i = 0; i < df->numb_columns; i++) {
        count+=nbVal(df->columns[i],x);
    }
    return count;
}

// Fonction pour compter le nombre de cellules dans un dataframe qui sont supérieures à une valeur
int count_cells_greater(CDataframe* df, void* x) {
    int count = 0;
    for(int i = 0; i < df->numb_columns; i++) {
        count+=nbSupVal(df->columns[i],x);
    }
    return count;
}

// Fonction pour compter le nombre de cellules dans un dataframe qui sont inférieures à une valeur
int count_cells_less(CDataframe* df, void* x) {
    int count = 0;
    for(int i = 0; i < df->numb_columns; i++) {
        count+=nbInfVal(df->columns[i],x);
    }
    return count;
}
void test_dataframe(){

}