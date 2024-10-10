#include "../inc/Render.hpp"

Render::Render():
    _renderer(NULL),
    _window(NULL)
{
}

Render::~Render(){
    if (this->_renderer)
        SDL_DestroyRenderer(this->_renderer);
    if (this->_window) {
        SDL_DestroyWindow(this->_window);
        SDL_Quit();
    }
};

Render::Render(const Render &cpy):
    _renderer(cpy._renderer),
    _window(cpy._window)
{

}

Render &Render::operator=(const Render &rhs)
{
    if (this != &rhs)
    {
        this->_renderer = rhs._renderer;
        this->_window = rhs._window;
    }
    return (*this);
}

SDL_Renderer* Render::getRenderer() const {
    return (this->_renderer);
}

void Render::init_sdl(const std::string& windowName, int windowWidth, int windowHeight){
    std::cout << "windowWidth" << windowWidth << std::endl;
    std::cout << "windowHeight" << windowHeight << std::endl;
    if (_renderer != NULL || _window != NULL)
        return ;
    //init sdl variables
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(std::string("Failed to init SDL: ") + std::string(SDL_GetError()));
    if (TTF_Init() == -1)
        throw std::runtime_error(std::string("Failed to init TTF: ") + std::string(SDL_GetError()));
    this->_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (!_window)
        throw std::runtime_error(std::string("Failed to create SDL window: ") + std::string(SDL_GetError()));

    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    if (!this->_renderer)
        throw std::runtime_error(std::string("Failed to create SDL renderer: ") + std::string(SDL_GetError()));
}


void    Render::writeText(const std::string& msg, const std::string& font, const SDL_Rect& rect, const SDL_Color& color, int size){
    TTF_Font* Font = TTF_OpenFont(font.c_str(), size);
    if (Font == NULL)
        throw std::runtime_error(std::string("Failed to open TTF Font: ") + std::string(SDL_GetError()));
    
    SDL_Surface* surfaceMsg = TTF_RenderText_Solid(Font, msg.c_str(), color);
    if (surfaceMsg == NULL)
        throw std::runtime_error(std::string("Failed to load TTF_RenderText_Solid  function: ") + std::string(SDL_GetError()));
    
    SDL_Texture* Message = SDL_CreateTextureFromSurface(this->_renderer, surfaceMsg);
    if (Message == NULL)
        throw std::runtime_error(std::string("Failed to create a texture from a surface: ") + std::string(SDL_GetError()));

    if (SDL_RenderCopy(this->_renderer, Message, NULL, &rect) != 0)
        throw std::runtime_error(std::string("Failed to render a copy: ") + std::string(SDL_GetError()));

    SDL_RenderPresent(this->_renderer);
    SDL_FreeSurface(surfaceMsg);
    SDL_DestroyTexture(Message);
    TTF_CloseFont(Font);
}

void Render::render_board() const
{
    // select brown color and clear the board with this color
    if (SDL_SetRenderDrawColor(this->_renderer, 205, 127, 50, 255) != 0)
        throw std::runtime_error(std::string("Failed to set render draw color: ") + std::string(SDL_GetError()));
    if (SDL_RenderClear(this->_renderer) != 0)
        throw std::runtime_error(std::string("Failed to clear the render: ") + std::string(SDL_GetError()));

    //select black color to draw lines
    if (SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255))
        throw std::runtime_error(std::string("Failed to set render draw color: ") + std::string(SDL_GetError()));

    // Draw grid of Board size + 1 ^ 2
    int line = BOARD_SIZE * (GRID_SIZE + 1);
    for (int x = MARGIN, i = 0; x < line + GRID_SIZE && i <= BOARD_SIZE; x += GRID_SIZE, i++)
    {
        // draw line on x and y axis
        if (SDL_RenderDrawLine(this->_renderer, x, MARGIN, x, line) != 0)
            throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));
        if (SDL_RenderDrawLine(this->_renderer, MARGIN, x, line , x) != 0)
            throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

    }
    //render the board
    SDL_RenderPresent(this->_renderer);
}


void    Render::erasePlayer(int y, int x) const {
    int x_square = x * GRID_SIZE + MARGIN - RADIUS;
    int y_square = y * GRID_SIZE + MARGIN - RADIUS;

    if (SDL_SetRenderDrawColor(this->_renderer, 205, 127, 50, 255) != 0)
        throw std::runtime_error(std::string("Failed to set render draw color: ") + std::string(SDL_GetError()));

    SDL_Rect rect = {x_square, y_square, RADIUS * 2, RADIUS * 2}; // x, y, width, height
    if (SDL_RenderFillRect(this->_renderer, &rect) != 0)
        throw std::runtime_error(std::string("Failed to set render a filled rect: ") + std::string(SDL_GetError()));
    if (SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255))
        throw std::runtime_error(std::string("Failed to set render draw color: ") + std::string(SDL_GetError()));

    int borderX = DIAMETER;
    if (x_square + borderX > MARGIN + (GRID_SIZE * BOARD_SIZE))
        borderX = RADIUS;

    int borderY = DIAMETER;
    if (y_square + borderY > MARGIN + (GRID_SIZE * BOARD_SIZE))
        borderY = RADIUS;

    int startX = 0;
    if (x_square < MARGIN)
        startX = RADIUS;

    int startY = 0;
    if (y_square < MARGIN)
        startY = RADIUS;

    if (SDL_RenderDrawLine(this->_renderer, x_square + startX , y_square + RADIUS, x_square + borderX, y_square + RADIUS) != 0)
        throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

    if (SDL_RenderDrawLine(this->_renderer, x_square + RADIUS, y_square + startY, x_square + RADIUS, y_square + borderY) != 0)
        throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

    SDL_RenderPresent(this->_renderer);
}


void Render::drawCircle(int centreX, int centreY) const {
    centreX = centreX * GRID_SIZE + MARGIN ;
    centreY = centreY * GRID_SIZE + MARGIN ;
    int x = RADIUS - 1;
    int y = 0;
    int dx = 1, dy = 1;
    int err = dx - (RADIUS * 2);

    while (x >= y){
        if (SDL_RenderDrawLine(this->_renderer, centreX + x, centreY - y, centreX + x, centreY + y) != 0)
            throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

        if (SDL_RenderDrawLine(this->_renderer, centreX - x, centreY - y, centreX - x, centreY + y) != 0)
            throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

        if (SDL_RenderDrawLine(this->_renderer, centreX + y, centreY - x, centreX + y, centreY + x) != 0)
            throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

        if (SDL_RenderDrawLine(this->_renderer, centreX - y, centreY - x, centreX - y, centreY + x) != 0)
            throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

        if (err <= 0){
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (RADIUS * 2);
        }
    }
    SDL_RenderPresent(this->_renderer);
}