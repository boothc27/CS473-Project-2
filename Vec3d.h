//  --  //  --  //  --  //  Vec3d.h   //  --  //  --  //  --  //
#ifndef VEC3D_H
#define VEC3D_H

// Simple class for a tuple of three Doubles
class Vec3d
{
    public:
        Vec3d();
        Vec3d(double x, double y, double z);

        double x;
        double y;
        double z;

    protected:

    private:
};

double dist(Vec3d a, Vec3d b);

#endif // VEC3D_H
