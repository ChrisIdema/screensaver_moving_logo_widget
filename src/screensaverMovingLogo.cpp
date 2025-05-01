#include <gui/containers/screensaverMovingLogo.hpp>

#include <stdlib.h>     // srand, rand
#include <time.h>       // time() 
#include <math.h>

screensaverMovingLogo::screensaverMovingLogo()
{
    speed = 240;
}

void screensaverMovingLogo::initialize()
{
    screensaverMovingLogoBase::initialize();

#ifdef SIMULATOR
    srand(unsigned int(time(nullptr)));
#endif

    int image_width = logo.getWidth();
    int image_height = logo.getHeight();

    int screen_width = touchgfx::HAL::DISPLAY_WIDTH;
    int screen_height = touchgfx::HAL::DISPLAY_HEIGHT;

    int max_x = (screen_width - image_width - 1);
    int max_y = (screen_height - image_height - 1);

    setPosition(0, 0, screen_width, screen_height); // set widget equal to screen size to make it screen filling


    ////random initial position:
    //x = rand() % (screen_width - image_width-2) + 1;
    //y = rand() % (screen_height - image_height-2) + 1;

    // center initial position
    x = float((screen_width - image_width) / 2);
    y = float((screen_height - image_height) / 2);

    logo.setXY(int(x), int(y));

    float x_old = x;
    float y_old = y;

    //speedX= speed * (1 - (rand()&1)*2);
    //speedY;

    //float angle = (rand() % 700) * 0.1f + 10.0f;
    //angle += (rand() % 3) * 90;
    //float radians = angle * (PI / 180);    
    //vectorX = cosf(radians) * (screen_height + screen_width); // make vector longer than diagonal to simplify intersection calculation
    //vectorY = sinf(radians) * (screen_height + screen_width); // make vector longer than diagonal to simplify intersection calculation

    vectorX = 1.0f * (screen_height + screen_width); // make vector longer than diagonal to simplify intersection calculation
    vectorY = 1.0f * (screen_height + screen_width); // make vector longer than diagonal to simplify intersection calculation

    x = x_old + vectorX;
    y = y_old + vectorY;

    float scale;

    if (x >= screen_width - image_width)
    {
        x = float(screen_width - image_width - 1);   
        scale = (x - x_old) / vectorX;
        vectorX *= scale;
        vectorY *= scale;
        y = y_old + vectorY;
    }
    else if (x < 0)
    {
        x = 0;
        scale = (x - x_old) / vectorX;
        vectorX *= scale;
        vectorY *= scale;
        y = y_old + vectorY;
    }


    if (y >= screen_height - image_height)
    {
        y = float(screen_height - image_height - 1);
        scale = (y - y_old) / vectorY;
        vectorX *= scale;
        vectorY *= scale;
        x = x_old + vectorX;
    }
    else if (y < 0)
    {
        y = 0;
        scale = (y - y_old) / vectorY;
        vectorX *= scale;
        vectorY *= scale;
        x = x_old + vectorX;
    }

    x = roundf(x);
    x = roundf(x);

    // calculate distance relative to width to allow constant speed
   // todo find an approximation without using sqrt
    //float distance = sqrtf((x_old - x) * (x_old - x) + (y_old - y) * (y_old - y)) / max_x;
    float distance = (fabsf(x_old - x) + fabsf(y_old - y)) / max_x; //manhattan distance


    logo.startMoveAnimation(int(x), int(y), int(speed * distance));

}


void screensaverMovingLogo::handleTickEvent()
{
    if (!logo.isMoveAnimationRunning())
    {
        int screen_width = touchgfx::HAL::DISPLAY_WIDTH;
        int screen_height = touchgfx::HAL::DISPLAY_HEIGHT;

        int image_width = logo.getWidth();
        int image_height = logo.getHeight();

        int max_x = (screen_width - image_width - 1);
        int max_y = (screen_height - image_height - 1);

        float x_old = x;
        float y_old = y;

        // bounce logic:
        if (x == 0 || x == max_x)
        {
            vectorX *= -1;
        }
        if (y == 0 || y == max_y)
        {
            vectorY *= -1;
        }


        // make vector longer than diagonal to simplify intersection calculation
        if ((vectorX* vectorX + vectorY* vectorY) < (max_x * max_x + max_y * max_y))
        {
            float scale = (max_x * max_x + max_y * max_y) / (vectorX * vectorX + vectorY * vectorY);
            vectorX = vectorX * scale;
            vectorY = vectorY * scale;
        }

        
        x = x_old + vectorX;
        y = y_old + vectorY;


        //scale vector so it intersects with 1 or 2 edges:
        float scale;

        if (x > max_x)
        {
            x = float(max_x);
            scale = (x - x_old) / vectorX;
            vectorX *= scale;
            vectorY *= scale;
            y = y_old + vectorY;
        }
        else if (x < 0)
        {
            x = 0;
            scale = (x - x_old) / vectorX;
            vectorX *= scale;
            vectorY *= scale;
            y = y_old + vectorY;
        }

        if (y > max_y)
        {
            y = float(max_y);
            scale = (y - y_old) / vectorY;
            vectorX *= scale;
            vectorY *= scale;
            x = x_old + vectorX;
        }
        else if (y < 0)
        {
            y = 0;
            scale = (y - y_old) / vectorY;
            vectorX *= scale;
            vectorY *= scale;
            x = x_old + vectorX;
        }

        x = roundf(x);
        x = roundf(x);

        // calculate distance relative to width to allow constant speed
        //float distance = sqrtf((x_old - x) * (x_old - x) + (y_old - y) * (y_old - y)) / max_x;

        float distance = (fabsf(x_old - x) + fabsf(y_old - y)) / max_x; //manhattan distance



        logo.startMoveAnimation(int(x), int(y), int(speed * distance));

    }
}

