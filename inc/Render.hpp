#ifndef __RENDER_HPP__
#define __RENDER_HPP__

#include "Button.hpp"
#include "gomoku.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <tuple>
#include <vector>

// #define WHITE_STONE_PATH "/nfs/homes/adamiens/42/spe/gomoku/img/stones/frog.png"
// #define BLACK_STONE_PATH "/nfs/homes/adamiens/42/spe/gomoku/img/stones/rat.png"

// #define PLACING_STONE_SOUND_PATH "/nfs/homes/adamiens/42/spe/gomoku/sound/placing_stone.ogg"
// #define PLACING_STONE_SOUND_PATH "/nfs/homes/adamiens/42/spe/gomoku/sound/placing_stone1.ogg"
// #define PLACING_STONE_SOUND_PATH "/nfs/homes/adamiens/42/spe/gomoku/sound/placing_stone_wood.ogg"

#define CAPTURE_SOUND_PATH "/nfs/homes/adamiens/42/spe/gomoku/sound/capture_axe.ogg"
// #define CAPTURE_SOUND_PATH "/nfs/homes/adamiens/42/spe/gomoku/sound/capture_animal.ogg"
// #define CAPTURE_SOUND_PATH "/nfs/homes/adamiens/42/spe/gomoku/sound/capture_blood.ogg"

const SDL_Color BLACK_COLOR = { 0, 0, 0, 255 };
// const SDL_Color LIGHT_GREY_COLOR = { 211, 211, 211, 100 };
const SDL_Color LIGHT_GREY_COLOR = { 100, 100, 100, 255 };
const SDL_Color WHITE_COLOR = { 255, 255, 255, 255 };

class Game;
class Button;

class Render {
public:
    Render();
    ~Render();

    Render(const Render& cpy);
    Render& operator=(const Render& rhs);

    SDL_Renderer* getRenderer() const;
    void initSDL(const std::string& windowName, int windowWidth,
        int windowHeight);
    void renderWin(uint16_t player) const;

    void renderBoard(Game& game) const;
    // void renderMenu(Button& player, Button& IA, Button& IAvsIA) const;
    void renderMenu(std::vector<std::tuple<Button, std::string>>& buttons) const;
    void erasePlayer(int x, int y) const;
    void drawCircle(int centreX, int centreY) const;
    void drawStoneAssets(int centreX, int centreY, int player);
    void writeText(const std::string& msg, const std::string& font,
        const SDL_Rect& rect, const SDL_Color& color, int size) const;
    void renderCapture(uint16_t p1Capture, uint16_t p2Capture) const;
    void eraseCapture();
    void renderImage(const std::string& path, const SDL_Rect* rect);
    void renderTime(const std::string& timeTaken) const;
    void drawRedCross(int x, int y);
    void drawEmptyCross(int x, int y);

private:
    SDL_Renderer* _renderer;
    SDL_Window* _window;
};

#endif