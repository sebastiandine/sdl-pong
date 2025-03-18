#include <SDL.h>

#include "Body.h"
#include "Wall.h"

struct PlayerInitValues {
    float x;
    float y;
};

class Player: public Body {
    public: 
        Player(float x, float y, Wall wall);
        void input(SDL_Event* event);
        void update(float deltaTime);
        void aiUpdate(float deltaTime, Body *ball);
        void render(SDL_Renderer *renderer);
        void reset();
    private:
        PlayerInitValues initValues;
        Wall wall;

};