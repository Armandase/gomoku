#ifndef __RENDER_HPP__
#define __RENDER_HPP__

# include <SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <iostream>
# include "gomoku.hpp"

class Render{
    public:
        Render();
        ~Render();
        
        Render(const Render &cpy);
        Render &operator=(const Render &rhs);

        SDL_Renderer* getRenderer() const;
        void    init_sdl(const std::string& windowName, int windowWidth, int windowHeight);

        void    writeText(const std::string& msg, const std::string& font, const SDL_Rect& rect, const SDL_Color& color, int size);
        void    render_board() const;
        void    erasePlayer(int y, int x) const;
        void    drawCircle(int centreX, int centreY) const;

    private:
        SDL_Renderer *_renderer;
        SDL_Window *_window;
};

#endif