#include "snake.h"
#include "apple.h"
#include "render.h"

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

Snake *head, *tail;
int score = 0;
int high_score = 0;
int delay;
bool direction_set = false;
SDL_Color snake_color = {0x00, 0xff, 0x00, 255};


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
                                direction_set = true;
                            }
                            break;
                        case SDLK_DOWN:
                            if (head->dir != SNAKE_UP) {
                                head->dir = SNAKE_DOWN;
                                direction_set = true;
                            }
                            break;
                        case SDLK_LEFT:
                            if (head->dir != SNAKE_RIGHT) {
                                head->dir = SNAKE_LEFT;
                                direction_set = true;
                            }
                            break;
                        case SDLK_RIGHT:
                            if (head->dir != SNAKE_LEFT) {
                                head->dir = SNAKE_RIGHT;
                                direction_set = true;
                            }
                            break;
                        case SDLK_SPACE:
                            delay = 100;
                            break;
                        case SDLK_f:

                            snake_color.r = rand() % 256;
                            snake_color.g = rand() % 256;
                            snake_color.b = rand() % 256;
                            break;
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);
        //loop start

        //move the snake
        if (direction_set) {
            move_snake();
            detect_crash();
            detect_apple();
        }

        render_grid(renderer, 300, 30);
        render_snake(renderer, 300, 30);
        render_apple(renderer, 300, 10);
        render_score(renderer, 1250, 30, 20);
        render_high_score(renderer, 1250, 400, 20);

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