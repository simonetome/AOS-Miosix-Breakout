#include "shape.h"


int Shape::getRow() const{ return row;}
int Shape::getCol() const{ return col;}
int Shape::getWidth() const{return width;}
std::string Shape::getShape() const{ return shapestr;}
void Shape::setRow(int r){this->row = r;}
void Shape::setCol(int c){this->col = c;}
void Shape::updatePosition(int rdir, int cdir){
    row += rdir;
    col += cdir;
}