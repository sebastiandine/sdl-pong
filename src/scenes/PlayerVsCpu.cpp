#include "PlayerVsCpu.h"

#include <iostream>

PlayerVsCpu::PlayerVsCpu(SDL_Renderer *renderer) : Scene(renderer) {

    // init sfx
    sfxBallHit = Mix_LoadWAV("./assets/sfx/mixkit-game-ball-tap-2073.wav");
    sfxPause = Mix_LoadWAV("./assets/sfx/mixkit-unlock-game-notification-253.wav");
    sfxBallMiss = Mix_LoadWAV("./assets/sfx/mixkit-negative-guitar-tone-2324.wav");


    wall = {10, (float)windowHeight-10};
    player1 = new Player(20, 270, wall);
    player2 = new Player(windowWidth-40, 270, wall);
    ball = new Ball(400, 300, wall, player1, player2, sfxBallHit);
    player1Score = new Score(renderer);
    player2Score = new Score(renderer);
    inputFreeze = 0;


    // init flags
    gamePaused = false;
    pointScored = false;

    // inits
    this->initTextures();
}

PlayerVsCpu::~PlayerVsCpu() {
    std::cout << "destroy";
    SDL_DestroyTexture(pauseTexture);
    Mix_FreeChunk(sfxBallHit);
    Mix_FreeChunk(sfxPause);
    Mix_FreeChunk(sfxBallMiss);

    delete player1Score;
    delete player2Score;

    delete player1;
    delete player2;
    delete ball;
}

std::string PlayerVsCpu::sceneName() {
    return "PlayerVsCpu";
}


void PlayerVsCpu::input(SDL_Event* event) {

    if(!pointScored && SDL_GetTicks() > inputFreeze) {
        
        player1->input(event);

        switch (event->type) {
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym) {
                    // SPACE for ball stop
                    case SDLK_SPACE:
                        Mix_PlayChannel(-1, sfxPause, 0);
                        gamePaused = !gamePaused;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

SceneStatus PlayerVsCpu::update(float deltaTime) {

    if(!gamePaused) {

        // wait a second if a point was scored during the last frame
        if (pointScored) {
            SDL_Delay(1000);
            pointScored = false;
        }

        // ball movement
        ball->update(deltaTime);

        if (ball->posX < player1->posX) {
            Mix_PlayChannel(-1, sfxBallMiss, 0);
            ball->reset();
            player1->reset();
            player2->reset();
            player2Score->increase(1);
            ball->dir = LEFT;
            pointScored = true;
            inputFreeze = SDL_GetTicks() + 1300;
            if (player2Score->value() == 10) {
                status.end = true;
                status.message = "Player 2 wins!";
            }
        }
        else if (ball->posX > (player2->posX + player2->width)) {
            Mix_PlayChannel(-1, sfxBallMiss, 0);
            ball->reset();
            player1->reset();
            player2->reset();
            player1Score->increase(1);
            ball->dir = RIGHT;
            pointScored = true;
            inputFreeze = SDL_GetTicks() + 1300;
            if (player1Score->value() == 10) {
                status.end = true;
                status.message = "Player 1 wins!";
            }
        }
        else {
        // player movement
        player1->update(deltaTime);
        player2->aiUpdate(deltaTime, ball);
        }


    }
    return status;
}

void PlayerVsCpu::render() {
    
    // render background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
    SDL_RenderClear(renderer);

    // render walls
    SDL_Rect wallTop = {0, 0, windowWidth, 10};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, &wallTop);

    SDL_Rect wallBottom = {0, windowHeight-10, windowWidth, 10};
    SDL_RenderFillRect(renderer, &wallBottom);

    SDL_Rect wallLeft = {0, 0, 10, windowHeight};
    SDL_RenderFillRect(renderer, &wallLeft);

    SDL_Rect wallRight = {windowWidth-10, 0, 10, windowHeight};
    SDL_RenderFillRect(renderer, &wallRight);

    SDL_Rect centerLine = {(windowWidth/2)-5, 0, 10, windowHeight};
    SDL_RenderFillRect(renderer, &centerLine);

    // player 1 score
    SDL_Rect player1ScoreRect;
    SDL_QueryTexture(player1Score->texture, NULL, NULL, &player1ScoreRect.w, &player1ScoreRect.h);
    player1ScoreRect.x = (windowWidth/2) - 100 - player1ScoreRect.w;
    player1ScoreRect.y = 25;
    SDL_RenderCopy(renderer, player1Score->texture, NULL, &player1ScoreRect);

    // player 2 score
    SDL_Rect player2ScoreRect;
    SDL_QueryTexture(player2Score->texture, NULL, NULL, &player2ScoreRect.w, &player2ScoreRect.h);
    player2ScoreRect.x = (windowWidth/2) + 100;
    player2ScoreRect.y = 25;
    SDL_RenderCopy(renderer, player2Score->texture, NULL, &player2ScoreRect);




    // render text
    if(gamePaused) {
        SDL_Rect pauseTextureRect;
        SDL_QueryTexture(pauseTexture, NULL, NULL, &pauseTextureRect.w, &pauseTextureRect.h); // query width & height from texture and assign them to SDL_Rect
        pauseTextureRect.x = windowWidth/2 - (pauseTextureRect.w / 2); // now that we know width & height of the SDL_Rect, we can position it precisely
        pauseTextureRect.y = windowHeight/2 - (pauseTextureRect.h / 2);
        SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseTextureRect);
    }
    else {
        if(!pointScored) {
            // render ball
            ball->render(renderer);
        }
        
        player1->render(renderer);
        player2->render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void PlayerVsCpu::initTextures() {
    // init fonts
    TTF_Font* fontLarge = TTF_OpenFont("./assets/fonts/symtext/Symtext.ttf", 100);
    if (fontLarge == NULL) std::cerr << "Error initializing Font" << std::endl;

    // SDL_Surface *textSurface = TTF_RenderText_Shaded(textFont, "PAUSE", {255, 255, 255, 255}, {255, 0, 0, 255}); text with background
    SDL_Surface *textSurface = TTF_RenderText_Solid(fontLarge, "PAUSE", {255, 255, 255, 255});
    pauseTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // cleanup
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(fontLarge);
}

