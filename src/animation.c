 /*
 * Copyright (c) 2018 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include "animation.h"

bool Animation_start(SDL_Renderer *renderer, int width, int height)
{
    Animation animation = {0};
    animation.renderer  = renderer;
    animation.width     = width;
    animation.height    = height;
    animation.plane.lives = 3;
    animation.score=0;
    animation.score=10;


    // Loat animation assets
    if(!Animation_load(&animation))
        return false;


    // Initialize framerate manager : 30 FPS
    FPSmanager fpsmanager;
    SDL_initFramerate(&fpsmanager);
    SDL_setFramerate(&fpsmanager, 60);

    // Initialize start frame
    int frame = SDL_getFramecount(&fpsmanager);


    // Event loop exit flag
    bool quit = false;

    // Event loop
    while(!quit)
    {
        SDL_Event e;

        // Get available event
        while(SDL_PollEvent(&e))
        {
            // Handle animation events
            quit = Animation_handleEvent(&animation, &e);

        }

        // Each new frame
        int currentFrame = SDL_getFramecount(&fpsmanager);
        if(currentFrame != frame)
        {
            // Update animation frame
            Animation_update(&animation, SDL_getFramerate(&fpsmanager));

            currentFrame = frame;
        }

        // Render animation
        Animation_render(&animation);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay
        SDL_framerateDelay(&fpsmanager);
    }

    Animation_destroy(&animation);

    printf("%d",animation.score );

    return true;
}

bool Animation_load(Animation *animation)
{
    // Load the ocean image
    if(!Background_load(animation->renderer, &animation->background, OCEAN_IMG))
        return false;

    // Background move direction
    animation->background.direction = DIRECTION_RIGHT;

    // Background speed in pixel/second
    animation->background.speed = OCEAN_SPEED;

    if(!Plane_load(animation->renderer, &animation->plane, PLANE_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->plane.margin = PLANE_MARGIN;


    // Set plane initial position
    Plane_setX(&animation->plane, (animation->width - animation->plane.image.rect.w) / 50);
    Plane_setY(&animation->plane, (animation->height - animation->plane.image.rect.h - animation->plane.margin)/2);

    // Plane move direction
    animation->plane.direction = DIRECTION_STOP;

    // Plane move speed in pixel/second
    animation->plane.speed = PLANE_SPEED;


    animation->currentenemy=-1;
    for(int i=0; i< ENEMY_NUM; i++ )
    {if(!Enemy_load(animation->renderer, &animation->enemy[i],ENEMY_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }
    animation->enemy[i].lives = 2;
     animation->enemy[i].margin = ENEMY_MARGIN;




// Plane move direction
  animation->enemy[i].direction = DIRECTION_STOP;

// Plane move speed in pixel/second
     animation->enemy[i].speed = ENEMY_SPEED;
     animation->enemy[i].shown = false;
    }




      animation->currentbullet=-1;
    for(int i = 0; i < BULLET_NUM; i++)
    {
        if(!Bullet_load(animation->renderer, &animation->bullet[i], BULLET_IMG))
         {
             Background_destroy(&animation->background);
             return false;
         }


         // Bullet move direction
         animation->bullet[i].direction = DIRECTION_STOP;

         // Bullet move speed in pixel/second
         animation->bullet[i].speed = BULLET_SPEED;

         animation->bullet[i].shown = false;




    }




    return true;
}

void Animation_destroy(Animation *animation)
{for(int i = 0; i < BULLET_NUM; i++)
    {Bullet_destroy(&animation->bullet[i]);}
    Plane_destroy(&animation->plane);
 for(int i=0; i< ENEMY_NUM; i++ )
   { Enemy_destroy(&animation->enemy[i]);}

    Background_destroy(&animation->background);
}

bool Animation_handleEvent(Animation *animation, SDL_Event *e)
{
    bool quit = false;

    // User requests quit
    if(e->type == SDL_QUIT)
    {
        quit = true;
    }
    else if(e->type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            quit = true;
            break;

        case SDLK_UP:
        case SDLK_DOWN:

            Plane_setDirection(&animation->plane, e->key.keysym.sym);
            break;
        case SDLK_SPACE:

               {
animation->currentbullet ++;
                    if( animation->currentbullet == BULLET_NUM ) // All bullet are shown
                    {
                        animation->currentbullet = 0;
                    }

                    animation->bullet[animation->currentbullet].shown = true;
                    Bullet_setDirection(&animation->bullet[animation->currentbullet], SDLK_SPACE);

                    // Set Bullet initial position
                    Bullet_setX(&animation->bullet[animation->currentbullet], animation->plane.image.rect.x);
                    Bullet_setY(&animation->bullet[animation->currentbullet],animation->plane.image.rect.y );

                    break;}


        }
    }
        else if(e->type == SDL_KEYUP)
        {
            switch (e->key.keysym.sym)
            {
            case SDLK_UP:
            case SDLK_DOWN:


                Plane_unsetDirection(&animation->plane, e->key.keysym.sym);

                break;

            }
    }if (animation->score > animation->scoreobjectif){
    animation->currentenemy ++;

    if( animation->currentenemy == ENEMY_NUM ) // All enemies are shown
    {
        animation->currentenemy = 0;
    }
    animation->enemy[animation->currentenemy].shown = true;

    Enemy_setDirection(&animation->enemy[animation->currentenemy]);
    // Set enemy initial position

    Enemy_setX(&animation->enemy[animation->currentenemy], 900+(rand()%300));
    Enemy_setY(&animation->enemy[animation->currentenemy], (animation->height - animation->enemy[animation->currentenemy].image.rect.h - animation->enemy[animation->currentenemy].margin)*(rand()/(double)RAND_MAX));
    animation->scoreobjectif = animation->score +10 ;
    }
    return quit;
}

void Animation_update(Animation *animation, int framerate)
{
    // Move ocean
    Background_move(&animation->background, framerate, animation);

    // Move plane
    Plane_move(&animation->plane,  animation->width, animation->height, framerate);

    // Move enemy
for(int i = 0; i < ENEMY_NUM; i++)
{Enemy_move(&animation->enemy[i], animation, framerate);}


    // Move bullet
    for(int i = 0; i < BULLET_NUM; i++)
    {Bullet_move(&animation->bullet[i], framerate,animation);}

    //, animation->width

}

void Animation_render(Animation *animation)
{
    // Render ocean
    Background_render(animation->renderer, &animation->background, animation->width, animation->height);

    // Render plane
    Plane_render(animation->renderer, &animation->plane);

    // Render enemy
    for(int i = 0; i < ENEMY_NUM; i++)
  { Enemy_render(animation->renderer, &animation->enemy[i]);}



    // Render bullet
   for(int i = 0; i < BULLET_NUM; i++){if(animation->bullet[i].shown == true)

       Bullet_render(animation->renderer, &animation->bullet[i]);}

}
