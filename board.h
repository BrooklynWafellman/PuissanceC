//
// Created by brook on 26/09/2024.
//

#ifndef BOARD_H
#define BOARD_H
#include "player.h"
typedef struct {
    char** grid;
    int player_turn;
    int grid_height;
    int grid_width;
    int win_condition;
    Player** player;
    int nb_players;
} Game;

Game* init_game(int grid_height, int grid_width, int win_condition, Player** player,int nb_players);
void free_game(Game* game);
void print_grid(Game* game);
int move_piece(Game* game, int col);
int check_top_left(Game* game ,char sign, int row,int column, int rec);
int check_bot_right(Game* game ,char sign, int row,int column, int rec);
int check_top_right(Game* game ,char sign, int row,int column, int rec);
int check_bot_left(Game* game ,char sign, int row,int column, int rec);
int check_top(Game* game ,char sign, int row,int column, int rec);
int check_bot(Game* game ,char sign, int row,int column, int rec);
int check_left(Game* game ,char sign, int row,int column, int rec);
int check_right(Game* game ,char sign, int row,int column, int rec);
void game_loop(Game* game);
int check_win(Game* game,char sign, int row,int column);


#endif //BOARD_H
