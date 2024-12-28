#ifndef SIM_H
#define SIM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400
#define COLOUR_WHITE 0xff, 0xff, 0xff, 0xff
#define COLOUR_BLACK 0x00, 0x00, 0x00, 0x00

#define MAX_CIRCLES 10
#define DEFAULT_RADIUS 50

typedef struct {
    double x;
    double y;
} Velocity;

typedef struct {
    Velocity velocity;
    int x;
    int y;
    int radius;
} Circle;

Circle circles[MAX_CIRCLES];
int circleCount = 0;
SDL_Renderer *renderer;

void new_circle(int x, int y, int radius);
void draw_circle(Circle *circle);
void update_circles();
void render_circles();

void handle_click(SDL_MouseButtonEvent *e);


#endif
