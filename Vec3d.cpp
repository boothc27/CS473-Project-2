//  --  //  --  //  --  //  Vec3d.cpp   //  --  //  --  //  --  //
#include "Vec3d.h"

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
