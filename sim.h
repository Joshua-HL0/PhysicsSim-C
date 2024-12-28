#ifndef SIM_H
#define SIM_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400
#define COLOUR_WHITE 0xff, 0xff, 0xff, 0xff
#define COLOUR_BLACK 0x00, 0x00, 0x00, 0x00

#define MAX_CIRCLES 10

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

void new_circle(double x, double y, double radius);
void draw_circle(Circle *circle);
void update_circles();


#endif
