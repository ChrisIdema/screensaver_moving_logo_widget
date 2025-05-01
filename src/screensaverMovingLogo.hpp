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

    void setImage(const Bitmap& bmp);
    void registerBounceCallback();
    //void setRandomSeed();
    //void setFrameRate();

protected:

    float x, y;
    float speed;

    float vectorX;
    float vectorY;
};

#endif // SCREENSAVERMOVINGLOGO_HPP
