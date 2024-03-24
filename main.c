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


int main(int argc, char* argv[]) {

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
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);
        //loop start

        render_grid(renderer, 300, 30);

        //loop end
        SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 255);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return 0;
}
