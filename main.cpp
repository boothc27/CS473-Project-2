//  --  //  --  //  --  //  main.cpp   //  --  //  --  //  --  //
/** CS473: Computer Graphics
  * Project 2
  * Modified from ICE Lesson 18: Camera
  * Author: CDT Booth
  */

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdio.h>
#include "Object3D.h"
#include "Camera.h"
#include <GL/glut.h>
#include "GL/freeglut.h"
#include "ImportObject.h"
#include "Helpers.h"

int frameRate = 60;     // Limit on FPS rate
int frameRateMS = 1000 / frameRate;

int windowSize[] = {800, 800};
int lastFrame = 0;

double axisLength = 50.0;

Object3D newObj = Object3D();
ImportObject shark = ImportObject();
ImportObject car = ImportObject();
ImportObject wheel1 = ImportObject();
ImportObject wheel2 = ImportObject();
ImportObject turret = ImportObject();
Camera cam = Camera();
double curAz = 45;
double curDist = 5.0;
double curEle = 5.0;
int prevX, prevY, prevZ = 0;
int dX, dY, dZ = 0;
bool rightMouse = false;
bool middleMouse = false;
bool freeCam = false;

void drawAxis() {

    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);   // Red for X-axis
        glVertex3f(-axisLength, 0, 0);
        glVertex3f(axisLength, 0, 0);

        glColor3f(0.0, 1.0, 0.0);   // Green for Y-axis
        glVertex3f(0, -axisLength, 0);
        glVertex3f(0, axisLength, 0);

        glColor3f(0.0, 0.0, 1.0);   // Blue for Z-axis
        glVertex3f(0, 0, -axisLength);
        glVertex3f(0, 0, axisLength);
    glEnd();
}

void drawHUD() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,2.0,0.0,1.0);
    glViewport(0, windowSize[1] - 200, 200, 200);

    glColor3f(0.5, 0.5, 0.5);
    using namespace std;
    ostringstream txt;
    txt << "R: Reset Camera";
    drawStringBitmap(0.1, 0.65, txt.str(), GLUT_BITMAP_8_BY_13);
    txt.str("");
    txt << "Arrow Keys: Move Turret";
    drawStringBitmap(0.1, 0.55, txt.str(), GLUT_BITMAP_8_BY_13);
    txt.str("");
    txt << "Hold Right Mouse: Pan Camera";
    drawStringBitmap(0.1, 0.45, txt.str(), GLUT_BITMAP_8_BY_13);
    txt.str("");
    txt << "Hold Middle Mouse: Zoom Camera";
    drawStringBitmap(0.1, 0.35, txt.str(), GLUT_BITMAP_8_BY_13);
    txt.str("");
    if (freeCam) {
        txt << "A/D: Move Camera in X";
        drawStringBitmap(0.1, 0.25, txt.str(), GLUT_BITMAP_8_BY_13);
        txt.str("");
        txt << "Q/Z: Move Camera in Y";
        drawStringBitmap(0.1, 0.15, txt.str(), GLUT_BITMAP_8_BY_13);
        txt.str("");
        txt << "W/S: Move Camera in Z";
        drawStringBitmap(0.1, 0.05, txt.str(), GLUT_BITMAP_8_BY_13);
        txt.str("");
    }
    else {
        txt << "WASD: Pan Camera";
        drawStringBitmap(0.1, 0.25, txt.str(), GLUT_BITMAP_8_BY_13);
        txt.str("");
    }


    glViewport(windowSize[0]-200, windowSize[1] - 100, 200, 100);
    if (freeCam) txt << "Camera Mode: Free";
    else txt << "Camera Mode: Locked";
    drawStringBitmap(0, 0.25, txt.str(), GLUT_BITMAP_8_BY_13);
    txt.str("");
    txt << "F to Toggle";
    drawStringBitmap(0, 0.0, txt.str(), GLUT_BITMAP_8_BY_13);
    txt.str("");
}

