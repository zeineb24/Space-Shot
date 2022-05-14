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

#ifndef ANIMATION_H
#define ANIMATION_H

#include "utils.h"
#include "plane.h"
#include "background.h"
#include "bullet.h"
#include "enemy.h"

#define ENEMY_IMG       "assets/enemy.png"
#define ENEMY_SPEED     250
#define ENEMY_MARGIN    20

#define PLANE_IMG       "assets/character.png"
#define PLANE_SPEED     250
#define PLANE_MARGIN    20

#define BULLET_IMG      "assets/bullet.png"
#define BULLET_SPEED     450
#define BULLET_MARGIN    5

#define OCEAN_IMG       "assets/background.jpg"
#define OCEAN_SPEED     220

#define BULLET_NUM      6

#define ENEMY_NUM      8


struct Animation
{
    // Animation screen dimensions
    int width;
    int height;

    // Animation renderer
    SDL_Renderer *renderer;

    // Background and Plane
    Background background;
    Plane plane;
    Bullet bullet[BULLET_NUM];
    int currentbullet;

    // enemies
    Enemy enemy[ENEMY_NUM];
    int currentenemy;

    // score
    int score;
    int scoreobjectif;
};
typedef struct Animation Animation;


bool Animation_start(SDL_Renderer *renderer, int width, int height);

bool Animation_load(Animation *animation);
void Animation_destroy(Animation *animation);

bool Animation_handleEvent(Animation *animation, SDL_Event *e);
void Animation_update(Animation *animation, int framerate);
void Animation_render(Animation *animation);

#endif // ANIMATION_H
