#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include "gomoku.hpp"
#include <SDL.h>

class Button {
private:
    int _buttonX;
    int _buttonY;
    int _width;
    int _height;

public:
    Button(int buttonX, int buttonY, int buttonWidth, int buttonHeight);
    ~Button();
    bool inButton(int mouseX, int mouseY);
    void renderButton(SDL_Renderer* renderer, int R, int G, int B);
    int getButtonX() const;
    int getButtonY() const;
    int getWidth() const;
    int getHeight() const;
};

#endif