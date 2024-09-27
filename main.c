#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "board.h"
#include "colors.h"


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

int main() {

    //Player *P1 = newPlayer(1,"\033[1;33m",'O');
    //Player *P2 = newPlayer(2,"\033[1;33m",'O');

    int grid_height;
    int grid_width;
    int win_condition;
    int nb_players;

    printf(" Entrez la hauteur de la grille : ");
    scanf("%d", &grid_height);
    printf("Entrez la largeur de la grille : ");
    scanf("%d", &grid_width);
    if (grid_height < 2 || grid_width < 2) {
        printf("La taille de la grille est invalide !\n");
        return 1;
    }
    printf("Entrez le nombre de joueurs : ");
    scanf("%d", &nb_players);
    if (nb_players<2) {
        printf("Le nombre de joueurs est invalide !\n");
        return 1;
    }

    Player **players = malloc(sizeof(Player*) * nb_players);
    char *symbol_used = malloc(sizeof(char) * nb_players);
    for (int i = 0; i < nb_players; i++) {
        char simb = choose_symbol(i,symbol_used);
        char* color = malloc(sizeof(char) * 11);
        choose_color(i,color);
        players[i]=newPlayer(i,color,simb);
    }

    printf("Entrez le nombre de pions a aligner pour gagner (minimum 2) : ");
    scanf("%d", &win_condition);
    int min_dimension = (grid_height < grid_width) ? grid_height : grid_width;
    if (win_condition < 2 || win_condition > min_dimension*nb_players) {
        printf("Le nombre de pions a aligner est invalide !\n");
        return 1;
    }
    Game* game = init_game(grid_height, grid_width, win_condition,players,nb_players);
    game_loop(game);
    free_game(game);
    return 0;
}