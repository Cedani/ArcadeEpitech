/*
** EPITECH PROJECT, 2021

** Visual Studio Live Share (Workspace)
** File description:
** Windows
*/

#include "../../include/sdl2/Windows.hpp"

Arcade::WindowsSDL::WindowsSDL(): window(nullptr), rend(nullptr)
{
    this->window = nullptr;
    this->rend = nullptr;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    if (TTF_Init() == -1) {
        printf("error initializing TTF: %s\n", SDL_GetError());
    }
}

Arcade::WindowsSDL::WindowsSDL(const WindowsSDL &other)
{
    window = other.window;
    rend = other.rend;
}

Arcade::WindowsSDL::~WindowsSDL()
{
    // this->closeWindow();
    // SDL_DestroyWindow(this->window);
}


void Arcade::WindowsSDL::openWindow()
{
    this->window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_FULLSCREEN);
    this->rend = SDL_CreateRenderer(this->window, -1, 0);
    SDL_SetRenderDrawColor(this->rend, 0, 0, 0, 255);
    SDL_RenderClear(this->rend);
}

void Arcade::WindowsSDL::closeWindow()
{
    SDL_DestroyRenderer(this->rend);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
}

void Arcade::WindowsSDL::clearWin()
{
    SDL_RenderClear(this->rend);
}

void Arcade::WindowsSDL::refreshWin()
{
    SDL_RenderPresent(this->rend);
}

void Arcade::WindowsSDL::drawText(const graphical_text_t &text)
{
    if (!text.toDraw)
        return;
    TTF_Font *font = TTF_OpenFont("Resources/Roboto/Roboto-Black.ttf", text.size);
    SDL_Color color = {text.color.r, text.color.g, text.color.b, 255};
    SDL_Surface *surf = TTF_RenderText_Solid(font, text.text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->rend, surf);
    SDL_Rect text_rect;
    text_rect.x = text.pos.x;
    text_rect.y = text.pos.y;
    text_rect.h = text.size + 4;
    text_rect.w = text.text.length() * (text.size * 2 / 4);
    SDL_SetRenderDrawColor(this->rend, 0, 0, 0, 255);
    SDL_RenderCopy(this->rend, texture, NULL, &text_rect);
    TTF_CloseFont(font);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
}

void Arcade::WindowsSDL::drawRectangle(const graphical_rectangle_t &rect)
{
    if (!rect.toDraw)
        return;
    SDL_Rect rec;
    rec.x = rect.pos.x;
    rec.y = rect.pos.y;
    rec.w = rect.size.x;
    rec.h = rect.size.y;
    SDL_SetRenderDrawColor(this->rend, rect.color.r, rect.color.g, rect.color.b, rect.color.a);
    SDL_RenderDrawRect(this->rend, &rec);
    if (rect.filled == true) {
        SDL_RenderFillRect(this->rend, &rec);
    }
    SDL_SetRenderDrawColor(this->rend, 0, 0, 0, 255);
}

void Arcade::WindowsSDL::drawSprite(const graphical_sprite_t &sprite)
{
    if (!sprite.toDraw)
        return;
    SDL_Texture *texture = IMG_LoadTexture(this->rend, sprite.path.c_str());
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Rect rec;

    rec.x = sprite.pos.x;
    rec.y = sprite.pos.y;
    rec.h = sprite.size.y;
    rec.w = sprite.size.x;
    if (sprite.scale.x != 1)
        rec.w = rec.w * sprite.scale.x;
    if (sprite.scale.y != 1)
        rec.h = rec.h * sprite.scale.y;
    SDL_RenderCopyEx(this->rend, texture, NULL, &rec, sprite.rotation, NULL, flip);
    SDL_DestroyTexture(texture);
}

void Arcade::WindowsSDL::showInputBox(const graphical_box_t &box)
{
    if (!box.toDraw)
        return;
    this->drawRectangle(graphical_rectangle_t(box.pos, box.size, false, graphical_color_t(), true));
    this->drawText(graphical_text_t(box.input, box.pos, 70, graphical_color_t(), true));
}

void Arcade::WindowsSDL::checkKey(std::vector<Arcade::key> &ret)
{
    for (int i = 97; i <= 122; i++)
        if (this->event.key.keysym.sym == i)
            ret.push_back(Arcade::key(i - 97));
    for (int i = 49; i <= SDLK_9; i++)
        if (this->event.key.keysym.sym == i)
            ret.push_back(Arcade::key(i - 22));
    if (this->event.key.keysym.sym == SDLK_0)
        ret.push_back(Arcade::key(KEY0));
    if (this->event.key.keysym.sym == 13)
        ret.push_back(Arcade::key(ENTER));
    if (this->event.key.keysym.sym == 27)
        ret.push_back(Arcade::key(ESCAPE));
    if (this->event.key.keysym.sym == 32)
        ret.push_back(Arcade::key(SPACE));
    if (this->event.key.keysym.sym == SDLK_UP)
        ret.push_back(Arcade::key(KEYUP));
    if (this->event.key.keysym.sym == SDLK_DOWN)
        ret.push_back(Arcade::key(KEYDOWN));
    if (this->event.key.keysym.sym == SDLK_RIGHT)
        ret.push_back(Arcade::key(KEYRIGHT));
    if (this->event.key.keysym.sym == SDLK_LEFT)
        ret.push_back(Arcade::key(KEYLEFT));
    if (this->event.key.keysym.sym == SDLK_BACKSPACE)
        ret.push_back(Arcade::key(BACKSPACE));
}

const std::vector<Arcade::key> Arcade::WindowsSDL::check()
{
    std::vector<Arcade::key> ret;
    if (!SDL_PollEvent(&this->event))
        return (ret);
    if (this->event.type == SDL_QUIT) {
        ret.push_back(ESCAPE);
        return (ret);
    }
    if (this->event.type == SDL_KEYDOWN)
        checkKey(ret);
    return (ret);
}

void Arcade::WindowsSDL::playSound(const std::string &path)
{
    (void)path;
}

extern "C" std::shared_ptr<Arcade::IGraphicalModule> entrypoint(void)
{
    return (std::make_shared<Arcade::WindowsSDL>());
}