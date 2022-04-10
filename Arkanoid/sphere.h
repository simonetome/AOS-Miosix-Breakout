#ifndef SPHERE_H
#define SPHERE_H

#include <string>
#include "shape.h"

class Sphere: public Shape{

    public:
        Sphere(int row, int col);
        int getRowDir();
        int getColDir();

    private:
        int rowDir,colDir;

};

#endif