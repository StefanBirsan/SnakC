#ifndef APPLE_H
#define APPLE_H

#include <SDL.h>

typedef struct {
    int x;
    int y;
} apple;

extern apple Apple;

void gen_apple();
void detect_apple();

#endif