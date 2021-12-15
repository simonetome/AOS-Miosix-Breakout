#ifndef GAMEOBJ_H
#define GAMEOBJ_H


class GameObj
{
    public:
        int x;
        int y;
        int width;
        const char * shape;
        int oldX = -1;
        int oldY = -1;
        GameObj(int x, int y,int width, const char * shape);
        

};

#endif