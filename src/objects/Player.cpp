#include "Player.h" 

Player::Player(float x, float y, Wall wall) {
    posX = x;
    posY = y;
    width = 15;
    height = 60;
    speed = 200;
    this->wall = wall;
    initValues = {posX, posY};
}

void Player::input(SDL_Event* event) {

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            // WS for player movement
            case SDLK_w:
                dir = UP;
                break;
            case SDLK_s:
                dir = DOWN;
                break;
            default:
                break;
        }
    }
    else if (event->type == SDL_KEYUP) {
        if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_s) {
            dir = NONE;
        }
    }
}

void Player::update(float deltaTime) {
    float move = speed * deltaTime;
    switch (dir) {
        case UP:
            posY -= (posY - move) <= wall.top ? 0 : move;
            break;
        case DOWN:
            posY += (posY + height + move) >= wall.bottom ? 0: move;
        default:
            break;
    }
}

void Player::aiUpdate(float deltaTime, Body *ball) {
    float move = speed * deltaTime;
    // UP
    if ((ball->posY + ball->height) < (posY + 20)) {
         posY -= (posY - move) <= wall.top ? 0 : move;
    }
    // DOWN
    else if (ball->posY > (posY + height - 20)) {
        posY += (posY + height + move) >= wall.bottom ? 0: move;
    }
}


void Player::render(SDL_Renderer *renderer) {
    SDL_Rect player_rect = {(int) posX, (int) posY, (int) width, (int) height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, &player_rect);
}

void Player::reset() {
    posX = initValues.x;
    posY = initValues.y;
}