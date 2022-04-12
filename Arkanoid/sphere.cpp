#include "sphere.h"
#include "settings.h"

Sphere::Sphere(int row, int col){
    this -> row = row;
    this -> col = col;
    this -> width = 1;
    this -> shapestr = SPHERE;
    this -> colDir = 0;
    this -> rowDir = 1;
}


int Sphere::getColDir(){ return colDir; }
int Sphere::getRowDir(){ return rowDir; }
void Sphere::setColDir(int newDir){ colDir = newDir; }
void Sphere::setRowDir(int newDir){ rowDir = newDir; }