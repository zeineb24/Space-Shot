#ifndef ENEMY_H
#define ENEMY_H


#include "utils.h"
#include "image.h"
typedef struct Animation Animation;

struct Enemy
{
    // Enemy
    Image image;



    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    bool shown;

    // Lives
    int lives;
};
typedef struct Enemy Enemy;


bool Enemy_load(SDL_Renderer *renderer, Enemy *enemy, const char *image);
void Enemy_destroy(Enemy *enemy);

void Enemy_setX(Enemy *enemy, int x);
void Enemy_setY(Enemy *enemy, int y);
void Enemy_setCoordinates(Enemy *enemy, int x, int y);

void Enemy_moveX(Enemy *enemy, int x);
void Enemy_moveY(Enemy *enemy, int y);

void Enemy_move(Enemy *enemy, Animation *animation, int framerate);
void Enemy_setDirection(Enemy *enemy);//, SDL_Keycode keycode);

void Enemy_unsetDirection(Enemy *enemy, SDL_Keycode keycode);


void Enemy_render(SDL_Renderer *renderer, Enemy *enemy);


#endif // ENEMY_H
