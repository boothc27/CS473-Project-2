#ifndef VEC3F_H
#define VEC3F_H

#include "GL/freeglut.h"

// Simple class for a tuple of three GLfloats
class Vec3f
{
    public:
        Vec3f();
        Vec3f(GLfloat x, GLfloat y, GLfloat z);

        GLfloat x;
        GLfloat y;
        GLfloat z;

    protected:

    private:
};

#endif // VEC3F_H
