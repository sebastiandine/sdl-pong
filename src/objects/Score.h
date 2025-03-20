#include <SDL.h>
#include <SDL_ttf.h>

class Score {
    public:
        explicit Score(SDL_Renderer* renderer);
        ~Score();
        SDL_Texture* texture;
        void increase(int i);
        int value();
        void reset();
    private:
        int counter;
        SDL_Renderer* renderer;
        TTF_Font* font;
        void updateTexture();
};