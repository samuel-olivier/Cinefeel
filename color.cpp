#include <QtMath>
#include "color.h"

Color::Color()
{
}

int Color::distance(int r, int g, int b) {
    return qAbs(red - r) + qAbs(green - g) + qAbs(blue - b);
}
