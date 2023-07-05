#include "Score.h"
#include <iostream>
#include <string>

Score::Score(SDL_Renderer* renderer) {
    this->renderer = renderer;
    counter = 0;

    // init font
    font = TTF_OpenFont("./assets/fonts/symtext/Symtext.ttf", 80);
    if (font == NULL) std::cerr << "Error initializing Font" << std::endl;

    // init texture
    texture = NULL;
    Score::updateTexture();
}

Score::~Score() {
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void Score::increase(int i) {
    counter += i;
    updateTexture();
}

int Score::value() {
    return counter;
}

void Score::reset() {
    counter = 0;
    updateTexture();
}

void Score::updateTexture() {

    if (texture != NULL) SDL_DestroyTexture(texture);

    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, std::to_string(counter).c_str(), {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    // cleanup
    SDL_FreeSurface(scoreSurface);
}
