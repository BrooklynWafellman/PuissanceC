#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    //char* name;
    int id;
    char *color;
    char symbol;
} Player;

Player *newPlayer(int id, char *color, char symbol);
void freePlayer(Player *p);

#endif //PLAYER_H
