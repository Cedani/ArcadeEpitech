/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <functional>
#include "../Errors.hpp"
#include "../IGameModule.hpp"
#include "../Arcade.hpp"
#include "../Clock.hpp"

// x=30 y=30
class Arcade::Nibbler : public IGameModule{
    public:
        Nibbler();
        ~Nibbler();

        void startGame() final;
        void updateGame() final;
        int check(const std::vector<Arcade::key>) final;
        const std::vector<graphical_rectangle_t> getRectangles() final;
        const std::vector<graphical_text_t> getTexts() final;
        const std::vector<graphical_sprite_t> getSprites() final;
        const std::vector<graphical_box_t> getBoxes() final;
        const std::vector<graphical_rectangle_t> getSpecials() final;
        const std::vector<graphical_sprite_t> getSpecialSprite() final;
        void createMap(const std::string &);
        bool toCheckSnakeMovement();
        void moveSnake();
        void calcPos();
        void moveSnake(float newX, float newY);
        void change(float &nb);
        void change(float &pos, float &newP);
        void popFood();
        void setName(const std::string &name) final;
        const std::vector<std::string> getSounds() final;
        void setVitesse(const float &) final;
        float getVitesse() const final;
    protected:
        const float startX = 230;
        const float startY = 100;
        std::size_t idxY;
        std::vector <graphical_rectangle_t> _snake;
        std::vector <graphical_rectangle_t> _map;
        std::vector <graphical_rectangle_t> _emptySpace;
        std::vector<std::string> _myMap;
        std::vector<graphical_vector_t> _snakePos;
        Clock _clock;
        int test = 0;
        std::vector <graphical_sprite_t> _sprites;
        key direction = KEY0;
        std::string _name;
};

#endif /* !NIBBLER_HPP_ */
