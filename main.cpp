//  --  //  --  //  --  //  main.cpp   //  --  //  --  //  --  //
/** CS473: Computer Graphics
  * Project 3
  * Modified from ICE Lesson 18: Camera and ICE Lesson 25: Lighting
  * Author: CDT Booth
  */

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include "Object3D.h"
#include "Camera.h"
#include <GL/glut.h>
#include "GL/freeglut.h"
#include "ImportObject.h"
#include "Light.h"
#include "Helpers.h"

int frameRate = 60;     // Limit on FPS rate
int frameRateMS = 1000 / frameRate;

int windowSize[] = {800, 800};
int lastFrame = 0;
bool lightingOn = false;

double axisLength = 50.0;

ImportObject objs[10];
int num_objs = 5;
Light light1 = Light(0);
Camera cam = Camera();
double curAz = 45;
double curDist = 5.0;
double curEle = 5.0;
int prevX, prevY, prevZ = 0;
int dX, dY, dZ = 0;
Vec3d carpos;
bool rightMouse = false;
bool middleMouse = false;
bool freeCam = true;

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
    cam.cameraLookAt(carpos);
	cam.setView();
	light1.drawLight();
    drawAxis();

    for(int i=0;i<num_objs;i++) {
        if (i>3) {
            for (int j=0;j<num_objs;j++) {
                if (i!=j) {
                    float objs_dist = dist(objs[i].getPos(),objs[j].getPos());
                    //printf("objs[%d]pos:%f,%f,%f\n",i,objs[i].getPos().x,objs[i].getPos().y,objs[i].getPos().z);
                    //printf("dist:%f\n",objs_dist);
                    if (dist(objs[i].getPos(),objs[j].getPos()) < 3.0) objs[i].moveTo(Vec3d(0.0,-10.0,0.0));
                }
            }
        }
        else {
            if (i==1) objs[1].moveTo(Vec3d(carpos.x+2.35,carpos.y,carpos.z));
            else if (i==2) objs[2].moveTo(Vec3d(carpos.x-2.75,carpos.y+0.15,carpos.z));
            else objs[i].moveTo(carpos);
        }
        objs[i].drawObjDL();
    }

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
                for (int i=0;i<4;i++) {
                    objs[i].rotateByY(5.0);
                }
            }
            else {
                curAz -= 0.1;
                cam.cameraPan(cam.getLookAt(), curAz, curDist, curEle);
            }
    }
    else if (key == 'a') {
            if (freeCam) {
                carpos.x-=1;
            }
            else {
                curAz += 0.1;
                cam.cameraPan(cam.getLookAt(), curAz, curDist, curEle);
            }
    }
    else if (key == 'w') {
            if (freeCam) {
                carpos.z+=1;
            }
            else {
                curEle += 0.1;
                cam.cameraPan(cam.getLookAt(), curAz, curDist, curEle);
            }
    }
    else if (key == 's') {
            if (freeCam) {
                carpos.z-=1;
            }
            else {
                curEle -= 0.1;
                cam.cameraPan(cam.getLookAt(), curAz, curDist, curEle);
            }
    }
    else if (key == 'q') {
            if (freeCam) {
                carpos.y+=1;
            }
    }
    else if (key == 'z') {
            if (freeCam) {
                carpos.y-=1;
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
    if (key == GLUT_KEY_LEFT) objs[3].rotateByY(5.0);
    else if (key == GLUT_KEY_RIGHT) objs[3].rotateByY(-5.0);

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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

    objs[0] = ImportObject();
    objs[1] = ImportObject();
    objs[2] = ImportObject();
    objs[3] = ImportObject();
    objs[4] = ImportObject();
    carpos.x = 0.0; carpos.y = 0.0; carpos.z = 0.0;

	light1.enableLight();
	light1.makeInfDist();
    light1.setPos(Vec3f(0.0, 20.0, 0.0));
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    objs[0].importAll("car");
    objs[1].importAll("front");
    objs[2].importAll("rear");
    objs[3].importAll("turret");
    objs[4].importAll("car");
    objs[4].moveTo(Vec3d(-5.0,0.0,5.0));
	cam.setView();
	cam.cameraPan(Vec3d(0.0,0.0,0.0), curAz, curDist, curEle);
    glutIdleFunc(idle);

	glutMainLoop();
}
