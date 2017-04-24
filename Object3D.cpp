//  --  //  --  //  --  //  Object3D.cpp   //  --  //  --  //  --  //
#include "Object3D.h"
#include "GL/freeglut.h"

Object3D::Object3D() {}

void Object3D::moveTo(double newX, double newY, double newZ) {
    this->pos.x = newX;
    this->pos.y = newY;
    this->pos.z = newZ;
}

void Object3D::moveTo(Vec3d newPos) {
    this->pos = newPos;
}

void Object3D::rotateX(double theta) {this->orientation.x = theta;}
void Object3D::rotateY(double theta) {this->orientation.y = theta;}
void Object3D::rotateZ(double theta) {this->orientation.z = theta;}
void Object3D::rotateByX(double dTheta) {this->orientation.x += dTheta;}
void Object3D::rotateByY(double dTheta) {this->orientation.y += dTheta;}
void Object3D::rotateByZ(double dTheta) {this->orientation.z += dTheta;}

void defaultDraw() {
        glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1);
        glVertex3f(0, 1.0, 1);
        glVertex3f(0, 1.0, 0);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1.0, 0);
        glVertex3f(1.0, 1.0, 0);
        glVertex3f(1.0, 0, 0);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(1, 0, 0);
        glVertex3f(1, 1.0, 0);
        glVertex3f(1, 1.0, 1.0);
        glVertex3f(1, 0, 1.0);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 0.5);
        glVertex3f(0, 1.0, 0);
        glVertex3f(0, 1.0, 1);
        glVertex3f(1.0, 1.0, 1);
        glVertex3f(1.0, 1.0, 0);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(0, 0.0, 0);
        glVertex3f(0, 0.0, 1);
        glVertex3f(1.0, 0, 1);
        glVertex3f(1.0, 0, 0);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.9, 0.9, 0.9);
        glVertex3f(0, 0, 1);
        glVertex3f(0, 1.0, 1);
        glVertex3f(1.0, 1, 1);
        glVertex3f(1, 0, 1);
        glEnd();
}

void Object3D::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        // Apply OpenGL transformations here
        glTranslated(this->pos.x, this->pos.y, this->pos.z);
        glRotated(this->orientation.x, 1, 0, 0);
        glRotated(this->orientation.y, 0, 1, 0);
        glRotated(this->orientation.z, 0, 0, 1);
        defaultDraw();
    glPopMatrix();
}

Vec3d Object3D::getPos() {
    return this->pos;
}
