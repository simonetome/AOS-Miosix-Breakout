

class gameObj
{
    private:

        float x;
        float y;
        float height;
        float width;

    public:

        virtual float getX();
        virtual void setX(float x);

        virtual float getY();
        virtual void setY(float y);

        virtual float getHeight();
        virtual void setHeight(float height);

        virtual float getWidth();
        virtual void setWidth(float width);
};