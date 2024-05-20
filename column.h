// Creator: Natio & Wek
#ifndef PROJET_C_COLUMN_H
#define PROJET_C_COLUMN_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define REALOC_SIZE 256
#define ASC 0
#define DESC 1
typedef enum {
    NULLVAL = 1, UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
} ENUM_TYPE;

typedef union {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char *string_value;
    void *struct_value;
} COL_TYPE;

typedef struct {
    char *title;
    unsigned int TP;
    unsigned int TL;
    ENUM_TYPE column_type;
    COL_TYPE **data;
    unsigned long long int *index;
    int valid_index;
    unsigned int index_size;
    int sort_dir;
} COLUMN;

/**
 * Crée une nouvelle colonne.
 * @param type Le type de données de la nouvelle colonne.
 * @param title Le titre de la nouvelle colonne.
 * @return Un pointeur vers la nouvelle colonne.
 */
COLUMN *create_column(ENUM_TYPE type, char *title);

/**
 * Insère des valeurs dans une colonne.
 * @param col La colonne dans laquelle insérer les valeurs.
 * @param value La valeur à insérer.
 * @return 1 si l'insertion a réussi, 0 sinon.
 */
int insert_values(COLUMN *col, void *value);

/**
 * Supprime une colonne.
 * @param col La colonne à supprimer.
 */
void delete_column(COLUMN *col);

/**
 * Affiche une colonne.
 * @param col La colonne à afficher.
 */
void print_col(COLUMN *col);

/**
 * Compte le nombre de valeurs dans une colonne.
 * @param col La colonne.
 * @param x La valeur à rechercher.
 * @return Le nombre de valeurs trouvées.
 */
int nbVal(COLUMN *col, void *x);

/**
 * Convertit une colonne en chaîne de caractères.
 * @param col La colonne à convertir.
 * @param i L'indice de la valeur à convertir.
 * @param str La chaîne de caractères.
 * @param size La taille de la chaîne de caractères.
 */
void convertCol(COLUMN *col, unsigned long long int i, char *str, unsigned int size);

/**
 * Compare une valeur à une autre dans une colonne.
 * @param col La colonne.
 * @param x La valeur à comparer.
 * @return 1 si la valeur est dans la colonne, 0 sinon.
 */
int valInCol(COLUMN *col, void *x);

/**
 * Récupère une valeur à une position donnée dans une colonne.
 * @param col La colonne.
 * @param x La position de la valeur.
 * @return La valeur à la position donnée.
 */
void *valPosX(COLUMN *col, int x);

/**
 * Compte le nombre de valeurs supérieures à une valeur donnée dans une colonne.
 * @param col La colonne.
 * @param x La valeur à comparer.
 * @return Le nombre de valeurs supérieures.
 */
int nbSupVal(COLUMN *col, void *x);

/**
 * Compte le nombre de valeurs inférieures à une valeur donnée dans une colonne.
 * @param col La colonne.
 * @param x La valeur à comparer.
 * @return Le nombre de valeurs inférieures.
 */
int nbInfVal(COLUMN *col, void *x);

/**
 * Compte le nombre de valeurs égales à une valeur donnée dans une colonne.
 * @param col La colonne.
 * @param x La valeur à comparer.
 * @return Le nombre de valeurs égales.
 */
int nbEqualVal(COLUMN *col, int x);

/**
* Trie une colonne dans un certain ordre
* @param col Le pointeur de la colonne à trier
* @param sort_dir Type de tri (ASC ou DESC)
*/
void sort_col(COLUMN *col, int sort_dir);

/**
 * Affiche une colonne par index.
 * @param col La colonne.
 */
void print_col_by_index(COLUMN *col);

/**
 * Mets à jour l'index de la colonne.
 * @param col La colonne.
 */
void update_index(COLUMN *col);

/**
 * Vérifie si une colonne est indexée.
 * @param col La colonne.
 * @return 1 si la colonne est indexée, 0 sinon.
 */
int check_index(COLUMN *col);

/**
 * Supprime l'index d'une colonne.
 * @param col La colonne.
 */
void erase_index(COLUMN *col);

/**
 * Recherche une valeur dans une colonne.
 * @param col La colonne.
 * @param value La valeur à rechercher.
 * @return 1 si la valeur est trouvée, 0 sinon.
 */
int search_value_in_column(COLUMN *col, void *value);

/**
 * Affiche l'index d'une colonne.
 * @param col La colonne.
 */
void print_index(COLUMN *col);

/**
 * Permet d'afficher un menu dans la console pour tester les différentes actions que l'on peut faire sur une colonne.
 */
void test_column();

#endif //PROJET_C_COLUMN_H
