#include "cdataframe.h"
CDataframe* create_dataframe(){
    CDataframe* new_dataframe = malloc(sizeof(CDataframe));
    new_dataframe->columns = NULL;
    new_dataframe->numb_columns=0;
    return new_dataframe;
}
void fill_dataframe(CDataframe* df) {
    printf("Enter the number of columns: ");
    scanf("%d", &(df->numb_columns));
    df->columns = malloc(df->numb_columns * sizeof(COLUMN*));

    for(int i = 0; i < df->numb_columns; i++) {
        printf("Enter the title for column %d: ", i+1);
        char* title = malloc(256 * sizeof(char));
        ENUM_TYPE type;
        scanf("%s", title);
        printf("Enter the type for column %d: ", i+1);
        scanf("%d", &type);

        df->columns[i] = create_column(type, title);

        printf("Enter the number of values for column %d: ", i+1);
        int num_values;
        scanf("%d", &num_values);
        free(title);

        for(int j = 0; j < num_values; j++) {
            printf("Enter value %d for column %d: ", j+1, i+1);
            int value;
            scanf("%d", &value);

            insert_values(df->columns[i], &value);
        }
    }
}
/*
void fill_dataframe_hardcoded(CDataframe* df) {
    df->numb_columns = 2;
    df->columns = malloc(df->numb_columns * sizeof(COLUMN*));

    char* title1 = "Column1";
    ENUM_TYPE type = INT;
    df->columns[0] = create_column(type, title1);
    insert_values(df->columns[0], 10);
    insert_values(df->columns[0], 20);

    char* title2 = "Column2";
    ENUM_TYPE type;
    df->columns[1] = create_column(type,title2);
    insert_values(df->columns[1], 30);
    insert_values(df->columns[1], 40);
}
    char* title1 = "Column1";
    ENUM_TYPE type1 = INT;
    df->columns[0] = create_column(type1, title1);
    insert_values(df->columns[0], 10);
    insert_values(df->columns[0], 20);

    char* title2 = "Column2";
    ENUM_TYPE type2 = INT;
    df->columns[1] = create_column(type2, title2);
    insert_values(df->columns[1], 30);
    insert_values(df->columns[1], 40);
} */
void print_dataframe(CDataframe* df) {
    for(int i = 0; i < df->numb_columns; i++) {
        printf("Column %d: ", i+1);
        print_col(df->columns[i]);
    }
}
void print_dataframe_ligne(CDataframe* df, int ligne) {
    for(int i = 0; i < df->numb_columns; i++) {
        printf("Column %d: ", i+1);
        for(int j = 0; j < ligne && j < df->columns[i]->TL; j++) {
            printf("[%d] %d\n", j, df->columns[i]->data[j]);
        }
    }
}
void print_dataframe_column(CDataframe* df, int column) {
    for(int i = 0; i < column && i < df->numb_columns; i++) {
        printf("Column %d: ", i+1);
        print_col(df->columns[i]);
    }
}
void add_row_dataframe(CDataframe* df, int* row_values) {
    for(int i = 0; i < df->numb_columns; i++) {
        insert_values(df->columns[i],  &row_values[i]);
    }
}
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
void add_column_dataframe(CDataframe* df,ENUM_TYPE type, char* title) {
    df->numb_columns++;
    df->columns = realloc(df->columns, df->numb_columns * sizeof(COLUMN*));
    df->columns[df->numb_columns-1] = create_column(type, title);
}
void delete_column_dataframe(CDataframe* df, int column_index) {
    if(column_index < df->numb_columns) {
        delete_column(df->columns[column_index]);
        for(int i = column_index; i < df->numb_columns - 1; i++) {
            df->columns[i] = df->columns[i + 1];
        }
        df->numb_columns--;
    }
}
void rename_column_dataframe(CDataframe* df, int column_index, char* new_title) {
    if(column_index < df->numb_columns) {
        df->columns[column_index]->title = new_title;
    }
}
int value_exists_in_dataframe(CDataframe* df, int value) {
    for(int i = 0; i < df->numb_columns; i++) {
        if (valInCol(df->columns[i], value) != -1) {
            return 1;
        }
    }
    return 0;
}
int get_value_from_dataframe(CDataframe* df, int row, int col) {
    if(col < df->numb_columns && row < df->columns[col]->TL) {
        return (int) df->columns[col]->data[row];
    }
    return -10;
}

