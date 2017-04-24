//  --  //  --  //  --  //  Helpers.h   //  --  //  --  //  --  //
#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <GL/freeglut.h>


double toRadians(double degrees);       // Converts degrees to radians
double normalizeDeg(double degrees);    // Keeps degrees between 0-360
double truncate(double amt, int dec);   // Rounds down at a given decimal place

void drawStringBitmap(double drawX, double drawY, std::string drawStr,
                      void* font=GLUT_BITMAP_9_BY_15);
void drawStringStroke(std::string drawStr, void* font=GLUT_STROKE_ROMAN);

#endif // HELPERS_H
