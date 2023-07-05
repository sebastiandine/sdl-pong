#include <iostream>
#include "GameOver.h"

GameOver::GameOver(SDL_Renderer *renderer, std::string winnerText) : Scene(renderer) {

    sceneEndTimestamp = SDL_GetTicks() + 3000;
    // init textures
    this->initTextures(winnerText);
}

GameOver::~GameOver() {
    SDL_DestroyTexture(gameOverTexture);
    SDL_DestroyTexture(winnerTexture);
}

std::string GameOver::sceneName() {
    return "GameOver";
}


void GameOver::input(SDL_Event* event) {}

SceneStatus GameOver::update(float deltaTime) {
    if (SDL_GetTicks() >= sceneEndTimestamp) {
        status.end = true;
    }
    return status;
}

void GameOver::render() {

    // render background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
    SDL_RenderClear(renderer);

    // gameOver
    SDL_Rect gameOverTextureRect;
    SDL_QueryTexture(gameOverTexture, NULL, NULL, &gameOverTextureRect.w, &gameOverTextureRect.h);
    gameOverTextureRect.x = windowWidth/2 - (gameOverTextureRect.w / 2);
    gameOverTextureRect.y = windowHeight/2 - (gameOverTextureRect.h / 2) - 100;
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverTextureRect);

    // winnerText
    SDL_Rect winnerTextureRect;
    SDL_QueryTexture(winnerTexture, NULL, NULL, &winnerTextureRect.w, &winnerTextureRect.h); 
    winnerTextureRect.x = windowWidth/2 - (winnerTextureRect.w / 2); 
    winnerTextureRect.y = windowHeight/2 - (winnerTextureRect.h / 2) + 100;
    SDL_RenderCopy(renderer, winnerTexture, NULL, &winnerTextureRect);

    SDL_RenderPresent(renderer);
}

void GameOver::initTextures(std::string winnerText) {
    // init fonts
    TTF_Font* fontLarge = TTF_OpenFont("./assets/fonts/symtext/Symtext.ttf", 100);
    TTF_Font* fontMedium = TTF_OpenFont("./assets/fonts/symtext/Symtext.ttf", 24);
    if (fontLarge == NULL || fontMedium == NULL) std::cerr << "Error initializing Font" << std::endl;

    // create textures
    SDL_Surface *gameOverSurface = TTF_RenderText_Solid(fontLarge, "GAME OVER", {255, 255, 255, 255});
    gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);

    SDL_Surface *winnerSurface = TTF_RenderText_Solid(fontMedium, winnerText.c_str(), {255, 255, 255, 255});
    winnerTexture = SDL_CreateTextureFromSurface(renderer, winnerSurface);
   
    // cleanup
    SDL_FreeSurface(gameOverSurface);
    SDL_FreeSurface(winnerSurface);

    TTF_CloseFont(fontLarge);
    TTF_CloseFont(fontMedium);
}

