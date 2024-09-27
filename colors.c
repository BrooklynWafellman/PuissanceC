#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"


void choose_color(int player_num,char* color) {
    int choice;
    printf("Joueur %d, choisissez votre couleur :\n", player_num + 1);
    printf("1. Rouge\n");
    printf("2. Vert\n");
    printf("3. Jaune\n");
    printf("4. Bleu\n");
    printf("5. Magenta\n");
    printf("6. Cyan\n");
    fflush(stdin);
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(color, COLOR_RED);
        break;
        case 2:
            strcpy(color, COLOR_GREEN);
        break;
        case 3:
            strcpy(color, COLOR_YELLOW);
        break;
        case 4:
            strcpy(color, COLOR_BLUE);
        break;
        case 5:
            strcpy(color, COLOR_MAGENTA);
        break;
        case 6:
            strcpy(color, COLOR_CYAN);
        break;
        default:
            printf("Choix invalide, couleur par defaut (Jaune) attribuee.\n");
        strcpy(color, COLOR_YELLOW);
        break;
    }
}

