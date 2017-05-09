//  --  //  --  //  --  //  Camera.cpp   //  --  //  --  //  --  //
#include <cmath>
#include "stdio.h"
#include "GL/freeglut.h"
#include "Helpers.h"
#include "Camera.h"

Camera::Camera(){
    this->moveCameraTo(Vec3d(5.0, 5.0, 5.0));
    this->cameraLookAt(Vec3d(0.0, 0.0, 0.0));
    this->setFOV(90.0);
    this->setClip(0.1, 100.0);
    this->setUpVec(Vec3d(0.0, 1.0, 0.0));
}

void Camera::moveCameraTo(Vec3d newPos) {
    this->pos = newPos;
}

Vec3d Camera::getPos() {return this->pos;}

void Camera::moveCameraBy(Vec3d deltaPos) {
    this->pos.x += deltaPos.x;
    this->pos.y += deltaPos.y;
    this->pos.z += deltaPos.z;
}

void Camera::cameraLookAt(Vec3d lookPos) {
    this->lookAt = lookPos;
}

void Camera::setUpVec(Vec3d newVec) {
    this->upVec = newVec;
}

void Camera::cameraPan(Vec3d lookPos, double azimuth, double dist, double elev) {
    // This function will set the camera's pos and lookAt attributes.
    this->lookAt = lookPos;
    double x = dist*cos(toRadians(azimuth));
    double y = elev;
    double z = dist*sin(toRadians(azimuth));
    this->moveCameraTo(Vec3d(x,y,z));
}

void Camera::cameraTrans(Vec3d deltaPos) {
    this->moveCameraBy(deltaPos);
    this->lookAt.x += deltaPos.x;
    this->lookAt.y += deltaPos.y;
    this->lookAt.z += deltaPos.z;
}

void Camera::setView() {
    this->setAspectByScreen();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(this->camFOV, this->aspectRatio, this->nearClip, this->farClip);
    gluLookAt(this->pos.x, this->pos.y, this->pos.z,
              this->lookAt.x, this->lookAt.y, this->lookAt.z,
              this->upVec.x, this->upVec.y, this->upVec.z);

    glutPostRedisplay();
}

void Camera::setClip(double nearC, double farC) {
    this->nearClip = nearC;
    this->farClip = farC;
}

void Camera::setFOV(double fov) {
    if (fov > 0 && fov <= 180) this->camFOV = fov;
}

Vec3d Camera::getLookAt() {
    return this->lookAt;
}

void Camera::setAspect(double newAspect) {
    this->aspectRatio = newAspect;
}

void Camera::setAspectByScreen() {
    double actualRatio = glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT);
    this->setAspect(actualRatio);
}
