//  --  //  --  //  --  //  Helpers.cpp   //  --  //  --  //  --  //
#include "Helpers.h"
#include <cmath>

using namespace std;


double toRadians(double degrees) {
    return (degrees / 180.0) * 3.14159;
}

double normalizeDeg(double degrees) {
    while (degrees > 360.0) degrees -= 360.0;
    while (degrees < 0.0) degrees += 360.0;
    return degrees;
}

double truncate(double amt, int dec) {
    amt *= pow(10, dec);
    amt = trunc(amt);
    return amt / pow(10, dec);
}

void drawStringBitmap(double drawX, double drawY, string drawStr,
                      void* font) {
    glRasterPos2f(drawX, drawY);// Position to start drawing in world coordinates
    for (unsigned int i = 0; i < drawStr.size(); i++)
        glutBitmapCharacter(font, drawStr[i]);

    // NOTE: Since these are bitmapped fonts, they will always show up as the
    // same size on the screen
}

void drawStringStroke(string drawStr, void* font) {
    for (unsigned int i = 0; i < drawStr.size(); i++)
        glutStrokeCharacter(font, drawStr[i]);
}
