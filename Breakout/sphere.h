#ifndef SPHERE_H
#define SPHERE_H

#include <string>
#include "shape.h"

/**
 * @brief Class that represents the sphere in the game.
 * 
 */
class Sphere: public Shape{

    public:
        /**
         * @brief Construct a new Sphere object
         * 
         * @param row define on which row the object will appear
         * @param col define on which column the object will appear 
         */
        Sphere(int row, int col);
        /**
         * @brief Get the Row Dir of the sphere
         * 
         * @return int 
         */
        int getRowDir() const;
        /**
         * @brief Get the Col Dir of the sphere
         * 
         * @return int 
         */
        int getColDir() const;
        /**
         * @brief Set the Row Dir of the sphere
         * 
         * @param newDir along the row +1/-1 for right/left
         */
        void setRowDir(int newDir);
        /**
         * @brief Set the Col Dir of the sphere
         * 
         * @param newDir along the col +1/-1 for down/up
         */
        void setColDir(int newDir);

    private:
        int rowDir,colDir;

};

#endif