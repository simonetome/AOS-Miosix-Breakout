#ifndef CANVAS_H
#define CANVAS_H
#include <list>
#include "block.h"
#include "paddle.h"
#include "sphere.h"
#include "shape.h"
#include "obstacle.h"
#include <memory>
#include <vector>

class Canvas{

    public:
        void reset();
        void drawWalls();
        void drawObject(const Shape& object);  
        void deleteObject(const Shape& object);
        void movePaddle(const Shape& object,const int& rowDirection);
        void moveSphere(const Shape& object,const int& rowDirection,const int& colDirection);
        void firstRender(const std::vector<std::unique_ptr<Block>>& blocks,const std::unique_ptr<Paddle>& paddle,
        const std::unique_ptr<Sphere>& sphere, const std::vector<std::unique_ptr<Obstacle>>& obstacles);
        void write(const std::string& towrite);
        void changeColor(const std::string& color);
    private:
        
};


#endif