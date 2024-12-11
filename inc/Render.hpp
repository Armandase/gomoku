#ifndef __RENDER_HPP__
#define __RENDER_HPP__

#include "Button.hpp"
#include "gomoku.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

const SDL_Color BLACK_COLOR = { 0, 0, 0, 255 };
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
    void renderMenu(Button& player, Button& IA) const;
    void erasePlayer(int x, int y) const;
    void drawCircle(int centreX, int centreY) const;
    void writeText(const std::string& msg, const std::string& font,
        const SDL_Rect& rect, const SDL_Color& color, int size) const;
    void renderCapture(uint16_t p1Capture, uint16_t p2Capture) const;
    void eraseCapture();
    void renderImage(const std::string& path, const SDL_Rect* rect);

private:
    SDL_Renderer* _renderer;
    SDL_Window* _window;
};

#endif