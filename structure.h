// Creator: Natio & Wek
#ifndef PROJET_C_STRUCTURE_H
#define PROJET_C_STRUCTURE_H
#include <stdio.h>
#include <stdlib.h>
typedef struct  {
    char* title;
    int* data;
    int TP;
    int TL;
}COLUMN;
typedef struct {
    COLUMN **columns;
    int numb_columns;
}CDataframe;
COLUMN *create_column(char* title);
int insert_values(COLUMN* col, int value);
void delete_column(COLUMN* col);
void print_col(COLUMN* col);
// Alimentation
CDataframe* create_dataframe();
void fill_dataframe(CDataframe* df);
void fill_dataframe_hardcoded(CDataframe* df);
// Affichage
void print_dataframe(CDataframe* df);
void print_dataframe_ligne(CDataframe* df, int ligne);
void print_dataframe_column(CDataframe* df, int column);
// Opérations usuelles
void add_row_dataframe(CDataframe* df, int* row_values);
void delete_row_dataframe(CDataframe* df, int row_index);
void add_column_dataframe(CDataframe* df, char* title);
void delete_column_dataframe(CDataframe* df, int column_index);
void rename_column_dataframe(CDataframe* df, int column_index, char* new_title);
// Analyse et statistiques
int value_exists_in_dataframe(CDataframe* df, int value);
int get_value_from_dataframe(CDataframe* df, int row, int col);
void set_value_in_dataframe(CDataframe* df, int row, int col, int new_value);
int get_number_rows(CDataframe* df);
int get_number_columns(CDataframe* df);

int count_cells_equal(CDataframe* df, int x);
int count_cells_greater(CDataframe* df, int x);
int count_cells_less(CDataframe* df, int x);

#endif //PROJET_C_STRUCTURE_H
