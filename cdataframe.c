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
    if(df->numb_columns == 0) {
        printf("Impossible d'ajouter une ligne à un dataframe sans colonne\n");
        return;
    }
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
    else {
        printf("Colonne et/ou ligne incorrecte/s\n");
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
    printf("Création d'un nouveau dataframe.\n");
    CDataframe* df = create_dataframe();
    while(1) {
        printf("Choisissez une option:\n 1: Ajouter une ligne\n 2: Supprimer une ligne\n 3: Ajouter une colonne\n 4: Supprimer une colonne\n 5: Renommer une colonne\n 6: Afficher le dataframe\n 7: Modifier une valeur\n 8: Actions de verification des valeurs\n 9: Quitter\n");
        int option;
        scanf("%d", &option);
        switch(option) {
            case 1: {
                if(df->numb_columns == 0) {
                    printf("Impossible d'ajouter une ligne à un dataframe sans colonne\n");
                    break;
                }
                printf("Entrez le nombre de valeurs dans la ligne:\n");
                int num_values;
                scanf("%d", &num_values);
                int* row_values = malloc(num_values * sizeof(int));
                for(int i = 0; i < num_values; i++) {
                    printf("Entrez la valeur %d:\n", i+1);
                    scanf("%d", &row_values[i]);
                }
                add_row_dataframe(df, row_values);
                free(row_values);
                break;
            }
            case 2: {
                if(get_number_rows(df) == 0) {
                    printf("Impossible de supprimer une ligne dans un dataframe qui n'en as pas\n");
                    break;
                }
                printf("Entrez l'indice de la ligne à supprimer:\n");
                int row_index;
                scanf("%d", &row_index);
                delete_row_dataframe(df, row_index);
                break;
            }
            case 3: {
                printf("Entrez le type de la colonne à ajouter:\n");
                ENUM_TYPE type;
                scanf("%d", &type);
                printf("Entrez le titre de la colonne à ajouter:\n");
                char title[100];
                scanf("%s", title);
                add_column_dataframe(df, type, title);
                break;
            }
            case 4: {
                printf("Entrez l'indice de la colonne à supprimer:\n");
                int column_index;
                scanf("%d", &column_index);
                delete_column_dataframe(df, column_index);
                break;
            }
            case 5: {
                printf("Entrez l'indice de la colonne à renommer:\n");
                int column_index;
                scanf("%d", &column_index);
                printf("Entrez le nouveau titre de la colonne:\n");
                char new_title[100];
                scanf("%s", new_title);
                rename_column_dataframe(df, column_index, new_title);
                break;
            }
            case 6: {
                printf("Affichage du dataframe:\n");
                print_dataframe(df);
                break;
            }

            case 7: {
                printf("Quelle est la position de la donnée à modifier?\n");
                int row, col;
                scanf("%d %d", &row, &col);
                printf("Entrez la nouvelle valeur:\n");
                switch (df->columns[col]->column_type) {
                    case UINT: {
                        unsigned int new_value;
                        scanf("%u", &new_value);
                        set_value_in_dataframe(df, row, col, &new_value);
                        break;
                    }
                    case INT: {
                        int new_value;
                        scanf("%d", &new_value);
                        set_value_in_dataframe(df, row, col, &new_value);
                        break;
                    }
                    case CHAR: {
                        char new_value;
                        scanf("%c", &new_value);
                        set_value_in_dataframe(df, row, col, &new_value);
                        break;
                    }
                    case FLOAT: {
                        float new_value;
                        scanf("%f", &new_value);
                        set_value_in_dataframe(df, row, col, &new_value);
                        break;
                    }
                    case DOUBLE: {
                        double new_value;
                        scanf("%lf", &new_value);
                        set_value_in_dataframe(df, row, col, &new_value);
                        break;
                    }
                    case STRING: {
                        char new_value[100];
                        scanf("%s", new_value);
                        set_value_in_dataframe(df, row, col, new_value);
                        break;
                    }
                    case STRUCTURE: {
                        printf("Impossible de modifier une colonne de type STRUCTURE\n");
                        break;
                    }

                }
            }
            case 8:{
                printf("Choisissez une option:\n 1: Compter le nombre de cellules égales à une valeur\n 2: Compter le nombre de cellules supérieures à une valeur\n 3: Compter le nombre de cellules inférieures à une valeur\n 4: Quitter\n");
                int option;
                scanf("%d", &option);
                switch(option) {
                    case 1: {
                        printf("Entrez la valeur à rechercher:\n");
                        int value;
                        scanf("%d", &value);
                        printf("Nombre de cellules égales à %d: %d\n", value, count_cells_equal(df, &value));
                        break;
                    }
                    case 2: {
                        printf("Entrez la valeur à comparer:\n");
                        int value;
                        scanf("%d", &value);
                        printf("Nombre de cellules supérieures à %d: %d\n", value, count_cells_greater(df, &value));
                        break;
                    }
                    case 3: {
                        printf("Entrez la valeur à comparer:\n");
                        int value;
                        scanf("%d", &value);
                        printf("Nombre de cellules inférieures à %d: %d\n", value, count_cells_less(df, &value));
                        break;
                    }
                    case 4:{
                        printf("Retour au menu des dataframes\n");
                        break;
                    }
                    default: {
                        printf("Option non reconnue. Veuillez réessayer.\n");
                        break;
                    }
                }
            }

            case 9: {
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