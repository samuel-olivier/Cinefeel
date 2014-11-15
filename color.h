#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
    Color();
    int red, green, blue;

    int distance(int r, int g, int b);
};

#endif // COLOR_H
