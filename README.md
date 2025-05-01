# screensaver_moving_logo_widget
TouchGFX widget for contest.
Moves a logo over the entire display. Bounces against the edges of the display.

# Status of code

The code works, but there are several features I would like to add:
- configure speed of animation from user application
- configure framerate of hardware so that speed of animation on hardware matches that of simulation
- callback on bounce so image can be changed on bounce
- random start location and direction (the hardware would need a random source for the seed of the PRNG or would need to have a true hardware RNG)


