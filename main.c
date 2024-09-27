#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "board.h"
#include "colors.h"




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

        char *name = choose_name(i);
        char* nom = malloc(sizeof(char) * strlen(name));
        strcpy(nom,name);

        players[i]=newPlayer(nom,i,color,simb);
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


/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PIECE_EMPTY '.'
#define MAX_PLAYERS 2
#define PORT 8080

typedef struct {
    char** grid;
    int player_turn;
    int grid_height;
    int grid_width;
    int win_condition;
    int nb_players;
} Game;

typedef struct {
    int server_socket;
    socklen_t addr_len;
    struct sockaddr_in address;
} ServerSocket;

char player_pieces[MAX_PLAYERS] = {'O', 'X'};

ServerSocket init_server(int port) {
    ServerSocket server;
    server.server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server.server_socket < 0) {
        perror("Erreur de création du socket");
        exit(EXIT_FAILURE);
    }

    server.address.sin_family = AF_INET;
    server.address.sin_addr.s_addr = INADDR_ANY;
    server.address.sin_port = htons(port);
    server.addr_len = sizeof(server.address);

    if (bind(server.server_socket, (struct sockaddr*)&server.address, server.addr_len) < 0) {
        perror("Erreur lors du bind");
        close(server.server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server.server_socket, 2) < 0) {
        perror("Erreur lors du listen");
        close(server.server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Serveur en écoute sur le port %d\n", port);
    return server;
}

Game* init_game(int grid_height, int grid_width, int win_condition, int nb_players) {
    Game* game = malloc(sizeof(Game));
    game->grid = malloc(grid_height * sizeof(char*));
    for (int i = 0; i < grid_height; i++) {
        game->grid[i] = malloc(grid_width * sizeof(char));
        for (int j = 0; j < grid_width; j++) {
            game->grid[i][j] = PIECE_EMPTY;
        }
    }
    game->player_turn = 0;
    game->grid_height = grid_height;
    game->grid_width = grid_width;
    game->win_condition = win_condition;
    game->nb_players = nb_players;
    return game;
}

void free_game(Game* game) {
    for (int i = 0; i < game->grid_height; i++) {
        free(game->grid[i]);
    }
    free(game->grid);
    free(game);
}

void print_grid(Game* game) {
    printf("You have to place %d tokens to win !\n", game->win_condition);

    for (int i = 0; i < game->grid_height; i++) {
        printf("|");
        for (int j = 0; j < game->grid_width; j++) {
            printf(" %c |", game->grid[i][j]);
        }
        printf("\n");
    }

    for (int j = 0; j < game->grid_width; j++) {
        printf(" %3d ", j);
    }
    printf("\n");
}

void format_grid(Game* game, char* buffer) {
    strcpy(buffer, "You have to place tokens to win!\n");


    for (int i = 0; i < game->grid_height; i++) {
        strcat(buffer, "|");
        for (int j = 0; j < game->grid_width; j++) {
            char temp[4];
            snprintf(temp, sizeof(temp), " %c |", game->grid[i][j]);
            strcat(buffer, temp);
        }
        strcat(buffer, "\n");
    }

    for (int j = 0; j < game->grid_width; j++) {
        char temp[5];
        snprintf(temp, sizeof(temp), " %2d ", j);
        strcat(buffer, temp);
    }
    strcat(buffer, "\n");
}

int move_piece(Game* game, int col) {
    if (col < 0 || col >= game->grid_width) {
        printf("Colonne invalide !\n");
        return -1;
    }

    if (game->grid[0][col] != PIECE_EMPTY) {
        printf("Colonne déjà pleine !\n");
        return -1;
    }

    int row = game->grid_height - 1;
    while (row >= 0 && game->grid[row][col] != PIECE_EMPTY) {
        row--;
    }
    game->grid[row][col] = player_pieces[game->player_turn];
    game->player_turn = (game->player_turn + 1) % game->nb_players;
    return 0;
}

int check_win(Game* game) {
    int count;
    char current_piece;

    for (int i = 0; i < game->grid_height; i++) {
        for (int j = 0; j <= game->grid_width - game->win_condition; j++) {
            current_piece = game->grid[i][j];
            if (current_piece != PIECE_EMPTY) {
                count = 1;
                for (int k = 1; k < game->win_condition; k++) {
                    if (game->grid[i][j + k] == current_piece) {
                        count++;
                    } else {
                        break;
                    }
                }
                if (count == game->win_condition) return game->player_turn == 0 ? 2 : 1;
            }
        }
    }

    return -1;
}

void game_loop(int client_socket, Game* game) {
    int winner = -1;
    char buffer[2048] = {0};

    while (winner == -1) {
        print_grid(game);

        if (game->player_turn == 0) {
            printf("Joueur 1 (O), entrez la colonne : ");
            int col;
            scanf("%d", &col);

            if (move_piece(game, col) != 0) {
                continue;
            }

            format_grid(game, buffer);
            send(client_socket, buffer, strlen(buffer), 0);
        } else {
            printf("En attente du coup du joueur 2...\n");
            recv(client_socket, buffer, sizeof(buffer), 0);
            int col = atoi(buffer);

            if (move_piece(game, col) != 0) {
                continue;
            }
        }

        winner = check_win(game);
    }

    printf("Le joueur %d a gagné !\n", winner);
    send(client_socket, "Le joueur a gagné !", strlen("Le joueur a gagné !"), 0);
}

int main() {
    ServerSocket server = init_server(PORT);
    int client_socket;
    struct sockaddr_in client_address;
    socklen_t client_addr_len = sizeof(client_address);

    printf("En attente de connexion...\n");
    client_socket = accept(server.server_socket, (struct sockaddr*)&client_address, &client_addr_len);

    if (client_socket < 0) {
        perror("Erreur lors de accept");
        close(server.server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Joueur 2 connecté !\n");

    int grid_height = 6, grid_width = 7, win_condition = 4;
    Game* game = init_game(grid_height, grid_width, win_condition, MAX_PLAYERS);

    game_loop(client_socket, game);

    free_game(game);
    close(client_socket);
    close(server.server_socket);

    return 0;
}*/
