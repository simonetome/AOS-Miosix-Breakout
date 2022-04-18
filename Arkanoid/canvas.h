#ifndef CANVAS_H
#define CANVAS_H
#include <list>
#include "block.h"
#include "paddle.h"
#include "sphere.h"
#include "shape.h"
#include <memory>
#include <vector>

class Canvas{

    public:
        void reset();
        void drawWalls();
        void drawObject(Shape& object);  
        void deleteObject(Shape& object);
        void movePaddle(Shape& object, int rowDirection);
        void moveSphere(Shape& object, int rowDirection, int colDirection);
        void firstRender(std::vector<std::unique_ptr<Block>>& blocks,std::unique_ptr<Paddle>& paddle, std::unique_ptr<Sphere>& sphere);
        void gameOver();
        void win();
        void changeColor(std::string i);
    private:
        
};


#endif