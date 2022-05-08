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

/**
 * @brief Canvas class is responsible for drawing and deleting objects from the terminal. It could be seen as the 
 * "View" component in a MVC pattern.  
 * 
 */
class Canvas{

    public:
        /**
         * @brief reset the terminal view deleting everything on it. 
         */
        void reset();
        /**
         * @brief draw on the terminal the Shape.
         * 
         * @param object 
         */
        void drawObject(const Shape& object);  
        /**
         * @brief delete the object from the terminal.
         * 
         * @param object 
         */
        void deleteObject(const Shape& object);
        /**
         * @brief move the paddle in the chosen direction. It's implementation just deletes one position and add another character in
         * the intended direction.  
         * 
         * @param object Shape reference to the paddle to move
         * @param rowDirection direction along the row +1/-1 for right/left
         */
        void movePaddle(const Shape& object,const int& rowDirection);
        /**
         * @brief move the sphere object 
         * 
         * @param object Shape reference to sphere
         * @param rowDirection direction along the row +1/-1 for right/left
         * @param colDirection direction along the col +1/-1 for down/up 
         */
        void moveSphere(const Shape& object,const int& rowDirection,const int& colDirection);
        /**
         * @brief method for the first render of the game. Called if I want to render everything that regards the game.
         *        All parameters are std::unique_ptr to Shape.
         * 
         * @param blocks blocks to be rendered 
         * @param paddle paddle to be rendered 
         * @param sphere sphere to be rendered
         * @param obstacles obstacles to be rendered
         */
        void firstRender(const std::vector<std::unique_ptr<Block>>& blocks,const std::unique_ptr<Paddle>& paddle,
        const std::unique_ptr<Sphere>& sphere, const std::vector<std::unique_ptr<Obstacle>>& obstacles);
        /**
         * @brief method to return to the final screen that could wither be a win xor a gameover.
         * 
         * @param won boolean (if true the "you won" screen appears, otherwise it will be a "game over"). 
         */
        void write(bool won);
    private:
        /**
         * @brief draw the walls of the game.
         */
        void drawWalls();
        /**
         * @brief wrapper method to write the escape sequence of the needed color, more human readable wrt to writing the escape itself.
         * 
         * @param color is the escape sequence for the color -> defined in settings.h header. 
         */
        void changeColor(const std::string& color);
        
};


#endif