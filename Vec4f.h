#ifndef VEC4F_H
#define VEC4F_H

#include "GL/freeglut.h"
#include "Vec3f.h"

// Simple class for a tuple of four GLfloats
class Vec4f
{
    public:
        Vec4f();
        Vec4f(Vec3f vec3, GLfloat a);
        Vec4f(GLfloat x, GLfloat y, GLfloat z, GLfloat a);

        GLfloat *toGLF();

        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat a;

    protected:

    private:
};

#endif // VEC4F_H
