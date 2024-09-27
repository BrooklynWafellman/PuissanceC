#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char* name;
    int id;
    char *color;
    char symbol;
} Player;

Player *newPlayer(char* nom, int id, char *color, char symbol);
char choose_symbol(int player_num, char* used_symbols);
char* choose_name(int player_num);
void freePlayer(Player *p);

#endif //PLAYER_H
