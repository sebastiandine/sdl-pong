#include <iostream>
#include "Menu.h"

Menu::Menu(SDL_Renderer *renderer) : Scene(renderer) {
    // init textures
    this->initTextures();
}

Menu::~Menu() {
    SDL_DestroyTexture(pongLogoTexture);
    SDL_DestroyTexture(instructionTexture);
}

std::string Menu::sceneName() {
    return "Menu";
}


void Menu::input(SDL_Event* event) {

    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_SPACE: 
                    status.end = true;
                    break;
                case SDLK_RETURN: 
                    status.end = true;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

SceneStatus Menu::update(float deltaTime) {
    return status;
}

void Menu::render() {

    // render background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
    SDL_RenderClear(renderer);

    // logo
    SDL_Rect logoTextureRect;
    SDL_QueryTexture(pongLogoTexture, NULL, NULL, &logoTextureRect.w, &logoTextureRect.h); // query width & height from texture and assign them to SDL_Rect
    logoTextureRect.x = windowWidth/2 - (logoTextureRect.w / 2); // now that we know width & height of the SDL_Rect, we can position it precisely
    logoTextureRect.y = windowHeight/2 - (logoTextureRect.h / 2) - 100;
    SDL_RenderCopy(renderer, pongLogoTexture, NULL, &logoTextureRect);

    // instruction
    SDL_Rect instructionTextureRect;
    SDL_QueryTexture(instructionTexture, NULL, NULL, &instructionTextureRect.w, &instructionTextureRect.h); 
    instructionTextureRect.x = windowWidth/2 - (instructionTextureRect.w / 2); 
    instructionTextureRect.y = windowHeight/2 - (instructionTextureRect.h / 2) + 100;
    SDL_RenderCopy(renderer, instructionTexture, NULL, &instructionTextureRect);

    SDL_RenderPresent(renderer);
}

void Menu::initTextures() {
    // init fonts
    TTF_Font* fontLarge = TTF_OpenFont("./assets/fonts/symtext/Symtext.ttf", 100);
    TTF_Font* fontMedium = TTF_OpenFont("./assets/fonts/symtext/Symtext.ttf", 24);
    std::cerr << "hallo" << std::endl;
    if (fontLarge == NULL || fontMedium == NULL) std::cerr << "Error initializing Font" << std::endl;

    // create textures
    //SDL_Surface *logoSurface = TTF_RenderText_Shaded(fontLarge, "PONG", {255, 255, 255, 255}, {255, 0, 0, 255}); // text with bg color
    SDL_Surface *logoSurface = TTF_RenderText_Solid(fontLarge, "PONG", {255, 255, 255, 255});
    pongLogoTexture = SDL_CreateTextureFromSurface(renderer, logoSurface);

    SDL_Surface *instructionSurface = TTF_RenderText_Solid(fontMedium, "Press SPACE or RETURN to start", {255, 255, 255, 255});
    instructionTexture = SDL_CreateTextureFromSurface(renderer, instructionSurface);
   
    // cleanup
    SDL_FreeSurface(logoSurface);
    SDL_FreeSurface(instructionSurface);

    TTF_CloseFont(fontLarge);
    TTF_CloseFont(fontMedium);
}

