#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    //char* name;
    int id;
    char *color;
    char symbol;
} Player;

Player *newPlayer(int id, char *color, char symbol);

#endif //PLAYER_H
