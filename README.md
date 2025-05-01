# screensaver_moving_logo_widget
TouchGFX widget for contest.
Moves a logo over the entire display. Bounces against the edges of the display.

# How to use
in the export folder you can find the .tpkg file. You can import that in your TouchGFX project.
If you add the widget anywhere to a screen it will automatically adjust itself to the screen size.

# Status of code

The code work (tested on STM32H735G and in simulator), but there are several features I would like to add:
- ability to hide widget and disable the animation to save resources
- configure speed of animation from user application
- configure framerate of hardware so that speed of animation on hardware matches that of simulation
- callback on bounce so image can be changed on bounce
- random start location and direction (the hardware would need a random source for the seed of the PRNG or would need to have a true hardware RNG)


