#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include <SDL.h>
#include <stdio.h>
#include <time.h>

#define GRID_SIZE 20
#define GRID_DIM 1000



extern int score;
extern int high_score;
extern bool direction_set;
extern SDL_Color snake_color;

enum {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT,
};

struct snake {
    int x;
    int y;
    int dir;

    struct snake *next;
};


typedef struct snake Snake;


extern Snake *head, *tail;

void init_snake();
void increase_snake();
void move_snake();
void reset_snake();
void detect_crash();

#endif //SNAKE_H