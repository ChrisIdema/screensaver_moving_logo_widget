#ifndef SCREENSAVERMOVINGLOGO_HPP
#define SCREENSAVERMOVINGLOGO_HPP

#include <gui_generated/containers/screensaverMovingLogoBase.hpp>


class screensaverMovingLogo : public screensaverMovingLogoBase
{
public:
    screensaverMovingLogo();
    virtual ~screensaverMovingLogo() {}

    virtual void initialize();

    virtual void handleTickEvent();

    void setImage();
    void registerBounceCallback();
    void setRandomSeed();

    void setFrameRate();

protected:

    int x, y;
    float speed;
    //float speedX;
    //float speedY;

    float destX;
    float destY;


    float vectorX;
    float vectorY;

};

#endif // SCREENSAVERMOVINGLOGO_HPP
