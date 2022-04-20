#ifndef SHAPE_H
#define SHAPE_H

#include <string>

class Shape{
    public:
        int getRow() const;
        int getCol() const;
        int getWidth() const;
        std::string getShape() const;
        void setRow(int r);
        void setCol(int c);
        void updatePosition(int r, int c);
    
    protected:
        int row, col, width;
        std::string shapestr;
};


#endif