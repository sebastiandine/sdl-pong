#include "Ball.h" 

Ball::Ball(float x, float y, Wall wall, Body* player1, Body* player2, Mix_Chunk* sfxBallHit) {
    posX = x;
    posY = y;
    width = 15;
    height = 15;
    speed = 300;
    maxSpeed = 800;
    movementAngle = 0;
    dir = LEFT;
    this->wall = wall;
    this->player1 = player1;
    this->player2 = player2;
    this->sfxBallHit = sfxBallHit;
    initValues = {posX, posY, 0.0, speed};
}

void Ball::reset() {
    posX = initValues.x;
    posY = initValues.y;
    movementAngle = initValues.angle;
    speed = initValues.speed;
}

void Ball::calculateAngle(Body *player) {
    if((posY + height) >= player->posY && (posY + height) <= (player->posY + 10)) {
        movementAngle = -150;
    }
    else if ((posY + height) >= (player->posY + 10) && (posY + height) <= (player->posY + 20)) {
        movementAngle = -120;
    }
    else if ((posY + height) >= (player->posY + 20) && (posY + height) <= (player->posY + 30)) {
        movementAngle = -90;
    }
    else if (posY >= (player->posY + 30) && (posY) <= (player->posY + 40)) {
        movementAngle = 90;
    }
    else if (posY >= (player->posY + 40) && (posY) <= (player->posY + 50)) {
        movementAngle = 120;
    }
    else if (posY >= (player->posY + 50) && (posY) <= (player->posY + 60)) {
        movementAngle = 150;
    }
    else {
        movementAngle = 0;
    }
}

void Ball::update(float deltaTime) {
    float moveX = speed * deltaTime;

    // collision with top wall
    if (posY <= wall.top) {
        movementAngle = -1 * movementAngle;
    }
    else if ((posY + height) >= wall.bottom) {
        movementAngle = -1 * movementAngle;
    }


    /** 
     * First, we need to check if the movement of this frame would move the x position of the 
     * ball behind the edge of one of the players. In that case, we reduce the movement so that
     * the x position of the ball exactly matches the edge of that player. This will lead to 
     * a collision detection during the next frame.
     * 
     * Note, that the second validation for each player (`posX != (player1->posX + player1->width)` or
     * `(posX + width) != player2->posX`) is essential to avoid an endless loop that would stick the ball
     * to the player's edge. These validations ensure, that the precise position of the ball to the 
     * player's edge is only performed once.
     * 
     * Note, that the third validation for each player (`posX > (player1->posX + player1->width)` or
     * `(posX + width) < player2->posX`) is required to avoid that the ball never moves beyond the player's 
     * x position if it is not colliding with it (the ball would flicker between the player's x 
     * position and the movement offest).
    */
    if ((posX - moveX) <= (player1->posX + player1->width) && posX != (player1->posX + player1->width) && posX > (player1->posX + player1->width)) {
        moveX = posX - (player1->posX + player1->width);
    }
    else if ((posX + width + moveX) >= player2->posX && (posX + width) != player2->posX && (posX + width) < player2->posX) {
        moveX = player2->posX - (posX + width);
    }
    else {
        
        // collision with player 1
        if (posX <= (player1->posX + player1->width)){
            // check if top or bottom of ball collide with player 1
            if((posY >= player1->posY && posY <= (player1->posY + player1->height))
                || ((posY+height) >= player1->posY && (posY+height) <= (player1->posY + player1->height))) {

                Mix_PlayChannel(-1, sfxBallHit, 0);
                dir = RIGHT;
                calculateAngle(player1);
                speed = speed < maxSpeed ? speed + 25 : speed;
            }
        }
        // collision with player 2
        else if ((posX + width) >= player2->posX){
            // check if top or bottom of ball collide with player 2
            if((posY >= player2->posY && posY <= (player2->posY + player2->height))
                || ((posY+height) >= player2->posY && (posY+height) <= (player2->posY + player2->height))) {
                
                Mix_PlayChannel(-1, sfxBallHit, 0);
                dir = LEFT;
                calculateAngle(player2);
                speed = speed < maxSpeed ? speed + 25 : speed;
            }
        }
    }


    switch (dir) {
        case RIGHT:
            posX += moveX;
            posY += movementAngle * deltaTime;
            break;
        case LEFT:
            posX -= moveX;
            posY += movementAngle * deltaTime;
            break;
        default:
            break;
    }
}

void Ball::render(SDL_Renderer *renderer) {
    SDL_Rect ball_rect = {(int) posX, (int) posY, (int) width, (int) height}; // white ball
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, &ball_rect);
}