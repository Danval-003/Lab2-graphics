#include <SDL2//SDL.h>
#include <iostream>
#include "color.h"
# include "render.h"
# include "framebuffer.h"
#include <vector>
using namespace std;

// Dimensiones de la ventana
const int WINDOW_WIDTH = pantallaAncho*3;
const int WINDOW_HEIGHT = pantallaAlto *3;

struct cell{
    int x;
    int y;
};

bool getNextCellState(int x, int y) {
    int aliveNeighbors = 0;

    // Obtener el número de células vecinas vivas
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0)
                continue;

            int neighborX = x + dx;
            int neighborY = y + dy;

            if (getCellState(neighborX, neighborY)) {
                aliveNeighbors++;
            }
        }
    }

    bool currentState = getCellState(x, y);
    if (currentState) {
        // La célula está viva (blanco)

        if (aliveNeighbors < 2 || aliveNeighbors > 3) {
            // underpopulation o overpopulation, la célula muere
            return false;
        } else {
            // survival, la célula se mantiene viva
            return true;
        }
    } else {
        // La célula está muerta (negro)

        if (aliveNeighbors == 3) {
            // reproduction, la célula muerta revive
            return true;
        } else {
            // La célula muerta se mantiene muerta
            return false;
        }
    }
}


void render(SDL_Renderer* renderer) {
    array<bool, pantallaAncho * pantallaAlto> nextFramebuffer;

    for (int y = 0; y < pantallaAlto; ++y) {
        for (int x = 0; x < pantallaAncho; ++x) {
            bool nextState = getNextCellState(x, y);

            nextFramebuffer[y*pantallaAncho+x]=nextState;
        }
    }

    for (int y = 0; y < pantallaAlto; ++y) {
        for (int x = 0; x < pantallaAncho; ++x) {
            if(nextFramebuffer[y*pantallaAncho+x]){
                setCurrentColor(WHITE);
            }else{
                setCurrentColor(BLACK);
            }
            point(x,y );
        }
    }

    // Render the framebuffer to the screen
    renderBuffer(renderer);
}
void setInitialPoints() {
    vector<cell> initialPoints = {
        // Gosper Glider Gun
        {5, 1}, {5, 2}, {6, 1}, {6, 2},
        {5, 11}, {6, 11}, {7, 11}, {4, 12}, {8, 12}, {3, 13}, {9, 13}, {3, 14}, {9, 14}, {6, 15},
        {4, 16}, {8, 16}, {5, 17}, {6, 17}, {7, 17}, {6, 18},
        {3, 21}, {4, 21}, {5, 21}, {3, 22}, {4, 22}, {5, 22}, {2, 23}, {6, 23}, {1, 25}, {2, 25},
        {6, 25}, {7, 25},
        {3, 35}, {4, 35}, {3, 36}, {4, 36},

        // Oscilador "Blinker"
        {12, 3}, {13, 3}, {14, 3},

        // Oscilador "Toad"
        {21, 4}, {22, 4}, {23, 4}, {20, 5}, {21, 5}, {22, 5},

        // Oscilador "Beacon"
        {31, 7}, {32, 7}, {31, 8}, {34, 9}, {33, 10}, {34, 10},

        // Patrón "Glider"
        {41, 0}, {42, 1}, {40, 2}, {41, 2}, {42, 2},

        // Oscilador "Blinker"
        {15, 80}, {16, 80}, {14, 80},

        // Oscilador "Toad"
        {21, 90}, {22, 90}, {23, 90}, {20, 90}, {21, 90}, {22, 90},

        // Oscilador "Beacon"
        {31, 75}, {32, 75}, {31, 76}, {34, 77}, {33, 78}, {34, 78},

        // Patrón "Glider"
        {41, 63}, {42, 64}, {40, 65}, {41, 65}, {42, 65},

        // Oscilador "Blinker"
        {65, 35}, {66, 35}, {64, 35},

        // Oscilador "Toad"
        {71, 45}, {72, 45}, {73, 45}, {70, 45}, {71, 45}, {72, 45},

        // Oscilador "Beacon"
        {81, 37}, {82, 37}, {81, 38}, {84, 39}, {83, 40}, {84, 40},

        // Patrón "Glider"
        {91, 23}, {92, 24}, {90, 25}, {91, 25}, {92, 25}
    };

    for (const auto& p : initialPoints) {
        setCurrentColor(WHITE);
        point(p.x, p.y);
    }
}






int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    bool running = true;
    SDL_Event event;
        // Clear the framebuffer
    clear();
    setInitialPoints();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Call our render function
        render(renderer);

        // Present the frame buffer to the screen
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
