// Creator: Natio & Wek

#include "column.h"
#include "cdataframe.h"
void handleSegFaultError(int sig) {
    printf("Une erreur de type Segmentation Fault a ete detectee probablement cree par une erreur de type lors de l'insertion des valeurs"
           ", le programme va s'arreter.\nVeuillez corriger l'erreur et relancer le programme.\n");
    exit(1);
}
int main(){
    printf("Voulez-vous tester : \n1. Les colonnes\n2. Les dataframes\n");
    int choice;
    scanf("%d",&choice);
    switch (choice){
        case 1:
            test_column();
            break;
        case 2:
            test_dataframe();
            break;
        default:
            printf("Choix invalide\n");
            break;
    }
    signal(SIGSEGV, handleSegFaultError);
/*
    COLUMN test=*create_column(STRING,"test");
    char *a="es";
    char *b="ezf";
    char *c="3";
    printf("%d\n",insert_values(&test,(void*)"es"));
    printf("%d\n",insert_values(&test, (void *) "efz"));
    printf("%d\n",insert_values(&test, (void *) "10"));
    insert_values(&test, (void *) "20");
    print_col(&test);
    printf("Taille de la colonne : %d\n",test.TL);
    delete_column(&test);
    print_col(&test);*//*
    COLUMN *col = create_column(INT, "Test Column");
    int value = 5;
    int non_existing_value = 6;
    int value1 = 5;
    int value2 = 6;
    int value3 = 7;

    printf(insert_values(col, &value) ? "Insertion successful\n" : "Insertion failed\n");
    print_col(col);
    printf("nbVal with existing value: %d\n", nbVal(col, &value));

    printf("nbVal with non-existing value: %d\n", nbVal(col, &non_existing_value));

    printf("valInCol with existing value: %d\n", valInCol(col, &value));

    printf("valInCol with non-existing value: %d\n", valInCol(col, &non_existing_value));

    printf("valPosX with valid position: %d\n", *(int*)valPosX(col, 0));

    printf("valPosX with invalid position: %p\n", valPosX(col, 1));

    insert_values(col, &value2);
    //printf("nbSupVal with values: %d\n", nbSupVal(col, value1));

    //printf("nbInfVal with values: %d\n", nbInfVal(col, value2));

    insert_values(col, &value1);

    print_col(col);
    delete_column(col);
    print_col(col);
/*
        // Create a column of type STRING
    COLUMN *col2 = create_column(STRING, "Test 2");
    printf("Created column: %s\n", col2->title);

// Insert a string value
    void *value12 = "test";
    printf("%d",insert_values(col2, value12));
    print_col(col2);
    printf("Inserted value: %s\n", value12);

// Check the number of occurrences of the value
    printf("Number of occurrences of %s: %d\n", value12, nbVal(col2, &value12));

// Check if the value is in the column
    printf("Is %s in the column? %d\n", value12, valInCol(col2, &value12));

// Get the value at a position
    printf("Value at position 0: %s\n", (char *)valPosX(col2, 0));

// Delete the column
    delete_column(col2);
    printf("Column deleted\n");


*//*
        // Create a dataframe
        CDataframe* df = create_dataframe();
    printf("Created dataframe\n");
        // Add a column
        char* title = "Test Column";
        add_column_dataframe(df, INT,title);

        // Print number of columns
        printf("Number of columns: %d\n", get_number_columns(df));

        // Add a row
        int row_values[] = {5};
        add_row_dataframe(df, row_values);
        print_col(df->columns[0]);
        // Print number of rows
        char str[10];
        convertCol(df->columns[0],0,str,df->columns[0]->TL);
        printf("%s",str );
        printf("Number of rows: %d\n", get_number_rows(df));

        printf("Value at (0,0): %d\n", *(int*)get_value_from_dataframe(df, 0, 0));
    int values = 10;
        set_value_in_dataframe(df, 0, 0, &values);
    int values1 = 5;
    int values2 = 15;
    printf("New value at (0,0): %d\n", *(int *) get_value_from_dataframe(df, 0, 0));
    int row_valuess[] = {10};
    int row_values2[] = {16};
    int row_values3[] = {3};
    // Check if value exists
    printf("Does 10 exist in dataframe: %d\n", value_exists_in_dataframe(df, &values));
    add_row_dataframe(df, row_valuess);
    add_row_dataframe(df, row_values2);
    add_row_dataframe(df, row_values3);
    print_col(df->columns[0]);
    printf("%d", nbVal(df->columns[0], &values));
    // Count cells equal to, greater than, and less than a value
    printf("Number of cells equal to 10: %d\n", count_cells_equal(df, &values));
    printf("Number of cells greater than 5: %d\n", count_cells_greater(df, &values1));
    printf("Number of cells less than 15: %d\n", count_cells_less(df, &values2));
    df->columns[0]->valid_index=0;
    sort_col(df->columns[0],ASC);
    print_col(df->columns[0]);
    print_col_by_index(df->columns[0]);
    for(int i=0;i<df->columns[0]->TL;i++){
        printf("%llu\n",df->columns[0]->index[i]);
    }
    printf("afeizfj%defezg\n", search_value_in_column(df->columns[0],&values2));
    // Delete a row
    delete_row_dataframe(df, 0);
    printf("Number of rows after deletion: %d\n", get_number_rows(df));

    // Delete a column
    delete_column_dataframe(df, 0);
    printf("Number of columns after deletion: %d\n", get_number_columns(df));
    print_dataframe(df);
    printf("All operations completed!\n");
*/
        return 0;
    }

