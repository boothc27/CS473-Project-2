//  --  //  --  //  --  //  Vec3d.cpp   //  --  //  --  //  --  //
#include "Vec3d.h"
#include <cmath>
#include <stdio.h>

Vec3d::Vec3d() {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

Vec3d::Vec3d(double ix, double iy, double iz) {
    this->x = ix;
    this->y = iy;
    this->z = iz;
}

double dist(Vec3d a, Vec3d b) {
    return sqrt(pow(a.x-b.x,2.0)+pow(a.y-b.y,2.0)+pow(a.z-b.z,2.0));
}

