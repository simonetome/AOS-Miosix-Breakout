#ifndef SPHERE_H
#define SPHERE_H

#include <string>
#include "shape.h"

class Sphere: public Shape{

    public:
        Sphere(int row, int col);
        int getRowDir() const;
        int getColDir() const;
        void setRowDir(int newDir);
        void setColDir(int newDir);

    private:
        int rowDir,colDir;

};

#endif