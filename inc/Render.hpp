#ifndef __RENDER_HPP__
#define __RENDER_HPP__

# include <SDL.h>
# include <SDL_ttf.h>
# include <iostream>
# include "gomoku.hpp"
# include "utils.hpp"

class Render{
    public:
        Render();
        ~Render();
        
        Render(const Render &cpy);
        Render &operator=(const Render &rhs);

        SDL_Renderer* getRenderer() const;
        void    initSDL(const std::string& windowName, int windowWidth, int windowHeight);
        void    renderWin(uint16_t player) const;


        void    renderBoard() const;
        void    erasePlayer(int x, int y) const;
        void    drawCircle(int centreX, int centreY) const;
        void    writeText(const std::string& msg, const std::string& font, const SDL_Rect& rect, const SDL_Color& color, int size) const;

    private:
        SDL_Renderer *_renderer;
        SDL_Window *_window;
};

#endif