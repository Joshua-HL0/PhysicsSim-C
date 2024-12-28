#include "sim.h"
#include <SDL2/SDL_render.h>
#include <stdlib.h>
#include <math.h>

int main(){
    SDL_Init(SDL_INIT_VIDEO);

    char *windowName = "PhySim";
    SDL_Window *window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    new_circle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, DEFAULT_RADIUS);
    draw_circle(&circles[circleCount-1]);
    

    uint8_t running = 1;
    SDL_Event event;
    while (running){

        render_circles();

        while (SDL_PollEvent(&event)){
            switch (event.type){
                case (SDL_QUIT): running = 0;
                case (SDL_MOUSEBUTTONDOWN) : handle_click(&event.button);
            }
        }

        update_circles();
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void new_circle(int x, int y, int radius){
   
    Circle *newCircle = malloc(sizeof(Circle));

    newCircle->x = x;
    newCircle->y = y;
    newCircle->radius = radius;
    newCircle->velocity.x = 0;
    newCircle->velocity.y = 0;

    circles[circleCount] = *newCircle;
    circleCount++;
}

void draw_circle(Circle *circle){
    
    int lowerX = circle->x - circle->radius;
    int lowerY = circle->y - circle->radius;
    int upperX = circle->x + circle->radius;
    int upperY = circle->y + circle->radius;
    int radiusSquared = circle->radius * circle->radius;

    for (int x = lowerX; x < upperX; x++){
        for (int y = lowerY; y < upperY; y++){
            int distanceSquared = ((x - circle->x) * (x - circle->x)) + ((y - circle->y) * (y - circle->y));
            if ((x * x) + (y * y) < radiusSquared){
                SDL_Rect rect = {x, y, 1, 1};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void update_circles(){

}

void render_circles(){
    
    SDL_SetRenderDrawColor(renderer, COLOUR_BLACK);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, COLOUR_WHITE);

    for (int i = 0; i < circleCount; i++){
        draw_circle(&circles[circleCount-1]);
    }

    SDL_RenderPresent(renderer);
}

void handle_click(SDL_MouseButtonEvent *e){
    if (e->button == SDL_BUTTON_LEFT){
        int x, y;
        SDL_GetMouseState(&x, &y);
        new_circle(x, y, DEFAULT_RADIUS);
    }
}
