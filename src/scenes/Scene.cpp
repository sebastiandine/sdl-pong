#include "Scene.h"
#include <iostream>

Scene::Scene(SDL_Renderer* renderer) {
    this->renderer = renderer;
    this->status = {false, ""};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
}

Scene::~Scene() {}

void Scene::input(SDL_Event* event) {}
SceneStatus Scene::update(float deltaTime) { return status; }
void Scene::render() {}
std::string Scene::sceneName() { return "Scene"; }