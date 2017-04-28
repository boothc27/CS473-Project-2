#include "Light.h"
#include <iostream>
#include <stdio.h>

Light::Light(int num){
    if (num < 0 || num > 7) {
        printf("ERROR: Light number invalid.  Defaulting to light 0.\n");
        num = 0;
    }
    this->lightNum = GL_LIGHT0 + num;
    this->setPos(Vec3f(0.0, 0.0, 1.0));
    this->disableLight();
    this->makeLocal();
    this->setAmbCol(Vec3f(1.0, 1.0, 1.0));
    this->setDiffCol(Vec3f(1.0, 1.0, 1.0));
    this->setSpecCol(Vec3f(1.0, 1.0, 1.0));
    this->setRadialAtten(Vec3f(1.0, 0.0, 0.0));
}

void Light::makeLocal() {
    this->localLight = true;
    GLfloat posArray[] = {this->pos.x, this->pos.y, this->pos.z, (GLfloat)this->localLight};
    glLightfv(this->lightNum, GL_POSITION, posArray);
}

void Light::makeInfDist() {
    this->localLight = false;
    GLfloat posArray[] = {this->pos.x, this->pos.y, this->pos.z, (GLfloat)this->localLight};
    glLightfv(this->lightNum, GL_POSITION, posArray);
}

void Light::enableLight() {
    this->enabled = true;
    glEnable(this->lightNum);
}

void Light::disableLight() {
    this->enabled = false;
    glDisable(this->lightNum);
}

void Light::setPos(Vec3f newPos) {
    this->pos = newPos;
    this->setLight();
}

void Light::changePos(Vec3f deltaPos) {
    this->pos.x += deltaPos.x;
    this->pos.y += deltaPos.y;
    this->pos.z += deltaPos.z;
    this->setLight();
}

void Light::setRadialAtten(Vec3f newAtten) {
    this->radAtten = newAtten;
    glLightf(this->lightNum, GL_CONSTANT_ATTENUATION, this->radAtten.x);
    glLightf(this->lightNum, GL_LINEAR_ATTENUATION, this->radAtten.y);
    glLightf(this->lightNum, GL_QUADRATIC_ATTENUATION, this->radAtten.z);
}

void Light::setAmbCol(Vec3f newCol) {
    this->ambLight = Vec4f(newCol, 1.0);
    GLfloat colArray[] = {this->ambLight.x, this->ambLight.y, this->ambLight.z, this->ambLight.a};
    glLightfv(this->lightNum, GL_AMBIENT, colArray);
}
void Light::setDiffCol(Vec3f newCol) {
    this->diffLight = Vec4f(newCol, 1.0);
    GLfloat colArray[] = {this->ambLight.x, this->ambLight.y, this->ambLight.z, this->ambLight.a};
    glLightfv(this->lightNum, GL_DIFFUSE, colArray);
}

void Light::setSpecCol(Vec3f newCol) {
    this->specLight = Vec4f(newCol, 1.0);
    GLfloat colArray[] = {this->ambLight.x, this->ambLight.y, this->ambLight.z, this->ambLight.a};
    glLightfv(this->lightNum, GL_SPECULAR, colArray);
}

void Light::drawLight() {
    if (this->localLight) {
        glColor3f(1.0, 1.0, 0.0);
        GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, yellow);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(this->pos.x, this->pos.y, this->pos.z);
        glutWireCube(0.1);
        glPopMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, black);
    }
}

void Light::setLight() {
    GLfloat lightArray[] = {this->pos.x, this->pos.y, this->pos.z, (GLfloat)this->localLight};
    glLightfv(this->lightNum, GL_POSITION, lightArray);
}
