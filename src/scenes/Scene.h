#pragma once
#include <SDL.h>
#include <string>

struct SceneStatus {
    bool end;
    std::string message;
};

class Scene {
    public:
        explicit Scene(SDL_Renderer* renderer);
        virtual ~Scene();
        virtual void input(SDL_Event* event);
        virtual SceneStatus update(float deltaTime);
        virtual void render();
        virtual std::string sceneName();
    protected:
        SDL_Renderer* renderer;
        SceneStatus status;
        int windowWidth;
        int windowHeight;
};