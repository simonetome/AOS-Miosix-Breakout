#include "canvas.h"
#include "paddle.h"

Canvas::Canvas(){
    //setCanvasMode();
}


void Canvas::drawFrame(const std::list<GameObj*> & changed){
    for (auto const& obj : changed){
        Terminal::delObject(obj);
       
        Terminal::drawObject(obj);
    }
}

// function to draw the initial field
void Canvas::drawField(const std::list<GameObj*> & gameObjects){

    for (auto const& obj : gameObjects){
        Terminal::drawObject(obj);
    }
}