void set_value_in_dataframe(CDataframe* df, int row, int col, void* new_value) {
    if(col < df->numb_columns && row < df->columns[col]->TL) {
        switch(df->columns[col]->column_type) {
            case NULLVAL:
                break;
            case UINT:
                df->columns[col]->data[row]->uint_value = *((unsigned int*)new_value);
                break;
            case INT:
                df->columns[col]->data[row]->int_value = *((int*)new_value);
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
int get_number_rows(CDataframe* df) {
    int max_rows = 0;
    for(int i = 0; i < df->numb_columns; i++) {
        if(df->columns[i]->TL > max_rows) {
            max_rows = df->columns[i]->TL;
        }
    }
    return max_rows;
}
int get_number_columns(CDataframe* df) {
    return df->numb_columns;
}
int count_cells_equal(CDataframe* df, void* x) {
    int count = 0;
    for(int i = 0; i < df->numb_columns; i++) {
        switch(df->columns[i]->column_type) {
            case NULLVAL:
                break;
            case UINT:
                if (*((unsigned int*)df->columns[i]->data) == *((unsigned int*)x)) {
                    count++;
                }
                break;
            case INT:
                if (*((int*)df->columns[i]->data) == *((int*)x)) {
                    count++;
                }
                break;
            case CHAR:
                if (*((char*)df->columns[i]->data) == *((char*)x)) {
                    count++;
                }
                break;
            case FLOAT:
                if (*((float*)df->columns[i]->data) == *((float*)x)) {
                    count++;
                }
                break;
            case DOUBLE:
                if (*((double*)df->columns[i]->data) == *((double*)x)) {
                    count++;
                }
                break;
            case STRING:
                if (strcmp((char*)df->columns[i]->data, (char*)x) == 0) {
                    count++;
                }
                break;
            case STRUCTURE:
                break;
        }
    }
    return count;
}

int count_cells_greater(CDataframe* df, void* x) {
    int count = 0;
    for(int i = 0; i < df->numb_columns; i++) {
        switch(df->columns[i]->column_type) {
            case NULLVAL:
                // Handle NULLVAL case
                break;
            case UINT:
                if (*((unsigned int*)df->columns[i]->data) > *((unsigned int*)x)) {
                    count++;
                }
                break;
            case INT:
                if (*((int*)df->columns[i]->data) > *((int*)x)) {
                    count++;
                }
                break;
            case CHAR:
                if (*((char*)df->columns[i]->data) > *((char*)x)) {
                    count++;
                }
                break;
            case FLOAT:
                if (*((float*)df->columns[i]->data) > *((float*)x)) {
                    count++;
                }
                break;
            case DOUBLE:
                if (*((double*)df->columns[i]->data) > *((double*)x)) {
                    count++;
                }
                break;
            case STRING:
                if (strcmp((char*)df->columns[i]->data, (char*)x) > 0) {
                    count++;
                }
                break;
            case STRUCTURE:
                // Handle STRUCTURE case
                break;
        }
    }
    return count;
}

int count_cells_less(CDataframe* df, void* x) {
    int count = 0;
    for(int i = 0; i < df->numb_columns; i++) {
        switch(df->columns[i]->column_type) {
            case NULLVAL:
                // Handle NULLVAL case
                break;
            case UINT:
                if (*((unsigned int*)df->columns[i]->data) < *((unsigned int*)x)) {
                    count++;
                }
                break;
            case INT:
                if (*((int*)df->columns[i]->data) < *((int*)x)) {
                    count++;
                }
                break;
            case CHAR:
                if (*((char*)df->columns[i]->data) < *((char*)x)) {
                    count++;
                }
                break;
            case FLOAT:
                if (*((float*)df->columns[i]->data) < *((float*)x)) {
                    count++;
                }
                break;
            case DOUBLE:
                if (*((double*)df->columns[i]->data) < *((double*)x)) {
                    count++;
                }
                break;
            case STRING:
                if (strcmp((char*)df->columns[i]->data, (char*)x) < 0) {
                    count++;
                }
                break;
            case STRUCTURE:
                // Handle STRUCTURE case
                break;
        }
    }
    return count;
}