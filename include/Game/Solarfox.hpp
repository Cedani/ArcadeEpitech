/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Solarfox
*/

#ifndef SOLARFOX_HPP_
#define SOLARFOX_HPP_
#include "../IGameModule.hpp"
#include "../IGraphicalModule.hpp"
#include "../Clock.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

class Arcade::Solarfox : public IGameModule {
    public:
        Solarfox();
        ~Solarfox();

        void startGame() final;
        void updateGame() final;
        int check(const std::vector<Arcade::key>) final;
        const std::vector<graphical_rectangle_t> getRectangles() final;
        const std::vector<graphical_text_t> getTexts() final;
        const std::vector<graphical_box_t> getBoxes() final;
        const std::vector<graphical_rectangle_t> getSpecials() final;
        const std::vector<graphical_sprite_t> getSprites() final;
        const std::vector<graphical_sprite_t> getSpecialSprite() final;
        void setName(const std::string &name) final;
        const std::vector<std::string> getSounds() final;
        void setVitesse(const float &) final;
        float getVitesse() const final;

    protected:
    private:
        int _scene;
        std::pair<std::string, graphical_rectangle_t> _cursor;
        bool _changed;
        std::vector<graphical_rectangle_t> _rectangles;
        std::map <std::string, graphical_text_t> _textes;
        std::vector <graphical_box_t> _boxes;
        std::vector <graphical_sprite_t> _sprites;
        Arcade::key _key;
        bool _incr;
        Arcade::key spaceShipDir;
        Arcade::key spaceShipOldDir;
        Arcade::key shootDir;

        std::map<int, Arcade::key> enemis;
        std::map<int, Arcade::Clock> enemisClock;
        std::map<int, Arcade::Clock> enemisMissileClock;
        Arcade::Clock shipClock;
        Arcade::Clock missileClock;
        std::pair<int, int> oldMissilePos;
        std::map<int, std::pair<Arcade::Clock, Arcade::key>> missileDir;
        int nbMissile;
        int score;
        int life;
        std::string _name;
        int nbrect;
        int lvl;

        int state = 0;

        void reloadSquare();
        void lifedecrease();
        void restart();
        std::vector<std::string> scoreArr;
        std::map<int, std::string> scoreMap;
};

#endif /* !SOLARFOX_HPP_ */
