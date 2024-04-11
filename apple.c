#include "apple.h"
#include "snake.h"

apple Apple;

void gen_apple(){

    bool in_snake;

    do {
        in_snake = false;
        Apple.x = rand() % GRID_SIZE;
        Apple.y = rand() % GRID_SIZE;

        Snake *track = head;

        while (track != NULL){
            if (track->x == Apple.x && track->y == Apple.y){
                in_snake = true;
            }
            track = track->next;
        }

    } while (in_snake);

}


void detect_apple(){
    if (head->x == Apple.x && head->y == Apple.y){

        increase_snake();
        gen_apple();
        score++;

        if (score > high_score) {
            high_score = score;
        }
    }
}