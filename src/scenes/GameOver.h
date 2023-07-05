#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Scene.h"

class GameOver: public Scene {
    public:
        GameOver(SDL_Renderer* renderer, std::string winnerText);
        ~GameOver();
        void input(SDL_Event* event) override;
        SceneStatus update(float deltaTime) override; 
        void render() override;
        std::string sceneName() override;
    private:
        SDL_Texture* gameOverTexture;
        SDL_Texture* winnerTexture;
        void initTextures(std::string winnerText);
        Uint32 sceneEndTimestamp;
};