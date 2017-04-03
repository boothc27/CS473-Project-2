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

class ImportObject : Object3D
{
    public:
        ImportObject();
        void importAll(std::string name_without_extension);
        void initObjDL();
        void drawObj();
        void drawObjDL();

    protected:

    private:
        void readMatl(std::string fName);
        void readObj(std::string fName);

        bool filesRead;
        bool dlProcessed;

        GLuint dlNumber;

        std::vector<Vec3d> vertecies;
        std::vector<Vec3d> normals;
        std::vector<Face> faces;
        std::map<std::string, int> matAbbrev;
        std::vector<Vec3d> materials;

        Vec3d getV3D(std::string line);


};



#endif // IMPORTOBJECT_H
