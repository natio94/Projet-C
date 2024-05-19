// Creator: Natio & Wek
#ifndef PROJET_C_COLUMN_H
#define PROJET_C_COLUMN_H
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
///l
typedef enum
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
}ENUM_TYPE;

typedef union {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
}COL_TYPE;

typedef struct  {
    char* title;
    unsigned int TP;
    unsigned int TL;
    ENUM_TYPE column_type;
    COL_TYPE **data;
    unsigned long long int *index;
}COLUMN;
/**
 * Crée une nouvelle colonne.
 * @param type Le type de données de la nouvelle colonne.
 * @param title Le titre de la nouvelle colonne.
 * @return Un pointeur vers la nouvelle colonne.
 */
COLUMN *create_column(ENUM_TYPE type, char* title);

/**
 * Insère des valeurs dans une colonne.
 * @param col La colonne dans laquelle insérer les valeurs.
 * @param value La valeur à insérer.
 * @return 1 si l'insertion a réussi, 0 sinon.
 */
int insert_values(COLUMN* col, void* value);

/**
 * Supprime une colonne.
 * @param col La colonne à supprimer.
 */
void delete_column(COLUMN* col);

/**
 * Affiche une colonne.
 * @param col La colonne à afficher.
 */
void print_col(COLUMN* col);

/**
 * Compte le nombre de valeurs dans une colonne.
 * @param col La colonne.
 * @param x La valeur à rechercher.
 * @return Le nombre de valeurs trouvées.
 */
int nbVal(COLUMN* col, void* x);

/**
 * Convertit une colonne en chaîne de caractères.
 * @param col La colonne à convertir.
 * @param i L'indice de la valeur à convertir.
 * @param str La chaîne de caractères.
 * @param size La taille de la chaîne de caractères.
 */
void convertCol(COLUMN* col, unsigned long long int i, char *str,unsigned int size);

/**
 * Compare une valeur à une autre dans une colonne.
 * @param col La colonne.
 * @param x La valeur à comparer.
 * @return 1 si la valeur est dans la colonne, 0 sinon.
 */
int valInCol(COLUMN *col, void* x);

/**
 * Récupère une valeur à une position donnée dans une colonne.
 * @param col La colonne.
 * @param x La position de la valeur.
 * @return La valeur à la position donnée.
 */
void* valPosX(COLUMN *col, int x);

/**
 * Compte le nombre de valeurs supérieures à une valeur donnée dans une colonne.
 * @param col La colonne.
 * @param x La valeur à comparer.
 * @return Le nombre de valeurs supérieures.
 */
int nbSupVal(COLUMN *col, void* x);

/**
 * Compte le nombre de valeurs inférieures à une valeur donnée dans une colonne.
 * @param col La colonne.
 * @param x La valeur à comparer.
 * @return Le nombre de valeurs inférieures.
 */
int nbInfVal(COLUMN *col, void* x);

/**
 * Compte le nombre de valeurs égales à une valeur donnée dans une colonne.
 * @param col La colonne.
 * @param x La valeur à comparer.
 * @return Le nombre de valeurs égales.
 */
int nbEqualVal(COLUMN *col, int x);

#endif //PROJET_C_COLUMN_H
