/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** WindowsNcurses
*/

#ifndef WINDOWS_HPP_
#define WINDOWS_HPP_
#include "../IGraphicalModule.hpp"
#include <ncurses.h>
#include <unordered_map>

class Arcade::WindowsNcurses : public IGraphicalModule{
    public:
        WindowsNcurses();
        WindowsNcurses(const WindowsNcurses &);
        ~WindowsNcurses();
        void drawText(const graphical_text_t &text) final;
        void drawSprite(const graphical_sprite_t &sprite) final;
        void showInputBox(const graphical_box_t &box) final;
        void drawRectangle(const graphical_rectangle_t &rect) final;
        void clearWin();
        void refreshWin();
        const std::vector<Arcade::key> check();
        void openWindow();
        void closeWindow();
        void playSound(const std::string &) final;
    protected:
        std::unordered_map<int, std::pair<WINDOW *, graphical_rectangle_t>> windowMapRect;
        std::unordered_map<int, std::pair<WINDOW *, graphical_box_t>> windowMapBox;

};

#endif /* !WINDOWS_HPP_ */