void display() {
    glViewport(0, 0, windowSize[0], windowSize[1]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	cam.setView();
    drawAxis();

    //newObj.draw();
    //shark.drawObjDL();

    car.drawObjDL();
    wheel1.rotateByZ(-1.0);
    wheel1.drawObjDL();
    wheel2.rotateByZ(-1.0);
    wheel2.drawObjDL();
    turret.drawObjDL();

    drawHUD();

	glutSwapBuffers();
}

void idle() {
    int curTime = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = curTime - lastFrame;
    int sleepTime = frameRateMS - deltaTime;
    if (sleepTime > 0) Sleep(sleepTime);

    lastFrame = glutGet(GLUT_ELAPSED_TIME);
}

void normKeys(unsigned char key, int mouseX, int mouseY) {
    if (key == 'd') {
            if (freeCam){
                Vec3d deltaPos;
                deltaPos.x = 1.0;
                cam.cameraTrans(deltaPos);
            }
            else {
                curAz -= 0.1;
                cam.cameraPan(cam.getLookAt(), curAz, curDist, curEle);
            }
    }
    else if (key == 'a') {
            if (freeCam) {
                Vec3d deltaPos;
                deltaPos.x = -1.0;
                cam.cameraTrans(deltaPos);
            }
            else {
                curAz += 0.1;
                cam.cameraPan(cam.getLookAt(), curAz, curDist, curEle);
            }
    }
    else if (key == 'w') {
            if (freeCam) {
                    Vec3d deltaPos;
                deltaPos.z = -1.0;
                cam.cameraTrans(deltaPos);
            }
            else {
                curEle += 0.1;
                cam.cameraPan(cam.getLookAt(), curAz, curDist, curEle);
            }
    }
    else if (key == 's') {
            if (freeCam) {
                    Vec3d deltaPos;
                deltaPos.z = 1.0;
                cam.cameraTrans(deltaPos);
            }
            else {
                curEle -= 0.1;
                cam.cameraPan(cam.getLookAt(), curAz, curDist, curEle);
            }
    }
    else if (key == 'q') {
            if (freeCam) {
                    Vec3d deltaPos;
                deltaPos.y = 1.0;
                cam.cameraTrans(deltaPos);
            }
    }
    else if (key == 'z') {
            if (freeCam) {
                    Vec3d deltaPos;
                deltaPos.y = -1.0;
                cam.cameraTrans(deltaPos);
            }
    }
    else if (key == 'r') {
        curAz = 45.0;
        curEle = 5.0;
        curDist = 5.0;
        cam.cameraPan(Vec3d(0.0,0.0,0.0), curAz, curDist, curEle);
    }
    else if (key == 'f') {
        if (freeCam) freeCam = false;
        else freeCam = true;
    }
    glutPostRedisplay();
}

void special(int key, int mouseX, int mouseY) {
    if (key == GLUT_KEY_LEFT) turret.rotateByY(5.0);
    else if (key == GLUT_KEY_RIGHT) turret.rotateByY(-5.0);

    glutPostRedisplay();
}

void mouseDelta(int x, int y) {
    dX = x-prevX;
    dY = y-prevY;
    curEle+=-dY/100.0;
    curAz+=toRadians(dX/10.0);
    prevX = x;
    prevY = y;
}

void zoomDelta(int x, int y) {
    dZ = y-prevZ;
    curDist+=dZ/100.0;
    prevZ = y;
}

void mouseMove(int x, int y) {
    if (rightMouse == true) mouseDelta(x,y);
    if (middleMouse == true) zoomDelta(x,y);
    if (freeCam) {
        cam.cameraPan(cam.getLookAt(), curAz, curDist, curEle);
    }
    else {
        cam.cameraPan(Vec3d(0.0,0.0,0.0), curAz, curDist, curEle);
    }
    //printf("curAz: %f -- curDist: %f -- curEle: %f\n", curAz,curDist,curEle);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON) {
        prevX = x;
        prevY = y;
        if (state == GLUT_DOWN) rightMouse = true;
        else rightMouse = false;
    }
    else if (button == GLUT_MIDDLE_BUTTON) {
        prevZ = y;
        if (state == GLUT_DOWN) middleMouse = true;
        else middleMouse = false;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("CS473 ICE18: 3D Camera");
	lastFrame = glutGet(GLUT_ELAPSED_TIME);
	glutDisplayFunc(display);
	glutKeyboardFunc(normKeys);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);

	// ICE: Add the necessary callbacks so that the camera:
	//     * Pans around newObj's position when you hold down the
	//       right mouse button (i.e. moving the mouse left and right
    //       will change the azimuth, moving the mouse up and down
    //       will change the elevation, scrolling in or out will
    //       change the distance of the camera from the object)

    shark.importAll("Shark");
    car.importAll("car");
    wheel1.importAll("front");
    wheel1.moveTo(Vec3d(2.35,0.0,0.0));
    wheel2.importAll("rear");
    wheel2.moveTo(Vec3d(-2.75,0.15,0.0));
    turret.importAll("turret");
	newObj.moveTo(Vec3d(1.0, 2.0, 1.0));
	cam.setView();
	cam.cameraPan(Vec3d(0.0,0.0,0.0), curAz, curDist, curEle);
    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}
