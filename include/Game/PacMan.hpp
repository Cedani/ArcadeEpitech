/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** PacMan
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_
#include "../IGameModule.hpp"
#include "../Arcade.hpp"
#include "../Clock.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

class Arcade::PacMan : public IGameModule {
    public:
        PacMan();
        ~PacMan();

        void startGame() final;
        void updateGame() final;
        int check(const std::vector<Arcade::key>) final;
        void bonusSpawn();
        void checkNextLvl();
        int collisionMap();
        void checkDamage();
        void pacGum();
        void deadPac();
        void findHome1();
        void findHome2();
        void findHome3();
        void findHome4();
        void pushThat();
        void collisionMapPhantom1();
        void collisionMapPhantom2();
        void collisionMapPhantom3();
        void collisionMapPhantom4();
        void find_pacman();
        void teleportation();
        void rotatePac();
        void phatomMov();
        void saveScore();
        const std::vector<graphical_rectangle_t> getSpecials() final;
        bool has_collision(graphical_sprite_t &spr1, graphical_sprite_t &spr2);
        const std::vector<graphical_rectangle_t> getRectangles() final;
        const std::vector<graphical_text_t> getTexts() final;
        const std::vector<graphical_box_t> getBoxes() final;
        const std::vector<graphical_sprite_t> getSprites() final;
        const std::vector<graphical_sprite_t> getSpecialSprite() final;
        void setName(const std::string &name) final;
        const std::vector<std::string> getSounds() final;
        void setVitesse(const float &) final;
        float getVitesse() const final;
    protected:
    private:
        std::vector<std::string> scoreArr;
        // std::map<int, std::string> scoreMap;
        std::vector<std::pair<std::string, int>> scoreMap;

        bool endLevel;
        bool killPac;
        int score;

        graphical_sprite_t bonusSprite;

        graphical_vector_t pac_pos;
        graphical_vector_t pacDir;
        graphical_vector_t temppacDir;
        graphical_sprite_t pacSprite;

        graphical_vector_t tp1;
        graphical_vector_t tp2;

        graphical_sprite_t phSprite1;
        graphical_vector_t phPos1;
        graphical_vector_t phDir1;
        bool vuln1;
        bool dead1;
        bool out1;

        graphical_sprite_t phSprite2;
        graphical_vector_t phPos2;
        graphical_vector_t phDir2;
        bool vuln2;
        bool dead2;
        bool out2;

        graphical_sprite_t phSprite3;
        graphical_vector_t phPos3;
        graphical_vector_t phDir3;
        bool vuln3;
        bool dead3;
        bool out3;

        graphical_sprite_t phSprite4;
        graphical_vector_t phPos4;
        graphical_vector_t phDir4;
        bool vuln4;
        bool dead4;
        bool out4;
        
        int nbrWay;
        graphical_vector_t memoryDir;

        graphical_vector_t spawn;
        graphical_vector_t prison;
        graphical_vector_t startPac;

        std::vector<std::string> _map;
        int _scene;
        std::pair<std::string, graphical_rectangle_t> _cursor;
        bool _changed;
        std::vector<graphical_rectangle_t> _snake;
        std::vector<graphical_rectangle_t> _rectangles;
        // std::vector<graphical_rectangle_t> _rectangles;
        std::vector <graphical_text_t> _textes;
        std::vector <graphical_box_t> _boxes;
        std::vector <graphical_sprite_t> _sprites;
        Arcade::key _key;
        std::unordered_map<std::string, Clock> _clockes;
        bool _incr;
        int test_index;
        std::string _name;
        float _speed;
        bool _setSpeed = false;
};

#endif /* !PACMAN_HPP_ */
