#include <SDL.h>
#include <SDL_ttf.h>

#include "Scene.h"

class Menu: public Scene {
    public:
        explicit Menu(SDL_Renderer* renderer);
        ~Menu();
        void input(SDL_Event* event) override;
        SceneStatus update(float deltaTime) override; 
        void render() override;
        std::string sceneName() override;
    private:
        SDL_Texture* pongLogoTexture;
        SDL_Texture* instructionTexture;
        void initTextures();
};