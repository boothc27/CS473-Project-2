//  --  //  --  //  --  //  main.cpp   //  --  //  --  //  --  //
/** CS473: Computer Graphics
  * Project 3
  * Modified from ICE Lesson 18: Camera and ICE Lesson 25: Lighting and ICE Lesson 27: Textures
  * Author: CDT Booth
  * Grass texture from: http://naldzgraphics.net/freebies/30-free-high-resolution-grass-textures/
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
#include "GL/glext.h"
#include "SOIL.h"

int frameRate = 60;     // Limit on FPS rate
int frameRateMS = 1000 / frameRate;

int windowSize[] = {800, 800};
int lastFrame = 0;
bool lightingOn = false;

double axisLength = 50.0;

ImportObject objs[20];
int num_objs = 9;
Light light1 = Light(0);
Camera cam = Camera();
double curAz = -180;
double curDist = 7.0;
double curEle = 5.0;
int prevX, prevY, prevZ = 0;
int dX, dY, dZ = 0;
Vec3d carpos;
int timer = 5000;
int score = 0;
bool rightMouse = false;
bool middleMouse = false;
bool hullCam = true;
bool game = false;
GLuint tex;

void drawAxis() {
    glClearColor(1, 1, 1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cam.setView();

	glBindTexture(GL_TEXTURE_2D, tex);
	glEnable(GL_TEXTURE_2D);

    glBegin(GL_POLYGON);
        // Top right
        glColor3f(1.0, 1.0, 1.0);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(50, -0.5, 50);

        glTexCoord2f(0.0, 1.0);
        glVertex3f(-50, -0.5, 50);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(-50, -0.5, -50);

        glTexCoord2f(1.0, 0.0);
        glVertex3f(50, -0.5, -50);
        glColor3f(1.0, 1.0, 1.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawHUD() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,2.0,0.0,1.0);

    glColor3f(0.5, 0.5, 0.5);
    using namespace std;
    ostringstream txt;

    glViewport(windowSize[0]/2-50, windowSize[1] - 100, 100, 100);
    if (game) {
        txt << "Time: " << timer/10;
        drawStringBitmap(0.1, 0.2, txt.str(), GLUT_BITMAP_8_BY_13);
        txt.str("");
        txt << "Score: " << score;
        drawStringBitmap(0.1, 0, txt.str(), GLUT_BITMAP_8_BY_13);
        txt.str("");
    }
    else {
        txt << "R: Start Game";
        drawStringBitmap(0.1, 0.2, txt.str(), GLUT_BITMAP_8_BY_13);
        txt.str("");
    }

    glViewport(0, windowSize[1] - 200, 200, 200);
    txt << "WASD: Move Car";
    drawStringBitmap(0.1, 0.65, txt.str(), GLUT_BITMAP_8_BY_13);
    txt.str("");
    txt << "Arrow Keys: Move Turret";
    drawStringBitmap(0.1, 0.55, txt.str(), GLUT_BITMAP_8_BY_13);
    txt.str("");

    glViewport(windowSize[0]-200, windowSize[1] - 100, 200, 100);
    if (hullCam) txt << "Camera Mode: Body";
    else txt << "Camera Mode: Turret";
    drawStringBitmap(0, 0.25, txt.str(), GLUT_BITMAP_8_BY_13);
    txt.str("");
    txt << "F to Toggle";
    drawStringBitmap(0, 0.0, txt.str(), GLUT_BITMAP_8_BY_13);
    txt.str("");
}

GLuint loadTexture(std::string filename) {
    // Placeholder variables - will be set later in the function
    GLuint textureNum;
    int height, width;

    // Loads the image file
    unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    if (image == NULL) {
        std::cout << "ERROR: Failed to load texture file:" << filename << "\n";
        return -1;
    }

    // Generates a new texture number and stores it under our variable above.
    // Note the & before the variable name indicates we are passing the
    // memory address of the variable to the function
    glGenTextures(1, &textureNum);

    // Now we tell OpenGL that which texture we're "working with"
    // i.e. setting parameters for.
    glBindTexture(GL_TEXTURE_2D, textureNum);

    // Specifies how OpenGL will handle texture coordinates greater than 1.0
    // and less than 0.0.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // X-axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   // Y-axis

    // Specifies how OpenGL will interpolate the texture if it needs
    // to scale it up or down to match the size of the face that we are
    // painting the texture on.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Now that we've set the parameters, we're going to convert the SOIL
    // image into a texture that is bound to the textureNum we established above
    glTexImage2D(GL_TEXTURE_2D,
                 0,                 // mipmap level; we'll leave it at 0
                 GL_RGB,            // format to store texture
                 width, height,     // dimensions of texture
                 0,                 // legacy parameter; leave at 0
                 GL_RGB,            // format of source image
                 GL_UNSIGNED_BYTE,  // how we stored the source image
                 image);            // image file to load

    // The texture is imported, so we don't need our image taking up
    // space in memory any more.
    SOIL_free_image_data(image);

    // Set the currently bound texture to 0 (to ensure that later glTexParameters
    // or other such functions don't accidentally mess up the texture we just
    // imported)
    glBindTexture(GL_TEXTURE_2D, 0);
    return textureNum;
}

void display() {
    glViewport(0, 0, windowSize[0], windowSize[1]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    drawAxis();

    glLoadIdentity();

	cam.cameraLookAt(carpos);
	cam.setView();
	Vec3d orient;
	if (hullCam) orient = objs[0].getOrientation();
	else orient = objs[3].getOrientation();
    double x = -5.0*cos(toRadians(orient.y));
    double z = 5.0*sin(toRadians(orient.y));
    Vec3d campos(carpos.x + x, 4.0, carpos.z + z);
	cam.moveCameraTo(campos);
	light1.drawLight();

	if (game) {
        if (timer > 0) timer-=1;
	}

    for(int i=0;i<num_objs;i++) {
        Vec3d newpos(objs[i].getPos().x+objs[i].getVel().x,objs[i].getPos().y+objs[i].getVel().y,objs[i].getPos().z+objs[i].getVel().z);
        objs[i].moveTo(newpos);
        if (i>3) {
            for (int j=0;j<num_objs;j++) {
                if (i!=j && i < 10 && (j < 3 || j > 10)) {
                    //printf("objs[%d]pos:%f,%f,%f\n",i,objs[i].getPos().x,objs[i].getPos().y,objs[i].getPos().z);
                    //printf("dist:%f\n",objs_dist);
                    if (dist(objs[i].getPos(),objs[j].getPos()) < 2.0) {

                        objs[i].moveTo(Vec3d(0.0,10.0,0.0));
                        score+=1;
                    }
                }
            }
        }
        else {
            objs[i].moveTo(carpos);
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
                for (int i=0;i<4;i++) {
                    objs[i].rotateByY(-5.0);
                }
    }
    else if (key == 'a') {
                for (int i=0;i<4;i++) {
                    objs[i].rotateByY(5.0);
                }
    }
    else if (key == 'w') {
                Vec3d orient = objs[0].getOrientation();
                double x = 1.0*cos(-toRadians(orient.y));
                double z = 1.0*sin(-toRadians(orient.y));
                carpos.x+=x;
                carpos.z+=z;
    }
    else if (key == 's') {
                Vec3d orient = objs[0].getOrientation();
                double x = -1.0*cos(-toRadians(orient.y));
                double z = -1.0*sin(-toRadians(orient.y));
                carpos.x+=x;
                carpos.z+=z;
    }
    else if (key == 'r') {
        game = true;
        timer = 5000;
        score = 0;
    }
    else if (key == 'f') {
        if (hullCam) hullCam = false;
        else hullCam = true;
    }
    else if (key == ' ') {
        objs[num_objs] = ImportObject();
        objs[num_objs].importAll("shell");
        Vec3d orient = objs[3].getOrientation();
        double x = 2.0*cos(-toRadians(orient.y));
        double z = 2.0*sin(-toRadians(orient.y));
        objs[num_objs].moveTo(Vec3d {carpos.x, carpos.y+1.5, carpos.z});
        objs[num_objs].rotateByY(orient.y);
        objs[num_objs].setVelocity(Vec3d {x,0.0,z});
        if (num_objs == 19) {
            num_objs = 10;
        }
        else num_objs+=1;
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
    curAz+=(dX/10.0);
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
    if (hullCam) {
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
	glutCreateWindow("Booth Project3");
	lastFrame = glutGet(GLUT_ELAPSED_TIME);
	glutDisplayFunc(display);
	glutKeyboardFunc(normKeys);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
    tex= SOIL_load_OGL_texture("grass.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    glBindTexture(GL_TEXTURE_2D, 0);

    for (int i=0;i<9;i++) {
        objs[i] = ImportObject();
    }
    carpos.x = 0.0; carpos.y = 0.0; carpos.z = 0.0;

	light1.enableLight();
	light1.makeInfDist();
    light1.setPos(Vec3f(0.0, 20.0, 0.0));
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    objs[0].importAll("car");
    objs[1].importAll("front");
    objs[2].importAll("rear");
    objs[3].importAll("turret");
    for (int i=4;i<9;i++) {
        objs[i].importAll("box");
    }
    objs[4].moveTo(Vec3d(-20.0,1.0,17.0));
    objs[5].moveTo(Vec3d(-15.0,1.0,18.0));
    objs[6].moveTo(Vec3d(-24.0,1.0,-14.0));
    objs[7].moveTo(Vec3d(-12.0,1.0,-31.0));
    objs[8].moveTo(Vec3d(12.0,1.0,-11.0));
    objs[9].moveTo(Vec3d(26.0,1.0,14.0));
    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}
