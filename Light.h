#ifndef LIGHT_H
#define LIGHT_H

#include "Vec3f.h"
#include "Vec4f.h"
#include "GL/freeglut.h"

class Light
{
    public:
        Light(int num);

        void enableLight();
        void disableLight();

        void makeLocal();       // Converts light into a local light source
        void makeInfDist();     // Converts light into a light at inf. distance

        void setPos(Vec3f newPos);
        void changePos(Vec3f deltaPos);
        void setRadialAtten(Vec3f newAtten);

        void setAmbCol(Vec3f newCol);
        void setDiffCol(Vec3f newCol);
        void setSpecCol(Vec3f newCol);

        void drawLight();

    protected:

    private:
        void setLight();

        int lightNum;

        Vec3f pos;
        Vec3f radAtten;
        Vec4f ambLight;
        Vec4f diffLight;
        Vec4f specLight;
        bool enabled;
        bool localLight;


};

#endif // LIGHT_H
