#include "enemy.h"
#include "animation.h"

bool Enemy_load(SDL_Renderer *renderer, Enemy *enemy, const char *image )
{
    // Load plane image
    if(!Image_load(renderer, &enemy->image, image))
    {
        return false;
    }



    return true;
}

void Enemy_destroy(Enemy *enemy)
{
    Image_destroy(&enemy->image);

}

void Enemy_setX(Enemy *enemy, int x)
{
    // Enemy x coordinate
    enemy->image.rect.x = x;


}

void Enemy_setY(Enemy *enemy, int y)
{
    // Enemy y coordinate
    enemy->image.rect.y = y;


}

void Enemy_setCoordinates(Enemy *enemy, int x, int y)
{
    Enemy_setX(enemy, x);
    Enemy_setY(enemy, y);
}

void Enemy_moveX(Enemy *enemy, int x)
{
    Enemy_setX(enemy, enemy->image.rect.x + x);
}

void Enemy_moveY(Enemy *enemy, int y)
{
    Enemy_setY(enemy, enemy->image.rect.y + y);
}

void Enemy_setDirection(Enemy *enemy)//, SDL_Keycode keycode)
{

        enemy->direction &= ~DIRECTION_RIGHT;
        enemy->direction |= DIRECTION_LEFT;


}

void Enemy_unsetDirection(Enemy *enemy, SDL_Keycode keycode)
{
    switch (keycode)
    {

    case SDLK_RIGHT:
        enemy->direction &= ~DIRECTION_RIGHT;
        break;

    case SDLK_LEFT:
        enemy->direction &= ~DIRECTION_LEFT;
        break;
    }
}

void Enemy_render(SDL_Renderer *renderer, Enemy *enemy)
{



    // Render enemy
    Image_render(renderer, &enemy->image);
}

void Enemy_move(Enemy *enemy,Animation *animation, int framerate)
{
    int enemyStep = enemy->speed / framerate;


        Enemy_moveX(enemy, -enemyStep);
        if (    enemy->image.rect.x - enemy->image.rect.w < animation->plane.image.rect.x
                && animation->plane.image.rect.x < enemy->image.rect.x
                && enemy->image.rect.y + enemy->image.rect.h < animation->plane.image.rect.y
                &&  animation->plane.image.rect.y < enemy->image.rect.y)
             { animation->plane.lives = animation->plane.lives - 1;

        Enemy_setX(enemy, 900+(rand()%300));

        printf("detected");}


}

