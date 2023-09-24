#include "../inc/Button.hpp"

Button::Button(int buttonX, int buttonY, int buttonWidth, int buttonHeight) : 
    _buttonX{buttonX},
    _buttonY{buttonY},
    _width{buttonWidth},
    _height{buttonHeight} {}

Button::~Button() {}

bool Button::inButton(int mouseX, int mouseY) {
    return (mouseX >= _buttonX && mouseX <= _buttonX + _width &&
            mouseY >= _buttonY && mouseY <= _buttonY + _height);
}

void Button::renderButton(SDL_Renderer *renderer, int R, int G, int B) {
    SDL_Rect buttonRect = {_buttonX, _buttonY, _width, _height};
    SDL_SetRenderDrawColor(renderer, R, G, B, 255);
    SDL_RenderFillRect(renderer, &buttonRect);
}