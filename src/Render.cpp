#include "../inc/Render.hpp"
#include "../inc/Game.hpp"

Render::Render()
    : _renderer(NULL)
    , _window(NULL)
{
}

Render::~Render()
{
    if (this->_renderer)
        SDL_DestroyRenderer(this->_renderer);
    if (this->_window) {
        SDL_DestroyWindow(this->_window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
};

Render::Render(const Render& cpy)
    : _renderer(cpy._renderer)
    , _window(cpy._window)
{
}

Render& Render::operator=(const Render& rhs)
{
    if (this != &rhs) {
        this->_renderer = rhs._renderer;
        this->_window = rhs._window;
    }
    return (*this);
}

SDL_Renderer* Render::getRenderer() const
{
    return (this->_renderer);
}

void Render::initSDL(const std::string& windowName, int windowWidth, int windowHeight)
{
    if (_renderer != NULL || _window != NULL)
        return;
    // init sdl variables
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(std::string("Failed to init SDL: ") + std::string(SDL_GetError()));
    if (TTF_Init() == -1)
        throw std::runtime_error(std::string("Failed to init TTF: ") + std::string(SDL_GetError()));
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
        throw std::runtime_error(std::string("Failed to init SDL_Image: ") + std::string(SDL_GetError()));
    this->_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (!_window)
        throw std::runtime_error(std::string("Failed to create SDL window: ") + std::string(SDL_GetError()));

    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    if (!this->_renderer)
        throw std::runtime_error(std::string("Failed to create SDL renderer: ") + std::string(SDL_GetError()));
}

void Render::writeText(const std::string& msg, const std::string& font, const SDL_Rect& rect, const SDL_Color& color, int size) const
{
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

void Render::renderImage(const std::string& path, const SDL_Rect* rect)
{
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface)
        throw std::runtime_error(std::string("Failed to load Image: ") + std::string(SDL_GetError()));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    if (!texture)
        throw std::runtime_error(std::string("Failed to load Texture: ") + std::string(SDL_GetError()));
    SDL_RenderCopy(this->_renderer, texture, NULL, rect);
    SDL_RenderPresent(this->_renderer);
    SDL_DestroyTexture(texture);
}

void Render::renderBoard(Game& game) const
{
    int cnt = 0;
    SDL_SetRenderDrawColor(this->_renderer, 205, 127, 50, 255);
    SDL_RenderClear(this->_renderer);
    SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);

    const int line = BOARD_DIMENSIONS + MARGIN;
    for (int x = MARGIN, i = 0; x <= line + GRID_SIZE && i < BOARD_SIZE; x += GRID_SIZE, i++) {
        // draw lines
        SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(this->_renderer, x, MARGIN, x, line);
        SDL_RenderDrawLine(this->_renderer, MARGIN, x, line, x);

        // draw number around the board
        SDL_SetRenderDrawColor(this->_renderer, 205, 127, 50, 255);
        SDL_Color textColor = BLACK_COLOR;

        SDL_Rect msg_rect_x = { x - (intlen(cnt) * (MARGIN / 3) / 2), 0 + MARGIN / 10, intlen(cnt) * (MARGIN / 4), MARGIN / 2 };
        SDL_RenderFillRect(this->_renderer, &msg_rect_x);
        writeText(std::to_string(cnt), "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect_x, textColor, FONT_SIZE);

        SDL_Rect msg_rect_y = { 0 + MARGIN / 10, x - (intlen(cnt) * (MARGIN / 3) / 2), intlen(cnt) * (MARGIN / 4), MARGIN / 2 };
        SDL_RenderFillRect(this->_renderer, &msg_rect_y);
        writeText(std::to_string(cnt), "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect_y, textColor, FONT_SIZE);

        cnt++;
    }
    renderCapture(game.getCapture(WHITE), game.getCapture(BLACK));
    SDL_RenderPresent(this->_renderer);
}

void Render::erasePlayer(int x, int y) const
{
    const int x_square = x * GRID_SIZE + MARGIN - RADIUS;
    const int y_square = y * GRID_SIZE + MARGIN - RADIUS;

    if (SDL_SetRenderDrawColor(this->_renderer, 205, 127, 50, 255) != 0)
        throw std::runtime_error(std::string("Failed to set render draw color: ") + std::string(SDL_GetError()));

    SDL_Rect rect = { x_square, y_square, RADIUS * 2, RADIUS * 2 }; // x, y, width, height
    if (SDL_RenderFillRect(this->_renderer, &rect) != 0)
        throw std::runtime_error(std::string("Failed to set render a filled rect: ") + std::string(SDL_GetError()));
    if (SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255))
        throw std::runtime_error(std::string("Failed to set render draw color: ") + std::string(SDL_GetError()));

    int borderX = DIAMETER;
    if (x_square + borderX > MARGIN + BOARD_DIMENSIONS)
        borderX = RADIUS;

    int borderY = DIAMETER;
    if (y_square + borderY > MARGIN + BOARD_DIMENSIONS)
        borderY = RADIUS;

    int startX = 0;
    if (x_square < MARGIN)
        startX = RADIUS;

    int startY = 0;
    if (y_square < MARGIN)
        startY = RADIUS;

    if (SDL_RenderDrawLine(this->_renderer, x_square + startX, y_square + RADIUS, x_square + borderX, y_square + RADIUS) != 0)
        throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

    if (SDL_RenderDrawLine(this->_renderer, x_square + RADIUS, y_square + startY, x_square + RADIUS, y_square + borderY) != 0)
        throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

    SDL_RenderPresent(this->_renderer);
}

void Render::drawCircle(int centreX, int centreY) const
{
    int x = RADIUS - 1;
    int y = 0;
    int dx = 1, dy = 1;
    int err = dx - (RADIUS * 2);

    while (x >= y) {
        if (SDL_RenderDrawLine(this->_renderer, centreX + x, centreY - y, centreX + x, centreY + y) != 0)
            throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

        if (SDL_RenderDrawLine(this->_renderer, centreX - x, centreY - y, centreX - x, centreY + y) != 0)
            throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

        if (SDL_RenderDrawLine(this->_renderer, centreX + y, centreY - x, centreX + y, centreY + x) != 0)
            throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

        if (SDL_RenderDrawLine(this->_renderer, centreX - y, centreY - x, centreX - y, centreY + x) != 0)
            throw std::runtime_error(std::string("Failed to render draw a line") + std::string(SDL_GetError()));

        if (err <= 0) {
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

void Render::drawStoneAssets(int centreX, int centreY, int player)
{
#if defined(WHITE_STONE_PATH) && defined(BLACK_STONE_PATH)

    // const SDL_Rect rect = { int(centreX - RADIUS * 1.5), int(centreY - RADIUS * 1.5), int(RADIUS * 3), int(RADIUS * 3) };
    const SDL_Rect rect = { int(centreX - RADIUS), int(centreY - RADIUS), int(RADIUS * 2), int(RADIUS * 2) };
    if (player == WHITE)
        renderImage(WHITE_STONE_PATH, &rect);
    else
        renderImage(BLACK_STONE_PATH, &rect);
#endif
}

void Render::renderWin(uint16_t player) const
{
    std::string message;
    player == BLACK ? message = "black wins" : message = "white wins";
    // reset game's Game with game's color
    SDL_SetRenderDrawColor(_renderer, 205, 127, 50, 255);
    // SDL_RenderClear(_renderer);

    // select text color and where it should be placed and his size
    const SDL_Color textColor = { 80, 0, 80, 255 };
    const SDL_Rect msg_rect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3 };
    writeText(message, "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", msg_rect, textColor, FONT_SIZE);
}

void Render::renderMenu(std::vector<std::tuple<Button, std::string>>& buttons) const
{
    if (buttons.empty())
        return;
    Button IA = std::get<0>(buttons[0]);
    int buttonWidth = IA.getWidth();
    int buttonHeight = IA.getHeight();
    int textMargin = 10;
    SDL_SetRenderDrawColor(this->_renderer, 205, 127, 50, 255);
    SDL_RenderClear(this->_renderer);
    for (auto& button : buttons) {
        Button& btn = std::get<0>(button);
        std::string& text = std::get<1>(button);

        SDL_SetRenderDrawColor(this->_renderer, 205, 127, 50, 255);
        btn.renderButton(this->_renderer, 205, 127, 50);
        const SDL_Rect playerText = { btn.getButtonX(), btn.getButtonY(), buttonWidth - textMargin, buttonHeight };

        SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(this->_renderer, &playerText);

        writeText(std::get<1>(button), "fonts/OpenSans-Bold.ttf",
            playerText, BLACK_COLOR, 50);
    }

    const SDL_Rect titleText = { SCREEN_WIDTH / 2 - (buttonWidth / 2), MARGIN, buttonWidth, buttonHeight };
    writeText("GOMOKU", "fonts/OpenSans-Bold.ttf",
        titleText, BLACK_COLOR, FONT_SIZE);

    const SDL_Rect creditText = { SCREEN_WIDTH - 310, SCREEN_HEIGHT - 70, 300, 50 };
    writeText("made by adamiens & nlocusso", "fonts/OpenSans-Bold.ttf",
        creditText, BLACK_COLOR, 50);

    SDL_RenderPresent(this->_renderer);
}

void Render::renderCapture(uint16_t p1Capture, uint16_t p2Capture) const
{

    // RENDER P1 CAPTURES
    const SDL_Rect p1rect = { MARGIN + BOARD_DIMENSIONS, SCREEN_HEIGHT / 5, OFFSET, GRID_SIZE };
    writeText(" WHITE CAPTURES ", "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", p1rect, BLACK_COLOR, FONT_SIZE);

    SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);

    for (int i = 1; i < p1Capture * 2 + 1; i++) {
        if (i <= 5)
            drawCircle((MARGIN + BOARD_DIMENSIONS) + (i * RADIUS * 2) + i * 10, SCREEN_HEIGHT / 5 + GRID_SIZE + RADIUS);
        else
            drawCircle((MARGIN + BOARD_DIMENSIONS) + ((i - 5) * RADIUS * 2) + (i - 5) * 10, SCREEN_HEIGHT / 5 + GRID_SIZE + RADIUS * 3);
    }

    // RENDER P2 CAPTURES
    const SDL_Rect p2rect = { MARGIN + BOARD_DIMENSIONS, SCREEN_HEIGHT / 5 * 3, OFFSET, GRID_SIZE };
    writeText(" BLACK CAPTURES ", "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", p2rect, BLACK_COLOR, FONT_SIZE);

    SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);

    for (int i = 1; i < p2Capture * 2 + 1; i++) {
        if (i <= 5)
            drawCircle((MARGIN + BOARD_DIMENSIONS) + (i * RADIUS * 2) + i * 10, SCREEN_HEIGHT / 5 * 3 + GRID_SIZE + RADIUS);
        else
            drawCircle((MARGIN + BOARD_DIMENSIONS) + ((i - 5) * RADIUS * 2) + (i - 5) * 10, SCREEN_HEIGHT / 5 * 3 + GRID_SIZE + RADIUS * 3);
    }

    SDL_RenderPresent(this->_renderer);
}

void Render::renderTime(const std::string& timeTaken) const
{
    const SDL_Rect timeTakenRect = { MARGIN + BOARD_DIMENSIONS + 1, SCREEN_HEIGHT / 10 * 9, OFFSET, GRID_SIZE };
    SDL_SetRenderDrawColor(this->_renderer, 205, 127, 50, 255);
    SDL_RenderFillRect(this->_renderer, &timeTakenRect);

    SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
    std::string timeTakenStr = " Time: " + timeTaken + "ms ";
    writeText(timeTakenStr, "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        timeTakenRect, BLACK_COLOR, FONT_SIZE);

    SDL_RenderPresent(this->_renderer);
}

void Render::eraseCapture()
{
    SDL_SetRenderDrawColor(_renderer, 205, 127, 50, 255);
    for (int i = 1; i < 11; i++) {
        if (i <= 5) {
            drawCircle((MARGIN + BOARD_DIMENSIONS) + (i * RADIUS * 2) + i * 10, SCREEN_HEIGHT / 5 + GRID_SIZE + RADIUS);
            drawCircle((MARGIN + BOARD_DIMENSIONS) + (i * RADIUS * 2) + i * 10, SCREEN_HEIGHT / 5 * 3 + GRID_SIZE + RADIUS);
        } else {
            drawCircle((MARGIN + BOARD_DIMENSIONS) + ((i - 5) * RADIUS * 2) + (i - 5) * 10, SCREEN_HEIGHT / 5 + GRID_SIZE + RADIUS * 3);
            drawCircle((MARGIN + BOARD_DIMENSIONS) + ((i - 5) * RADIUS * 2) + (i - 5) * 10, SCREEN_HEIGHT / 5 * 3 + GRID_SIZE + RADIUS * 3);
        }
    }
    SDL_RenderPresent(_renderer);
}

void Render::drawRedCross(int x, int y) {
    SDL_SetRenderDrawColor(this->_renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(this->_renderer, x - RADIUS, y - RADIUS, x + RADIUS, y + RADIUS);
    SDL_RenderDrawLine(this->_renderer, x - RADIUS, y + RADIUS, x + RADIUS, y - RADIUS);
    SDL_RenderPresent(this->_renderer);
}

void Render::drawEmptyCross(int x, int y) {
    SDL_SetRenderDrawColor(_renderer, 205, 127, 50, 255);
    SDL_RenderDrawLine(this->_renderer, x - RADIUS, y - RADIUS, x + RADIUS, y + RADIUS);
    SDL_RenderDrawLine(this->_renderer, x - RADIUS, y + RADIUS, x + RADIUS, y - RADIUS);
    SDL_RenderPresent(this->_renderer);
}