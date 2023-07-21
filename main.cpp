#include <SDL2//SDL.h>
#include <iostream>
#include "color.h"
# include "render.h"
# include "framebuffer.h"
#include <vector>
using namespace std;

// Dimensiones de la ventana
const int WINDOW_WIDTH = pantallaAncho;
const int WINDOW_HEIGHT = pantallaAlto;

// Dimensiones de la raqueta
const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 100;

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
        cout<<x<<','<<y<<' '<<aliveNeighbors<< endl;

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
        // Oscilador "Toad" (Período 2)
        {50, 20},
        {51, 20},
        {52, 20},
        {49, 21},
        {50, 21},
        {51, 21},
        // Oscilador "Toad" (Período 2)
        {65, 25},
        {66, 25},
        {67, 25},
        {66, 26},
        {67, 26},
        {68, 26},
                // Oscilador "Blinker" (Período 2)
        {10, 10},
        {11, 10},
        {12, 10},
        // Oscilador "Blinker" (Período 2)
        {25, 15},
        {26, 15},
        {27, 15},
        // Agrega más puntos aquí si lo deseas
        // Nave "Glider"
        {5, 5},
        {6, 6},
        {4, 7},
        {5, 7},
        {6, 7},
        // Nave "Glider"
        {30, 40},
        {31, 41},
        {32, 39},
        {32, 40},
        {32, 41},
                // Nave "LWSS"
        {70, 50},
        {71, 50},
        {72, 50},
        {73, 50},
        {69, 51},
        {73, 51},
        {73, 52},
        {69, 53},
        {72, 53},
        // Nave "LWSS"
        {15, 70},
        {16, 70},
        {17, 70},
        {18, 70},
        {14, 71},
        {18, 71},
        {18, 72},
        {14, 73},
        {17, 73},
        // Agrega más puntos aquí si lo deseas
    };

    for (const auto& p : initialPoints) {
        setCurrentColor(WHITE);
        point(p.x, p.y);
    }
}


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("life", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

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
