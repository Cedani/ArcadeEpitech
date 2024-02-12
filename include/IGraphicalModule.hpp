/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** IGraphicalModule
*/

#ifndef IGRAPHICALMODULE_HPP_
#define IGRAPHICALMODULE_HPP_
#include "Arcade.hpp"
#include <vector>

class Arcade::IGraphicalModule{
    public:
        virtual ~IGraphicalModule() = default;

        virtual void drawText(const graphical_text_t &text) = 0;
        virtual void drawSprite(const graphical_sprite_t &sprite) = 0;
        virtual void showInputBox(const graphical_box_t &box) = 0;
        virtual void drawRectangle(const graphical_rectangle_t &rect) = 0;
        virtual void clearWin() = 0;
        virtual void refreshWin() = 0;
        virtual const std::vector<Arcade::key> check() = 0;
        virtual void openWindow() = 0;
        virtual void closeWindow() = 0;
        virtual void playSound(const std::string &) = 0;
};

#endif /* !IGRAPHICALMODULE_HPP_ */
