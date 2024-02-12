/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** Window
*/

#ifndef WINDOWS_HPP_
#define WINDOWS_HPP_
#include "../IGraphicalModule.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class Arcade::WindowsSDL : public IGraphicalModule {
    public:
        WindowsSDL();
        WindowsSDL(const WindowsSDL &);
        ~WindowsSDL();

        void drawText(const graphical_text_t &text) final;
        void drawSprite(const graphical_sprite_t &sprite) final;
        void showInputBox(const graphical_box_t &box) final;
        void drawRectangle(const graphical_rectangle_t &rect) final;
        void clearWin() final;
        void refreshWin() final;
        const std::vector<Arcade::key> check() final;
        void checkKey(std::vector<Arcade::key> &ret);
        void openWindow() final;
        void closeWindow() final;
        void analyseEvent();
        void playSound(const std::string &) final;
    protected:
    private:
        SDL_Window *window;
        SDL_Renderer *rend;
        SDL_Event event;
};
#endif /* !WINDOWS_HPP_ */
// cursorUp