# Snake-on-Arduino-written-in-C

Snake- project on arduino.
The master branch is code that runs on this Wokwi-link: https://wokwi.com/projects/296234816685212169\n

If you want to run it on an Arduino (I use a UNO R3) use the Arduino-master branch instead. 
The horizontal inputs needed to be inverted to properly represent right and left.\n

The setup used is, excluding the arduino:
1 Joystick
2 8x8 led-matrixes\n
and jumpercables.

The code for the led-matrix and joystick comes from aspcodenet on GitHuB and modified by me:
https://github.com/aspcodenet/avrmax72
https://github.com/aspcodenet/avrjoystick

If you want to increase or decrease the speed of the snake, you can change the number of miliiseconds on this delay in main, row 91
"if(millis_get() - millisecondsSinceLastAction > 300)"
