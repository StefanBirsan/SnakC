#include "render.h"
#include "apple.h"
#include "snake.h"

void render_snake(SDL_Renderer *renderer, int x, int y){

    SDL_SetRenderDrawColor(renderer, snake_color.r, snake_color.g, snake_color.b, 255);
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

void render_high_score(SDL_Renderer *renderer, int x, int y, int size){
    int temp_score = high_score;
    int digit_count = 0;


    do {
        digit_count++;
        temp_score /= 10;
    } while (temp_score > 0);

    temp_score = high_score;
    for (int i = 0; i < digit_count; i++) {
        draw_digit(renderer, temp_score % 10, x + (digit_count - i - 1) * size * 4, y, size);
        temp_score /= 10;
    }
}