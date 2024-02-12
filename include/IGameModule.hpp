/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_
#include "Arcade.hpp"
#include <unordered_map>
#include <vector>

class Arcade::IGameModule {
    public:
        virtual ~IGameModule() = default;
    
        virtual void startGame() = 0;
        virtual void updateGame() = 0;
        virtual int check(const std::vector<Arcade::key>) = 0;
        virtual void setName(const std::string &name) = 0;
        virtual const std::vector<graphical_rectangle_t> getSpecials() = 0;
        virtual const std::vector<graphical_sprite_t> getSpecialSprite() = 0;
        virtual const std::vector<graphical_rectangle_t> getRectangles() = 0;
        virtual const std::vector<graphical_text_t> getTexts() = 0;
        virtual const std::vector<graphical_sprite_t> getSprites() = 0;
        virtual const std::vector<graphical_box_t> getBoxes() = 0;
        virtual const std::vector<std::string> getSounds() = 0;
        virtual void setVitesse(const float &) = 0;
        virtual float getVitesse() const = 0;
};

#endif /* !IGAMEMODULE_HPP_ */
