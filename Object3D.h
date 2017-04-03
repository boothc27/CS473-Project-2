#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Vec3d.h"

class Object3D
{
    public:
        Object3D();

        void moveTo(double newX, double newY, double newZ);
        void moveTo(Vec3d newPos);

        void rotateX(double theta);
        void rotateY(double theta);
        void rotateZ(double theta);

        void rotateByX(double dTheta);
        void rotateByY(double dTheta);
        void rotateByZ(double dTheta);

        Vec3d getPos();
        Vec3d getOrient();

        virtual void draw();

    protected:

        Vec3d pos;
        Vec3d orientation;

    private:
};

#endif // OBJECT3D_H
