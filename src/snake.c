#include "../headers/snake.h"


void init_snake() {

    Snake *new= malloc(sizeof(Snake));

    new->x = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
    new->y = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);

    // Set the initial direction based on the initial position
    if (new->x < GRID_SIZE / 2 && new->y >= GRID_SIZE / 2) {
        new->dir = SNAKE_RIGHT;
    } else if (new->x >= GRID_SIZE / 2 && new->y < GRID_SIZE / 2) {
        new->dir = SNAKE_LEFT;
    } else if (new->y < GRID_SIZE / 2) {
        new->dir = SNAKE_DOWN;
    } else {
        new->dir = SNAKE_UP;
    }

    new->next = NULL;

    head = new;
    tail = new;

}

void increase_snake(){

    Snake *new = malloc(sizeof(Snake));

    switch (tail->dir) {

        case SNAKE_UP:
            new->x = tail->x;
            new->y = tail->y + 1;
            break;
        case SNAKE_DOWN:
            new->x = tail->x;
            new->y = tail->y - 1;
            break;
        case SNAKE_LEFT:
            new->x = tail->x + 1;
            new->y = tail->y;
            break;
        case SNAKE_RIGHT:
            new->x = tail->x - 1;
            new->y = tail->y;
            break;

    }

    new->x = tail->x;
    new->y = tail->y - 1;
    new->dir = tail->dir;

    new->next = NULL;
    tail->next = new;

    tail = new;


}

void move_snake() {

    int prev_x = head->x;
    int prev_y = head->y;
    int prev_dir = head->dir;


    // Update the position of the head based on its direction
    switch (head->dir) {
        case SNAKE_UP:
            head->y--;
            break;
        case SNAKE_DOWN:
            head->y++;
            break;
        case SNAKE_LEFT:
            head->x--;
            break;
        case SNAKE_RIGHT:
            head->x++;
            break;
    }

    Snake *track = head;

    if(track->next != NULL){
        track = track->next;
    }

    while (track != NULL){

        int save_x = track->x;
        int save_y = track->y;
        int save_dir = track->dir;

        track->x = prev_x;
        track->y = prev_y;
        track->dir = prev_dir;

        track = track->next;

        prev_x = save_x;
        prev_y = save_y;
        prev_dir = save_dir;
    }


}

void reset_snake(){
    Snake *track = head;
    Snake *temp;

    while (track != NULL){

        temp = track;
        track = track->next;
        free(temp);

    }

    init_snake();
    increase_snake();
    increase_snake();

    score = 0;


}

void detect_crash(){

    if (head->x < 0 || head->x >= GRID_SIZE || head->y < 0 || head->y >= GRID_SIZE){
        reset_snake();
        direction_set = false;
    }

    Snake *track = head->next;

    if(track->next != NULL){
        track = track->next;
    }

    while(track != NULL){
        if (track->x == head->x && track->y == head->y){
            reset_snake();
        }
        track = track->next;
    }

}
