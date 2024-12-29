#include "sim.h"
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

        while (SDL_PollEvent(&event)){
            switch (event.type){
                case (SDL_QUIT): running = 0; break;
                case (SDL_MOUSEBUTTONDOWN) : handle_click(&event.button); break;
            }
        }
        
        update_circles();
        render_circles();
        SDL_Delay(30);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void new_circle(int x, int y, int radius){
        
    if (circleCount >= MAX_CIRCLES){
        return;
    }

    circles[circleCount].x = x;
    circles[circleCount].y = y;
    circles[circleCount].radius = radius;
    circles[circleCount].velocity.x = rand() % 2 ? (rand() % 11) : -(rand() % 11);
    circles[circleCount].velocity.y = GRAVITY;

    printf("New X: %d Y: %d VX: %f VY: %f\n", circles[circleCount].x, circles[circleCount].y, circles[circleCount].velocity.x, circles[circleCount].velocity.y);
    circleCount++;
}

void draw_circle(Circle *circle){
    
    SDL_SetRenderDrawColor(renderer, COLOUR_WHITE);

    int lowerX = circle->x - circle->radius;
    int lowerY = circle->y - circle->radius;
    int upperX = circle->x + circle->radius;
    int upperY = circle->y + circle->radius;
    int radiusSquared = circle->radius * circle->radius;

    for (int x = lowerX; x < upperX; x++){
        for (int y = lowerY; y < upperY; y++){
            int distanceSquared = ((x - circle->x) * (x - circle->x)) + ((y - circle->y) * (y - circle->y));
            if (distanceSquared < radiusSquared){
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}


void handle_collision(Circle *a, Circle *b){
    double dx = b->x - a->x;
    double dy = b->y - a->y;

    double distance = sqrt(pow(dx, 2) + pow(dy, 2));

    if (distance < a->radius + b->radius){

        a->velocity.x *= -1;
        a->velocity.y *= -1;
        b->velocity.x *= -1;
        b->velocity.y *= -1;
    }
}

void update_circles(){
    for (int i = 0; i < circleCount; i++){

        circles[i].x += circles[i].velocity.x;
        circles[i].y += circles[i].velocity.y;

        if (circles[i].x - circles[i].radius < 0){
            circles[i].velocity.x *= -1;
            circles[i].x = circles[i].radius;
        }
        else if (circles[i].x + circles[i].radius > WINDOW_WIDTH){
            circles[i].velocity.x *= -1;
            circles[i].x = WINDOW_WIDTH - circles[i].radius;
        }


        if (circles[i].y - circles[i].radius < 0){
            circles[i].velocity.y *= -1;
            circles[i].y = circles[i].radius;
        }
        else if (circles[i].y + circles[i].radius > WINDOW_HEIGHT){
            circles[i].velocity.y *= -1;
            circles[i].y = WINDOW_HEIGHT - circles[i].radius;
        }

        for (int j = 0; j < circleCount; j++){
            handle_collision(&circles[i], &circles[j]);
        }
    }
}

void render_circles(){
    
    SDL_SetRenderDrawColor(renderer, COLOUR_BLACK);
    SDL_RenderClear(renderer);

    for (int i = 0; i < circleCount; i++){
        draw_circle(&circles[i]);
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
