#include "shape.h"


const int Shape::getRow(){ return row;}
const int Shape::getCol(){ return col;}
const int Shape::getWidth(){return width;}
const std::string Shape::getShape(){ return shapestr;}
void Shape::setRow(int r){this->row = r;}
void Shape::setCol(int c){this->col = c;}
void Shape::updatePosition(int rdir, int cdir){
    row += rdir;
    col += cdir;
}