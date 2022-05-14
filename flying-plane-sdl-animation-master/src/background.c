#include "animation.h"
#include "background.h"

bool Background_load(SDL_Renderer *renderer, Background *background, const char *file)
{
    return Image_load(renderer, &background->image, file);
}

void Background_destroy(Background *background)
{
    Image_destroy(&background->image);
}

void Background_move(Background *background, int framerate, Animation *animation)
{
    background->image.rect.x -= background->speed / framerate;
       if(background->image.rect.x <= - background->image.rect.w)
       {background->image.rect.x = 0;
        animation->score ++;}
}


void Background_render(SDL_Renderer *renderer, Background *background, int width, int height)
{
    // Unused height
        (void) height;

        SDL_Rect crop = background->image.rect;

        if(background->direction == DIRECTION_RIGHT )
        {
            int remaining = background->image.rect.w + background->image.rect.x;

            if(background->image.rect.x > - background->image.rect.w )
            {
                crop.x = - background->image.rect.x;
                crop.w = (remaining > width) ? width : remaining;


                SDL_Point pos = {0, 0 };
                Image_renderCrop(renderer, &background->image, &crop, &pos);
            }

            if(remaining < width)
            {
                crop.x = 0;
                crop.w = width - remaining;

                SDL_Point pos = { remaining, 0 };
                Image_renderCrop(renderer, &background->image, &crop, &pos);
            }
        }
}
