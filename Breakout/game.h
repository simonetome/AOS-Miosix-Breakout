#ifndef GAME_H
#define GAME_H

#include "canvas.h"
#include "block.h"
#include "paddle.h"
#include "sphere.h"
#include "obstacle.h"
#include <list>
#include <vector>
#include <memory>

/**
 * @brief This is the most important class and represents the game 
 * itself. We can map this class as both the Model and Controller
 * modules in a MVC pattern (which wasn't used in the project). 
 * The game update position of the objects based on the input of
 * the player and on the collision that may happens during the movement
 * of the sphere. It also check if a block need to be destroyed and is
 * responsible of destroying it. In a very unformal way the Game class 
 * is responsible of everything, except the rendering of what happens.
 * When something happens (a block is destroyed, the ball bounces) the
 * Game object is responsible of calling the correct Canvas methods 
 * to display the changes to the user. 
 * 
 */
class Game{

public:
    /**
     * @brief Construct a new Game object 
     * 
     * @param dif int that represents the difficulty of the game [EASY-0|MEDIUM-1|HARD-2]
     */
    Game(int dif);
    /**
     * @brief the main method of the game object. It runs until the game ends and it's
     * responsible of checking collisions of the ball and update positions of the ball and 
     * blocks (check if after an hit the block is destroyed). It runs every X ms based on the 
     * difficulty thanks to a std::thread sleep. This method is also responsible on the creation
     * of the thread for the input controller.
     * 
     */
    void startGame();
    /**
     * @brief this methods runs cuncurrently with the startGame() and it's responsible on 
     * updating the paddle position according to the input of the player. According to BUTTON
     * in settings.h it could use both a GPIO controller or the keyboard.
     * 
     */
    void inputController();  

private:
    /**
     * @brief blocks in the game
     * 
     */
    std::vector<std::unique_ptr<Block>> blocks;
    /**
     * @brief obstacles in the game 
     * 
     */
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    /**
     * @brief moving paddle in the game
     * 
     */
    std::unique_ptr<Paddle> paddle;
    /**
     * @brief moving sphere in the game 
     * 
     */
    std::unique_ptr<Sphere> sphere;
    /**
     * @brief EASY(0)|MEDIUM(1)|HARD(2) (settings.h) 
     * controls the speed of the ball/the presence of the obstacles/number of overall hits needed
     * in order to win the game 
     * 
     */
    int difficulty;

    /**
     * @brief true if there are obstacles in the game, controlled by the difficulty.
     * 
     */
    bool obstacles_present;
    
    /**
     * @brief Canvas object 
     * 
     */
    Canvas canvas;
    
};

#endif