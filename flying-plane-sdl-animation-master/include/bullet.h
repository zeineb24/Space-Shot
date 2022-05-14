#ifndef BULLET_H
#define BULLET_H

#include "utils.h"
#include "image.h"

typedef struct Animation Animation;

struct Bullet
{
    // Plane
    Image image;

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    bool shown;
};
typedef struct Bullet Bullet;


bool Bullet_load(SDL_Renderer *renderer, Bullet *bullet, const char *image );
void Bullet_destroy(Bullet *bullet);
void Bullet_setX(Bullet *bullet, int x);
void Bullet_setY(Bullet *bullet, int y);
void Bullet_setCoordinates(Bullet *bullet, int x, int y);

void Bullet_moveX(Bullet *bullet, int x);

void Bullet_move(Bullet *bullet, int framerate,Animation *animation); //, int screenWidth
void Bullet_setDirection(Bullet *bullet, SDL_Keycode keycode);
void Bullet_render(SDL_Renderer *renderer, Bullet *bullet);

#endif // BULLET_H
