#ifndef SHAPE_H
#define SHAPE_H

#include <string>

/**
 * @brief superclass that represents every shape in the game, except the walls.
 * 
 */
class Shape{
    public:
        /**
         * @brief Get the row position of the shape 
         * 
         * @return int 
         */
        int getRow() const;
        /**
         * @brief Get the col position of the shape
         * 
         * @return int 
         */
        int getCol() const;
        /**
         * @brief Get the Width of the shape. Each shape is defined as a string (an escape sequence that defines the atomic character that represents 
         * the material of the object). Each object has a characteristic width (note: no height).
         * 
         * Example for a block defined with '@' and with width 5:    @@@@@
         * 
         * @return int 
         */
        int getWidth() const;
        /**
         * @brief Get the Color of the shape. The color is the escape sequence defined in settings.h.
         * 
         * @return std::string 
         */
        std::string getColor() const;
        /**
         * @brief Get the string that represents the atomic character of the object (x,y) point.
         * 
         * Example for a block defined with '@' and with width 5:    @@@@@ the method will return '@'
         * 
         * @return std::string shapestr
         */
        std::string getShape() const;
        /**
         * @brief Set the Row position for the object 
         * 
         * @param r int
         */
        void setRow(int r);
        /**
         * @brief Set the Col position for the object 
         * 
         * @param c int 
         */
        void setCol(int c);
        /**
         * @brief update the position of the object using the directions for both row and column.
         * 
         * @param r signed int that is summed to current row position. +1/-1 to move right/left. 
         * @param c signed int that is summed to current col position. +1/-1 to move down/up.
         */
        void updatePosition(int r, int c);
        /**
         * @brief Set the Color of the object 
         * 
         * @param color string (use the definitions in settings.h)
         */
        void setColor(const std::string color);
    
    protected:
        int row, col, width;
        std::string shapestr;
        std::string color;
};


#endif