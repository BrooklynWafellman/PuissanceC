

#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "board.h"

#include "colors.h"
#define PIECE_EMPTY '.'



Game* init_game(int grid_height, int grid_width, int win_condition, Player** player,int nb_players) {
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
    game->player = malloc(sizeof(Player*) * nb_players);
    for (int i = 0; i < nb_players; i++) {
        game->player[i] = malloc(sizeof(Player));
        game->player[i] = player[i]; // possiblement erreur
    }
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
    for (int i = 0; i < game->grid_height; i++) {
        for (int j = 0; j < game->grid_width; j++) {
            for (int k = 0; k < game->nb_players; k++) {
                if(game->grid[i][j] == game->player[k]->symbol) {
                    printf("%s", game->player[k]->color);
                }
            }
            printf("%c%s ", game->grid[i][j],COLOR_RESET);
        }
        printf("\n");
    }
    for (int j = 0; j < game->grid_width; j++) {
        printf("%d ", j + 1);
    }
    printf("\n");
}


int check_top_left(Game* game ,char sign, int row,int column, int rec) {
    if((row>=0 && column>=0) && (row < game->grid_height && column < game->grid_width)) {
        if(game->grid[row][column] == sign) {
            return check_top_left(game, sign, row -1, column -1, rec + 1);
        }
    }
    return rec;
}

int check_bot_right(Game* game ,char sign, int row,int column, int rec) {
    if((row>=0 && column>=0) && (row < game->grid_height && column < game->grid_width)) {
        if(game->grid[row][column] == sign) {
            return check_bot_right(game, sign, row + 1, column + 1, rec + 1);
        }
    }
    return rec;
}

int check_top(Game* game ,char sign, int row,int column, int rec) {
    if((row>=0 && column>=0) && (row < game->grid_height && column < game->grid_width)) {
        if(game->grid[row][column] == sign) {
            return check_top(game, sign, row -1, column, rec + 1);
        }
    }
    return rec;
}

int check_bot(Game* game ,char sign, int row,int column, int rec) {
    if((row>=0 && column>=0) && (row < game->grid_height && column < game->grid_width)) {
        if(game->grid[row][column] == sign) {
            return check_bot(game, sign, row +1, column, rec + 1);
        }
    }
    return rec;
}

int check_left(Game* game ,char sign, int row,int column, int rec) {
    if((row>=0 && column>=0) && (row < game->grid_height && column < game->grid_width)) {
        if(game->grid[row][column] == sign) {
            return check_left(game, sign, row, column-1, rec + 1);
        }
    }
    return rec;
}

int check_right(Game* game ,char sign, int row,int column, int rec) {
    if((row>=0 && column>=0) && (row < game->grid_height && column < game->grid_width)) {
        if(game->grid[row][column] == sign) {
            return check_right(game, sign, row, column+1, rec + 1);
        }
    }
    return rec;
}

int check_top_right(Game* game ,char sign, int row,int column, int rec) {
    if((row>=0 && column>=0) && (row < game->grid_height && column < game->grid_width)) {
        if(game->grid[row][column] == sign) {
            return check_top_right(game, sign, row-1, column+1, rec + 1);
        }
    }
    return rec;
}

int check_bot_left(Game* game ,char sign, int row,int column, int rec) {
    if((row>=0 && column>=0) && (row < game->grid_height && column < game->grid_width)) {
        if(game->grid[row][column] == sign) {
            return check_bot_left(game, sign, row+1, column-1, rec + 1);
        }
    }
    return rec;
}

int check_win(Game* game ,char sign, int row,int column) {
    int result = 0;

    int top_left =check_top_left(game ,sign, row-1,column-1,0);
    int bot_right =check_bot_right(game ,sign, row+1,column+1,0);
    if(result <1 + top_left + bot_right) {
        result = 1 + top_left + bot_right;
    }



        int top =check_top(game ,sign, row-1,column,0);
        int bot =check_bot(game ,sign, row+1,column,0);
        if(result <1 + top + bot) {
            result = 1 + top + bot;
        }

        int left =check_left(game ,sign, row,column-1,0);
        int right =check_right(game ,sign, row,column+1,0);
        if(result <1 + left + right) {
            result = 1 + left + right;
        }

        int top_right =check_top_right(game ,sign, row-1,column+1,0);
        int bot_left =check_bot_left(game ,sign, row+1,column-1,0);
        if(result <1 + top_right + bot_left) {
            result = 1 + top_right + bot_left;
        }


    return result;
}

/*int check_win(Game* game) {
    int count;
    for (int i = 0; i < game->grid_height; i++) {
        for (int j = 0; j <= game->grid_width - game->win_condition; j++) {
            count = 1;
            for (int k = 1; k < game->win_condition; k++) {
                if (game->grid[i][j] != PIECE_EMPTY && game->grid[i][j] == game->grid[i][j + k]) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == game->win_condition) {
                return game->grid[i][j] == PIECE_YELLOW ? 0 : 1;
            }
        }
    }
    for (int i = 0; i <= game->grid_height - game->win_condition; i++) {
        for (int j = 0; j < game->grid_width; j++) {
            count = 1;
            for (int k = 1; k < game->win_condition; k++) {
                if (game->grid[i][j] != PIECE_EMPTY && game->grid[i][j] == game->grid[i + k][j]) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == game->win_condition) {
                return game->grid[i][j] == PIECE_YELLOW ? 0 : 1;
            }
        }
    }
    for (int i = game->win_condition - 1; i < game->grid_height; i++) {
        for (int j = 0; j <= game->grid_width - game->win_condition; j++) {
            count = 1;
            for (int k = 1; k < game->win_condition; k++) {
                if (game->grid[i][j] != PIECE_EMPTY && game->grid[i][j] == game->grid[i - k][j + k]) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == game->win_condition) {
                return game->grid[i][j] == PIECE_YELLOW ? 0 : 1;
            }
        }
    }
    for (int i = 0; i <= game->grid_height - game->win_condition; i++) {
        for (int j = 0; j <= game->grid_width - game->win_condition; j++) {
            count = 1;
            for (int k = 1; k < game->win_condition; k++) {
                if (game->grid[i][j] != PIECE_EMPTY && game->grid[i][j] == game->grid[i + k][j + k]) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == game->win_condition) {
                return game->grid[i][j] == PIECE_YELLOW ? 0 : 1;
            }
        }
    }
    return -1;
}*/

void game_loop(Game* game) {
    int won = 0;
    while (!won) {
        print_grid(game);
        int col;
        printf("Joueur %d, choisissez la colonne (1-%d) : ", game->player_turn + 1, game->grid_width);
        scanf("%d", &col);
        int winner = move_piece(game, col - 1);
        //int winner = check_win(game);
        if (winner >= game->win_condition) {
            print_grid(game);
            printf("Joueur %d a gagne !\n", game->player[game->player_turn]->id+1);
            won = 1;
        }
        game->player_turn = (game->player_turn + 1)%game->nb_players;
    }
}

int move_piece(Game* game, int col) {
    if (col < 0 || col >= game->grid_width) {
        printf("Colonne invalide !\n");
        return;
    }
    if (game->grid[0][col] != PIECE_EMPTY) {
        printf("Colonne deja pleine !\n");
        return;
    }
    int row = game->grid_height - 1;
    while (row >= 0 && game->grid[row][col] != PIECE_EMPTY) {
        row--;
    }
    game->grid[row][col] = game->player[game->player_turn]->symbol;
    return check_win(game,game->player[game->player_turn]->symbol,row,col);
}