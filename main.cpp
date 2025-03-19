// if the game is compiled on Windows via MinGW, we need to flag the `main` function explicitly
// to override SDL from searching for the commonly expected `main` function signature.
#if defined(_WIN32) && (defined(__MINGW32__) || defined(__MINGW64__))
#define SDL_MAIN_HANDLED // explicitly initialize SDL main (required on Windows with static link). see also the `main` function
#endif

// if the game is compiled on Windows via MSVC, we need the main function to support
// the Windows window application convention
#ifdef _MSC_VER
#include <windows.h>
#endif

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "src/scenes/Scene.h"
#include "src/scenes/PlayerVsCpu.h"
#include "src/scenes/Menu.h"
#include "src/scenes/GameOver.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FPS 30
#define FRAME_TIME (1000 / FPS) // how many milliseconds per frame

bool gameIsRunning = false;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

Scene *currentScene;

int lastFrameTimestamp = 0; // Timestamp of the last frame rendering

bool init_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL2 Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    //window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return false;
    }

    /* init ttf */
    if (TTF_Init() != 0) {
        std::cerr << "Error initializing SDL_TTF" << std::endl;
        return false;
    }

    /* init sounds/ mixer */
    if(Mix_Init(0) != 0) { // 0 for wav support
        std::cerr << "Error initializing SDL_Mixer" << std::endl;
        return false;
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    return true;
}


void input() {

    SDL_Event event;
    SDL_PollEvent(&event);

     switch (event.type) {
        case SDL_QUIT:  // x icon on top right header
            gameIsRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                // ESCAPE for quitting the game
                case SDLK_ESCAPE:
                    gameIsRunning = false;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    currentScene->input(&event);
}

void update() {

    /**
     * Calculate how long the program should wait, until it should render the next frame.
     * Since we are using `deltaTime`for the movement, this is not necessary from the 
     * perspective of the game, but since we are using `SDL_Delay` for waiting, we are 
     * not blocking the CPU when it is not required.
    */
    int timeToWait = FRAME_TIME - (SDL_GetTicks() - lastFrameTimestamp);
    if (timeToWait > 0) {
        SDL_Delay(timeToWait);
    }

    /**
     * By using the concept of `deltaTime`, we do not need to specify movements
     * per frame, but per second.
    */
    float deltaTime = (SDL_GetTicks() - lastFrameTimestamp) / 1000.0f;

    SceneStatus sceneStatus = currentScene->update(deltaTime);
    if(sceneStatus.end) {
       
        if (currentScene->sceneName() == "Menu") {
            delete currentScene;
            currentScene = new PlayerVsCpu(renderer);
        }
        else if (currentScene->sceneName() == "PlayerVsCpu") {
            delete currentScene;
            currentScene = new GameOver(renderer, sceneStatus.message);
        }
        else if (currentScene->sceneName() == "GameOver") {
            delete currentScene;
            currentScene = new PlayerVsCpu(renderer);
        }
    }

    lastFrameTimestamp = SDL_GetTicks();
}

void render() {
    currentScene->render();
}

void destroy_window() {
    delete currentScene;
    Mix_CloseAudio(); 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int _main() {
    gameIsRunning = init_window();
    currentScene = new Menu(renderer);

    std::cout << "Game started." << std::endl;
    while (gameIsRunning) {
        input();
        update();
        render();
    }

    destroy_window();
    return 0;
}

int main(int argc, char* argv[]) {

    #if defined(_WIN32) && (defined(__MINGW32__) || defined(__MINGW64__))
    SDL_SetMainReady(); // explicitly initialize SDL main (required on Windows with static link)
    #endif
    return _main();
}

// on windows with MSVC compiler, we need to support this main function signature
#ifdef _MSC_VER
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return _main();
}
#endif

