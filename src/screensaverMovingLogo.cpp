#include <gui/containers/screensaverMovingLogo.hpp>

#include <stdlib.h>     // srand, rand
#include <time.h>       // time() 
#include <math.h>

screensaverMovingLogo::screensaverMovingLogo()
{

}

void screensaverMovingLogo::initialize()
{
    screensaverMovingLogoBase::initialize();

#ifdef SIMULATOR
    std::srand(unsigned int(time(nullptr)));
#endif

    int image_width = logo.getWidth();
    int image_height = logo.getHeight();

    //touchgfx::HAL::

    //int screen_width = touchgfx::HAL::getInstance()->DISPLAY_WIDTH;
    int screen_width = touchgfx::HAL::DISPLAY_WIDTH;
    int screen_height = touchgfx::HAL::DISPLAY_HEIGHT;

    setPosition(0, 0, screen_width, screen_height); // widget equal to screen size

    //setWidth(screen_width);
    //setHeight(screen_height);

    //random initial position:
    x = rand() % (screen_width - image_width-2) + 1;
    y = rand() % (screen_height - image_height-2) + 1;

    x = (screen_width - image_width) / 2;
    y = (screen_height - image_height) / 2;

    logo.setXY(x, y);


    speed=1;
    //speedX= speed * (1 - (rand()&1)*2);
    //speedY;

    float angle = (rand() % 700) * 0.1f + 10.0f;
    angle += (rand() % 3) * 90;

    float radians = angle * (PI / 180);

    vectorX = cosf(radians) * 1000;
    vectorY = sinf(radians) * 1000;

    destX = x + vectorX;
    destY = y + vectorY;

    float scale;

    if (destX >= screen_width - image_width)
    {
        destX = float(screen_width - image_width - 1);   
        scale = (destX - x) / vectorX;
        vectorX *= scale;
        vectorY *= scale;
        destY = y + vectorY;
    }
    else if (destX < 0)
    {
        destX = 0;
        scale = (destX - x) / vectorX;
        vectorX *= scale;
        vectorY *= scale;
        destY = y + vectorY;
    }


    if (destY >= screen_height - image_height)
    {
        destY = float(screen_height - image_height - 1);
        scale = (destY - y) / vectorY;
        vectorX *= scale;
        vectorY *= scale;
        destX = x + vectorX;
    }
    else if (destY < 0)
    {
        destY = 0;
        scale = (destY - y) / vectorY;
        vectorX *= scale;
        vectorY *= scale;
        destX = x + vectorX;
    }

    destX = roundf(destX);
    destY = roundf(destY);

    float distance = sqrtf((x - destX) * (x - destX) + (y - destY) * (y - destY)) / screen_width;



    logo.startMoveAnimation(int(destX), int(destY), int(120 * distance));

}


void screensaverMovingLogo::handleTickEvent()
{
    if (!logo.isMoveAnimationRunning())
    {
        int screen_width = touchgfx::HAL::DISPLAY_WIDTH;
        int screen_height = touchgfx::HAL::DISPLAY_HEIGHT;

        int image_width = logo.getWidth();
        int image_height = logo.getHeight();

        x = int(destX);
        y = int(destY);

        if (x == 0 || x == (screen_width- image_width -1))
        {
            vectorX *= -1;
        }

        if (y == 0 || y == (screen_height - image_height - 1))
        {
            vectorY *= -1;
        }

        vectorX = vectorX * 1000;
        vectorY = vectorY * 1000;


        destX = x + vectorX;
        destY = y + vectorY;

        float scale;


        if (destX >= screen_width - image_width)
        {
            destX = float(screen_width - image_width - 1);
            scale = (destX - x) / vectorX;
            vectorX *= scale;
            vectorY *= scale;
            destY = y + vectorY;
        }
        else if (destX < 0)
        {
            destX = 0;
            scale = (destX - x) / vectorX;
            vectorX *= scale;
            vectorY *= scale;
            destY = y + vectorY;
        }


        if (destY >= screen_height - image_height)
        {
            destY = float(screen_height - image_height - 1);
            scale = (destY - y) / vectorY;
            vectorX *= scale;
            vectorY *= scale;
            destX = x + vectorX;
        }
        else if (destY < 0)
        {
            destY = 0;
            scale = (destY - y) / vectorY;
            vectorX *= scale;
            vectorY *= scale;
            destX = x + vectorX;
        }

        destX = roundf(destX);
        destY = roundf(destY);

        float distance = sqrtf((x - destX) * (x - destX) + (y - destY) * (y - destY)) / screen_width;



        logo.startMoveAnimation(int(destX), int(destY), int(120 * distance));
    }
}

