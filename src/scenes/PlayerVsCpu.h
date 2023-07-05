#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Scene.h"
#include "../objects/Ball.h"
#include "../objects/Player.h"
#include "../objects/Wall.h"
#include "../objects/Score.h"

class PlayerVsCpu: public Scene {
    public:
        PlayerVsCpu(SDL_Renderer* renderer);
        ~PlayerVsCpu();
        void input(SDL_Event* event) override;
        SceneStatus update(float deltaTime) override; 
        void render() override;
        std::string sceneName() override;

        
    private:
        Player* player1;
        Player* player2;
        Ball* ball;
        Wall wall;

        Score* player1Score;
        Score* player2Score;

        Mix_Chunk* sfxBallHit;
        Mix_Chunk* sfxPause;
        Mix_Chunk* sfxBallMiss;

        SDL_Texture* pauseTexture;

        bool gamePaused;
        bool pointScored;

        Uint32 inputFreeze;

        void initTextures();
};