//
// Created by brook on 26/09/2024.
//

#ifndef BOARD_H
#define BOARD_H

typedef struct {
    char** grid;
    int player_turn;
    int grid_height;
    int grid_width;
    int win_condition;
} Game;

Game* init_game(int grid_height, int grid_width, int win_condition);
void free_game(Game* game);
void print_grid(Game* game);
void move_piece(Game* game, int col);
void game_loop(Game* game);
int check_win(Game* game);


#endif //BOARD_H
