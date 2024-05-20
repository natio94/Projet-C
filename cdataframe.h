#ifndef PROJET_C_CDATAFRAME_H
#define PROJET_C_CDATAFRAME_H
#include <stdio.h>
#include <stdlib.h>
#include "column.h"
#include <string.h>
typedef struct {
    COLUMN **columns;
    int numb_columns;
}CDataframe;
/**
 * Crée un nouveau dataframe.
 * @return Un pointeur vers le dataframe nouvellement créé.
 */
CDataframe* create_dataframe();

// Remplissage
/**
 * Remplit un dataframe avec l'entrée de l'utilisateur.
 * @param df Le dataframe à remplir.
 */
void fill_dataframe(CDataframe* df);

/**
 * Remplit un dataframe avec des données déjà définie.
 * @param df Le dataframe à remplir.
 */
void fill_dataframe_hardcoded(CDataframe* df);

// Affichage
/**
 * Affiche un dataframe.
 * @param df Le dataframe à afficher.
 */
void print_dataframe(CDataframe* df);

/**
 * Affiche une ligne spécifique d'un dataframe.
 * @param df Le dataframe.
 * @param ligne L'indice de la ligne à afficher.
 */
void print_dataframe_ligne(CDataframe* df, int ligne);

/**
 * Affiche une colonne spécifique d'un dataframe.
 * @param df Le dataframe.
 * @param column L'indice de la colonne à afficher.
 */
void print_dataframe_column(CDataframe* df, int column);

// Opérations usuelles
/**
 * Ajoute une ligne à un dataframe.
 * @param df Le dataframe.
 * @param row_values Les valeurs de la ligne à ajouter.
 */
void add_row_dataframe(CDataframe* df, int* row_values);

/**
 * Supprime une ligne d'un dataframe.
 * @param df Le dataframe.
 * @param row_index L'indice de la ligne à supprimer.
 */
void delete_row_dataframe(CDataframe* df, int row_index);

/**
 * Ajoute une colonne à un dataframe.
 * @param df Le dataframe.
 * @param type Le type de la colonne à ajouter.
 * @param title Le titre de la colonne à ajouter.
 */
void add_column_dataframe(CDataframe* df, ENUM_TYPE type, char* title);

/**
 * Supprime une colonne d'un dataframe.
 * @param df Le dataframe.
 * @param column_index L'indice de la colonne à supprimer.
 */
void delete_column_dataframe(CDataframe* df, int column_index);

/**
 * Renomme une colonne d'un dataframe.
 * @param df Le dataframe.
 * @param column_index L'indice de la colonne à renommer.
 * @param new_title Le nouveau titre de la colonne.
 */
void rename_column_dataframe(CDataframe* df, int column_index, char* new_title);

// Analyse et statistiques
/**
 * Vérifie si une valeur existe dans un dataframe.
 * @param df Le dataframe.
 * @param value La valeur à rechercher.
 * @return 1 si la valeur existe, 0 sinon.
 */
int value_exists_in_dataframe(CDataframe* df, void* value);

/**
 * Récupère une valeur d'un dataframe.
 * @param df Le dataframe.
 * @param row L'indice de la ligne.
 * @param col L'indice de la colonne.
 * @return La valeur à l'indice donné.
 */
void* get_value_from_dataframe(CDataframe* df, int row, int col);

/**
 * Modifie une valeur d'un dataframe.
 * @param df Le dataframe.
 * @param row L'indice de la ligne.
 * @param col L'indice de la colonne.
 * @param new_value La nouvelle valeur à insérer.
 */
void set_value_in_dataframe(CDataframe* df, int row, int col, void* new_value);

/**
 * Récupère le nombre de lignes d'un dataframe.
 * @param df Le dataframe.
 * @return Le nombre de lignes.
 */
int get_number_rows(CDataframe* df);

/**
 * Récupère le nombre de colonnes d'un dataframe.
 * @param df Le dataframe.
 * @return Le nombre de colonnes.
 */
int get_number_columns(CDataframe* df);

/**
 * Récupère le nombre de valeurs égales à une valeur donnée dans un dataframe.
 * @param df Le dataframe.
 * @param x La valeur à rechercher.
 * @return Le nombre de valeurs égales à x.
 */
int count_cells_equal(CDataframe* df, void* x);

/**
 * Récupère le nombre de valeurs supérieures à une valeur donnée dans un dataframe.
 * @param df Le dataframe.
 * @param x La valeur à comparer.
 * @return Le nombre de valeurs supérieures à x.
 */
int count_cells_greater(CDataframe* df, void* x);

/**
 * Récupère le nombre de valeurs inférieures à une valeur donnée dans un dataframe.
 * @param df Le dataframe.
 * @param x La valeur à comparer.
 * @return Le nombre de valeurs inférieures à x.
 */
int count_cells_less(CDataframe* df, void* x);

/**
 * Permet d'afficher un menu dans la console pour tester les différentes actions que l'on peut faire sur un dataframe.
 */
void test_dataframe();
#endif //PROJET_C_CDATAFRAME_H
