#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"


Player *newPlayer(char* nom, int id, char *color, char symbol) {
    Player *p = malloc(sizeof(Player));

    p->name = malloc(sizeof(char) * (strlen(nom) + 1));
    strcpy(p->name,nom);
    p->id = id;
    p->color = malloc(strlen(color) + 1);
    strcpy(p->color, color);
    p->symbol = symbol;

    return p;
}

void freePlayer(Player *p) {
    free(p->name);
    free(p->color);
    free(p);
}

char choose_symbol(int player_num, char* used_symbols) {
    int valid = 0;
    char simb;
    while (!valid) {

        printf("Joueur %d quel est votre symbole ? : ",player_num +1);
        fflush(stdin); //pour eviter de récuperer un \n
        scanf("%c",&simb); //pb avec \0
        while(simb<33 || simb>126 || simb=='.') {
            printf("Choisissez un autre symbole ! : ");
            scanf("%c",&simb);
        }

        valid = 1;
        for (int i = 0; i < player_num; i++) {
            if (simb == used_symbols[i]) {
                printf("Symbole déjà utilisé, choisissez-en un autre.\n");
                valid = 0;
                break;
            }
        }
    }
    used_symbols[player_num] = simb;
    return simb;
}

char* choose_name(int player_num) {
    char* name = malloc(sizeof(char) * 1000);
    int name_size = 1000;

        printf("Joueur %d quel est votre nom ? : ",player_num +1);
        fflush(stdin); //pour eviter de récuperer un \n
        scanf("%s",name);
        if(name!=0) {
            return name;
        }
        else {
            printf("ERREUR : Joueur %d quel est votre nom ? : ",player_num +1);
            fflush(stdin); //pour eviter de récuperer un \n
            scanf("%s",&name);
        }

    return name;
}