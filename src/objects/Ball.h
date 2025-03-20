#include <SDL.h>
#include <SDL_mixer.h>

#include "Body.h"
#include "Wall.h"

struct BallInitValues {
    float x;
    float y;
    float angle;
    int speed;
};

class Ball: public Body {
    public:
        int maxSpeed;
        Ball(float x, float y, Wall wall, Body* player1, Body* player2, Mix_Chunk* sfxBallHit);
        void update(float deltaTime);
        void render(SDL_Renderer *renderer);
        void reset(); 
    private:
        BallInitValues initValues;
        Wall wall;
        Body* player1;
        Body* player2;
        float movementAngle;
        Mix_Chunk* sfxBallHit;
        void calculateAngle(Body *player);
};