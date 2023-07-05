#pragma once
enum direction {NONE=0, UP, DOWN, LEFT, RIGHT};

class Body {
    public: 
        float posX;
        float posY;
        float width;
        float height;
        int speed;
        direction dir = NONE;
};