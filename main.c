#include "snake.h"

#if 0
//almost fullscreen
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_WIDTH 2880
#define WINDOW_HEIGHT 1800

#else
//stream
#define WINDOW_WIDTH 2880
#define WINDOW_HEIGHT 1800
#define WINDOW_X 0
#define WINDOW_Y 0
#endif

#define GRID_SIZE 20
#define GRID_DIM 1000

int score = 0;
int delay;



enum {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT,
};

typedef struct {
    int x;
    int y;

} apple;

apple Apple;

struct snake {
    int x;
    int y;
    int dir;

    struct snake *next;
};

typedef struct snake Snake;

Snake *head;
Snake *tail;

void init_snake(){

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

    return;
}

void render_snake(SDL_Renderer *renderer, int x, int y){

    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);
    int seg_size = GRID_DIM / GRID_SIZE - 10;
    SDL_Rect seg;

    seg.w = seg_size;
    seg.h = seg_size;

    Snake *track = head;

    while (track != NULL){
        seg.x = x + track->x * seg_size; // Corrected line
        seg.y = y + track->y * seg_size;

        SDL_RenderFillRect(renderer, &seg);

        track = track->next;
    }

    return;
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

    return;

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

    return;
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

    return;
}


void render_grid(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0X55, 255);


    int cell_size = GRID_DIM / GRID_SIZE - 10;
    SDL_Rect cell;

    cell.w = cell_size;
    cell.h = cell_size;

    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            cell.x = x + (i * cell_size);
            cell.y = y + (j * cell_size);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }



    return;
}

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

void render_apple(SDL_Renderer *renderer, int x, int y){

    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 255);

    int cell_size = GRID_DIM / GRID_SIZE - 10;
    int apple_size = cell_size - 10;

    SDL_Rect appl;

    appl.w = apple_size;
    appl.h = apple_size;

    appl.x = (x + Apple.x * cell_size + (cell_size - apple_size) / 2);
    appl.y = (y + Apple.y * cell_size + (cell_size - apple_size) / 2) + 20;

    SDL_RenderFillRect(renderer, &appl);

}

void detect_apple(){
    if (head->x == Apple.x && head->y == Apple.y){
        increase_snake();
        gen_apple();
        score++;
    }
    return;
}

void detect_crash(){

    if (head->x < 0 || head->x >= GRID_SIZE || head->y < 0 || head->y >= GRID_SIZE){
        reset_snake();
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

void draw_digit(SDL_Renderer *renderer, int digit, int x, int y, int size){
    // Define the 3x5 grid for each digit
    int digits[10][5][3] = {
            {{1, 1, 1}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 1, 1}}, // 0
            {{0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}}, // 1
            {{1, 1, 1}, {0, 0, 1}, {1, 1, 1}, {1, 0, 0}, {1, 1, 1}}, // 2
            {{1, 1, 1}, {0, 0, 1}, {1, 1, 1}, {0, 0, 1}, {1, 1, 1}}, // 3
            {{1, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 0, 1}, {0, 0, 1}}, // 4
            {{1, 1, 1}, {1, 0, 0}, {1, 1, 1}, {0, 0, 1}, {1, 1, 1}}, // 5
            {{1, 1, 1}, {1, 0, 0}, {1, 1, 1}, {1, 0, 1}, {1, 1, 1}}, // 6
            {{1, 1, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}}, // 7
            {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}, {1, 0, 1}, {1, 1, 1}}, // 8
            {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}, {0, 0, 1}, {1, 1, 1}}  // 9
    };

    SDL_Rect rect;
    rect.w = size;
    rect.h = size;

    // Draw the digit
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (digits[digit][i][j]) {
                rect.x = x + j * size;
                rect.y = y + i * size;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void render_score(SDL_Renderer *renderer, int x, int y, int size){
    int temp_score = score;
    int digit_count = 0;

    // Calculate the number of digits in the score
    do {
        digit_count++;
        temp_score /= 10;
    } while (temp_score > 0);

    // Draw each digit
    temp_score = score;
    for (int i = 0; i < digit_count; i++) {
        draw_digit(renderer, temp_score % 10, x + (digit_count - i - 1) * size * 4, y, size);
        temp_score /= 10;
    }
}


int main(int argc, char* argv[]) {

    srand(time(0));

    init_snake();
    increase_snake();
    increase_snake();

    gen_apple();

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow(
            "Snake",
            WINDOW_X,
            WINDOW_Y,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_BORDERLESS
            );

    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    }



    bool quit = false;
    SDL_Event event;

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    while (!quit){
        while (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_UP:
                            if (head->dir != SNAKE_DOWN) {
                                head->dir = SNAKE_UP;
                            }
                            break;
                        case SDLK_DOWN:
                            if (head->dir != SNAKE_UP) {
                                head->dir = SNAKE_DOWN;
                            }
                            break;
                        case SDLK_LEFT:
                            if (head->dir != SNAKE_RIGHT) {
                                head->dir = SNAKE_LEFT;
                            }
                            break;
                        case SDLK_RIGHT:
                            if (head->dir != SNAKE_LEFT) {
                                head->dir = SNAKE_RIGHT;
                            }
                            break;
                        case SDLK_SPACE:
                            delay = 100;
                            break;
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);
        //loop start

        //move the snake
        move_snake();
        detect_crash();
        detect_apple();

        render_grid(renderer, 300, 30);
        render_snake(renderer, 300, 30);
        render_apple(renderer, 300, 10);
        render_score(renderer, 1300, 30, 20);

        //loop end
        SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 255);

        SDL_RenderPresent(renderer);

        if (state[SDL_SCANCODE_SPACE]) {
            delay = 100;
        } else {
            delay = 200;
        }

        SDL_Delay(delay);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return 0;
}
