/**
 * Projet C Dataframe
 * Ce fichier contient la fonction main et test les fonctionnalités des colonnes et des dataframes.
 * @authors CORNUAU Nathan et THIRARD Wagner
 * */
#include "column.h"
#include "cdataframe.h"

int main() {
    printf("Voulez-vous tester : \n1. Les colonnes\n2. Les dataframes\n");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
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
    return 0;
}

