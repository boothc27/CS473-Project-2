#include "Vec4f.h"

Vec4f::Vec4f() {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
    this->a = 0.0;
}

Vec4f::Vec4f(Vec3f vec3, GLfloat ia) {
    this->x = vec3.x;
    this->y = vec3.y;
    this->z = vec3.z;
    this->a = a;
}

GLfloat *Vec4f::toGLF() {
    static GLfloat fArray [] = {this->x, this->y, this->z, this->a};
    return fArray;
}


Vec4f::Vec4f(GLfloat ix, GLfloat iy, GLfloat iz, GLfloat ia) {
    this->x = ix;
    this->y = iy;
    this->z = iz;
    this->a = ia;
}


