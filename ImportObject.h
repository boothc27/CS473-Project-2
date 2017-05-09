//  --  //  --  //  --  //  ImportObject.h   //  --  //  --  //  --  //
/* CS473: Computer Graphics
 * OpenGL .OBJ/.MTL file importer
 * Author: CPT Boyles
 */

#ifndef IMPORTOBJECT_H
#define IMPORTOBJECT_H

#include <string>
#include <vector>
#include <map>
#include "Vec3d.h"
#include "GL/freeglut.h"
#include "Object3D.h"

class Face
{
    public:
        Face();
        void addVertNorm(int vertexNum, int normNum, int matNum);
        int getFaceVert(int num);
        int getFaceNorm(int num);
        int getFaceMat(int num);
        int numVertecies();

    private:
        std::vector<int> faceVert;
        std::vector<int> faceNorm;
        std::vector<int> faceMat;
};

class ImportObject
{
    public:
        ImportObject();
        void importAll(std::string name_without_extension);
        void initObjDL();
        void drawObj();
        void drawObjDL();

        void setVelocity(Vec3d newVel);
        void moveTo(Vec3d newPos);
        void rotateByX(double dTheta);
        void rotateByY(double dTheta);
        void rotateByZ(double dTheta);
        Vec3d getPos();
        Vec3d getOrientation();
        Vec3d getVel();

    protected:

    private:
        void readMatl(std::string fName);
        void readObj(std::string fName);

        bool filesRead;
        bool dlProcessed;

        GLuint dlNumber;

        std::vector<Vec3d> vertecies;
        std::vector<Vec3d> vts;
        std::vector<Vec3d> normals;
        std::vector<Face> faces;
        std::map<std::string, int> matAbbrev;
        // Conversation with CDT Royal about reading material for lighting
        // Specifically, what data structures to use to read in different material values
        std::vector<Vec3d> material_ka;
        std::vector<Vec3d> material_kd;
        std::vector<Vec3d> material_ks;

        Vec3d getV3D(std::string line);
        Vec3d pos;
        Vec3d velocity;
        Vec3d orientation;


};



#endif // IMPORTOBJECT_H
