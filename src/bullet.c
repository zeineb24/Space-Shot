#include "bullet.h"
#include "animation.h"


bool Bullet_load(SDL_Renderer *renderer, Bullet *bullet, const char *image )
{
    // Load bullet image
    if(!Image_load(renderer, &bullet->image, image))
    {
        return false;
    }
    return true;
}

void Bullet_destroy(Bullet *bullet)
{
    Image_destroy(&bullet->image);

}
void Bullet_setX(Bullet *bullet, int x)
{
    // Bullet x coordinate
    bullet->image.rect.x = x;


}

void Bullet_setY(Bullet *bullet, int y)
{
    // bullet y coordinate
    bullet->image.rect.y = y;

}

void Bullet_setCoordinates(Bullet *bullet, int x, int y)
{
    Bullet_setX(bullet, x);
    Bullet_setY(bullet, y);
}
void Bullet_moveX(Bullet *bullet, int x)
{
    Bullet_setX(bullet,bullet->image.rect.x + x);
}



void Bullet_move(Bullet *bullet, int framerate,Animation *animation)
{
    int bulletStep = bullet->speed / framerate;

        Bullet_moveX(bullet, bulletStep);
       for(int i = 0; i < ENEMY_NUM; i++)
       {if(bullet->image.rect.x + bullet->image.rect.w > animation->enemy[i].image.rect.x
            && animation->enemy[i].image.rect.x > bullet->image.rect.x
            && bullet->image.rect.y + bullet->image.rect.h > animation->enemy[i].image.rect.y
            &&  animation->enemy[i].image.rect.y > bullet->image.rect.y ) {
     animation->enemy[i].lives = animation->enemy[i].lives - 1;
        Bullet_destroy(bullet);
   }
        if (animation->enemy[i].lives == 0){
            Enemy_detsroy(animation->enemy[i]   );
            animation->score = animation->score + 100;
        }}


}


void Bullet_setDirection(Bullet *bullet, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_SPACE:
        bullet->direction &= ~DIRECTION_LEFT;
        bullet->direction |= DIRECTION_RIGHT;
        break;

    }
}

void Bullet_unsetDirection(Bullet *bullet, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_UP:
        bullet->direction &= ~DIRECTION_UP;
        break;

    case SDLK_DOWN:
        bullet->direction &= ~DIRECTION_DOWN;
        break;


    }
}


void Bullet_render(SDL_Renderer *renderer, Bullet *bullet)
{
    ;

    // Render bullet
    Image_render(renderer, &bullet->image);
}
