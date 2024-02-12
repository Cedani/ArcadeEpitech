/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Solarfox
*/

#include "../../../include/Game/Solarfox.hpp"
#include <math.h>
#include <iostream>
#include <fstream>

Arcade::Solarfox::Solarfox() : spaceShipDir(KEY0), spaceShipOldDir(KEY0)
{
    enemis[0] = (KEYLEFT);
    enemis[1] = (KEYRIGHT);
    enemis[2] = (KEYUP);
    enemis[3] = (KEYDOWN);
    Arcade::Clock clock0;
    Arcade::Clock clock1;
    Arcade::Clock clock2;
    Arcade::Clock clock3;
    Arcade::Clock clock4;
    Arcade::Clock clock5;
    Arcade::Clock clock6;
    Arcade::Clock clock7;

    enemisClock[0] = clock0;
    enemisClock[1] = clock1;
    enemisClock[2] = clock2;
    enemisClock[3] = clock3;
    enemisMissileClock[0] = clock4;
    enemisMissileClock[1] = clock5;
    enemisMissileClock[2] = clock6;
    enemisMissileClock[3] = clock7;

    oldMissilePos.second = 0;
    oldMissilePos.first = 0;

    nbMissile = 0;
    life = 3;
    score = 0;
    nbrect = 15;
    lvl = 0;
    state = 0;
}

Arcade::Solarfox::~Solarfox()
{
}

void Arcade::Solarfox::startGame()
{

    _rectangles.push_back(graphical_rectangle_t(graphical_vector_t(500, 100), graphical_vector_t(900, 900), false, graphical_color_t(255, 165, 0)));
    _sprites.push_back(graphical_sprite_t("Resources/Image/solarfox/spaceship.png", graphical_vector_t(950, 590), graphical_vector_t(70, 70)));
    _sprites.back().toDraw = true;
    _sprites.push_back(graphical_sprite_t("Resources/Image/solarfox/noticesolarfox.png", graphical_vector_t(1550, 500), graphical_vector_t(163, 195)));
    _sprites.back().toDraw = true;
    _sprites.push_back(graphical_sprite_t("Resources/Image/solarfox/enemi.png", graphical_vector_t(1000, 1000 - 58), graphical_vector_t(104, 60)));
    _sprites.back().toDraw = true;
    _sprites.push_back(graphical_sprite_t("Resources/Image/solarfox/enemiup.png", graphical_vector_t(1000, 100), graphical_vector_t(104, 60)));
    _sprites.back().toDraw = true;
    _sprites.push_back(graphical_sprite_t("Resources/Image/solarfox/enemileft.png", graphical_vector_t(1400 - 60, 1000 - 58), graphical_vector_t(60, 104)));
    _sprites.back().toDraw = true;
    _sprites.push_back(graphical_sprite_t("Resources/Image/solarfox/enemiright.png", graphical_vector_t(500, 1000 - 58), graphical_vector_t(60, 104)));
    _sprites.back().toDraw = true;
    _sprites.push_back(graphical_sprite_t("Resources/Image/solarfox/missilealli.png", graphical_vector_t(100, 100), graphical_vector_t(26, 48)));
    _sprites.back().toDraw = false;
    _textes.insert(std::pair<std::string, graphical_text_t>("Score:", graphical_text_t("Score:", graphical_vector_t(100, 100, 0), 30, graphical_color_t())));
    _textes.insert(std::pair<std::string, graphical_text_t>("sc", graphical_text_t(std::to_string(score), graphical_vector_t(200, 100, 0), 30, graphical_color_t())));
    _textes.insert(std::pair<std::string, graphical_text_t>("life:", graphical_text_t("life:", graphical_vector_t(100, 300, 0), 30, graphical_color_t(255, 50, 50))));
    _textes.insert(std::pair<std::string, graphical_text_t>("lf", graphical_text_t(std::to_string(life), graphical_vector_t(170, 300, 0), 30, graphical_color_t(255, 50, 50))));
    _textes.insert(std::pair<std::string, graphical_text_t>("level:", graphical_text_t("level:", graphical_vector_t(100, 200, 0), 30, graphical_color_t(50, 255, 50))));
    _textes.insert(std::pair<std::string, graphical_text_t>("lv", graphical_text_t(std::to_string(lvl), graphical_vector_t(190, 200, 0), 30, graphical_color_t(50, 255, 50))));

    for (int i = 0; i < 20; i++)
    {
        if (i < 15)
        {
            _rectangles.push_back(graphical_rectangle_t(graphical_vector_t((rand() % 700) + 600, (rand() % 700) + 200), graphical_vector_t(25, 25), true, graphical_color_t(50, 50, 255)));
        }
        else
        {
            _rectangles.push_back(graphical_rectangle_t(graphical_vector_t((rand() % 700) + 600, (rand() % 700) + 200), graphical_vector_t(25, 25), true, graphical_color_t(255, 50, 50)));
        }
    }
    if (_rectangles.empty() == false)
        for (auto &e : _rectangles)
            e.toDraw = true;

}

void Arcade::Solarfox::updateGame()
{
    if (state == 0)
    {
        std::size_t i = 0;
        int t = 0;

        if (life == 0)
        {
            _textes.clear();
            _rectangles.clear();
            _sprites.clear();
            _rectangles.push_back(graphical_rectangle_t(graphical_vector_t(500, 100), graphical_vector_t(900, 900), false, graphical_color_t(255, 165, 0)));
            _textes.insert(std::pair<std::string, graphical_text_t>("To restart press R", graphical_text_t("To restart press R", graphical_vector_t(100, 100, 0), 30, graphical_color_t())));
            _textes.insert(std::pair<std::string, graphical_text_t>("Your score:", graphical_text_t("Your score" + _name + ":" + std::to_string(score), graphical_vector_t(850, 300, 0), 30, graphical_color_t())));
            lvl++;
            state++;

            std::ifstream file;
            std::string tmp;
            std::string buffer;

            scoreArr.clear();
            scoreMap.clear();
            file.open("Resources/Leaderords/leaderboardSolarFox.txt");
            if (!file)
                exit(84);
            while (getline(file, tmp)) {
                scoreArr.push_back(tmp);
            }
            for (; scoreArr.size() != 0;)
            {
                scoreMap[std::stoi(scoreArr.back().substr(0, scoreArr.back().find(" ") + 1))] = scoreArr.back().substr(scoreArr.back().find(" ") + 1, scoreArr.back().size());
                scoreArr.pop_back();
            }
            int j = 5;
            file.close();

            std::ofstream myfile;
            myfile.open("Resources/Leaderords/leaderboardSolarFox.txt", std::ofstream::out | std::ofstream::trunc);
            myfile.close();
            myfile.open("Resources/Leaderords/leaderboardSolarFox.txt");
            for (auto &e : scoreMap)
            {
                j--;
                if (score <= e.first)
                {
                    _textes.insert(std::pair<std::string, graphical_text_t>(std::to_string(j), graphical_text_t(std::to_string(j) + +": " + "you" + " " + std::to_string(score), graphical_vector_t(850, 400 + j * 50, 0), 30, graphical_color_t())));
                    if (j != 4)
                    {
                        if (_name == "")
                        {
                            myfile << std::to_string(score) + " " + "max" << std::endl;
                        }
                        else
                        {
                            myfile << std::to_string(score) + " " + "test" << std::endl;
                        }
                    }
                    score = 10000;
                    j--;
                }
                if (j != 4)
                    myfile << std::to_string(e.first) + " " + e.second << std::endl;
                _textes.insert(std::pair<std::string, graphical_text_t>(std::to_string(j), graphical_text_t(std::to_string(j) + ": " + e.second + " " + std::to_string(e.first), graphical_vector_t(850, 400 + j * 50, 0), 30, graphical_color_t())));
            }
            scoreMap.clear();
            scoreArr.clear();
            score = 0;
            if (_textes.empty() == false)
                for (auto &e : _textes)
                    e.second.toDraw = true;
        }
        if (nbrect == 0)
            reloadSquare();
        if (_textes.empty() == false)
            for (auto &e : _textes)
                e.second.toDraw = true;

        _textes["sc"].text = std::to_string(score);
        _textes["lf"].text = std::to_string(life);
        _textes["lv"].text = std::to_string(lvl);
        for (auto &e : _sprites)
        {
            i++;
            t = 0;
            if (e.toDraw == false)
                continue;
            if (i >= 3 && i <= 6)
            {
                if (e.pos.x < _sprites.front().pos.x + _sprites.front().size.x && e.pos.x + e.size.x > _sprites.front().pos.x && e.pos.y < _sprites.front().pos.y + _sprites.front().size.y && e.size.y + e.pos.y > _sprites.front().pos.y) {
                    lifedecrease();
                }
                if (enemisClock[i - 3].getElapsedTime() > 2000 + (i - 3) * 2000)
                {
                    if (enemis[i - 3] == KEYLEFT)
                        e.pos.x -= 1;
                    if (enemis[i - 3] == KEYRIGHT)
                        e.pos.x += 1;
                    if (enemis[i - 3] == KEYUP)
                        e.pos.y -= 1;
                    if (enemis[i - 3] == KEYDOWN)
                        e.pos.y += 1;
                    if (e.pos.x < 500 && enemis[i - 3] == KEYLEFT)
                        enemis[i - 3] = KEYRIGHT;
                    if (e.pos.x > 1400 - 103 && enemis[i - 3] == KEYRIGHT)
                        enemis[i - 3] = KEYLEFT;
                    if (e.pos.y < 100 && enemis[i - 3] == KEYUP)
                        enemis[i - 3] = KEYDOWN;
                    if (e.pos.y > 1000 - 104 && enemis[i - 3] == KEYDOWN)
                        enemis[i - 3] = KEYUP;
                    enemisClock[i - 3].restart();
                }
                if (sqrt(pow(e.pos.x - _sprites.front().pos.x, 2) + pow(e.pos.y - _sprites.front().pos.y, 2)) < 400 && enemisMissileClock[i - 3].getElapsedTime() > 1000000)
                {
                    if (i - 3 == 0)
                        _sprites.push_back(graphical_sprite_t("Resources/Image/solarfox/missile.png", graphical_vector_t(e.pos.x, e.pos.y), graphical_vector_t(27, 66)));
                    else if (i - 3 == 1)
                        _sprites.push_back(graphical_sprite_t("Resources/Image/solarfox/missiledown.png", graphical_vector_t(e.pos.x, e.pos.y), graphical_vector_t(27, 66)));
                    else if (i - 3 == 2)
                        _sprites.push_back(graphical_sprite_t("Resources/Image/solarfox/missileright.png", graphical_vector_t(e.pos.x, e.pos.y), graphical_vector_t(66, 27)));
                    else if (i - 3 == 3)
                        _sprites.push_back(graphical_sprite_t("Resources/Image/solarfox/missileleft.png", graphical_vector_t(e.pos.x, e.pos.y), graphical_vector_t(66, 27)));
                    _sprites.back().toDraw = true;
                    Arcade::Clock temp;
                    if (i - 3 == 0)
                    {
                        missileDir[nbMissile].second = KEYUP;
                        missileDir[nbMissile].first = temp;
                    }
                    else if (i - 3 == 1)
                    {
                        missileDir[nbMissile].second = KEYDOWN;
                        missileDir[nbMissile].first = temp;
                    }
                    else if (i - 3 == 2)
                    {
                        missileDir[nbMissile].second = KEYLEFT;
                        missileDir[nbMissile].first = temp;
                    }
                    else if (i - 3 == 3)
                    {
                        missileDir[nbMissile].second = KEYRIGHT;
                        missileDir[nbMissile].first = temp;
                    }
                    nbMissile++;
                    enemisMissileClock[i - 3].restart();
                }
            }
            if (i == 7 && missileClock.getElapsedTime() > 2000 && e.toDraw)
            {
                if (shootDir == KEYUP || shootDir == KEY0)
                    e.pos.y -= 2.5;
                if (shootDir == KEYDOWN)
                    e.pos.y += 2.5;
                if (shootDir == KEYLEFT)
                    e.pos.x -= 2.5;
                if (shootDir == KEYRIGHT)
                    e.pos.x += 2.5;
                if (sqrt(pow(oldMissilePos.first - e.pos.x, 2) + pow(oldMissilePos.second - e.pos.y, 2)) > 200)
                {
                    e.toDraw = false;
                }
                missileClock.restart();
                for (auto &a : _rectangles)
                {
                    if (a.toDraw == false)
                        continue;
                    if (e.pos.x < a.pos.x + a.size.x && e.pos.x + e.size.x > a.pos.x && e.pos.y < a.pos.y + a.size.y && e.size.y + e.pos.y > a.pos.y)
                    {
                        a.toDraw = false;
                        if (a.color.b == 255)
                        {
                            e.toDraw = false;
                            score += 2;
                            nbrect -= 1;
                        }
                        else if (a.color.g != 165)
                        {
                            e.toDraw = false;
                            lifedecrease();
                        }
                    }
                }
            }
            if (i > 7 && i != _sprites.size() + 1)
            {
                if (missileDir[i - 8].first.getElapsedTime() > 2000)
                {
                    if (missileDir[i - 8].second == KEYUP)
                    {
                        if (e.pos.y > 100)
                            e.pos.y -= 0.5;
                        else
                            e.toDraw = false;
                    }
                    if (missileDir[i - 8].second == KEYDOWN)
                    {
                        if (e.pos.y < 1000 - 65)
                            e.pos.y += 0.5;
                        else
                            e.toDraw = false;
                    }
                    if (missileDir[i - 8].second == KEYLEFT)
                    {
                        if (e.pos.x > 500)
                            e.pos.x -= 0.5;
                        else
                            e.toDraw = false;
                    }
                    if (missileDir[i - 8].second == KEYRIGHT)
                    {
                        if (e.pos.x < 1400 - 65)
                            e.pos.x += 0.5;
                        else
                            e.toDraw = false;
                    }
                    missileDir[i - 8].first.restart();
                    if (e.pos.x < _sprites.front().pos.x + _sprites.front().size.x && e.pos.x + e.size.x > _sprites.front().pos.x && e.pos.y < _sprites.front().pos.y + _sprites.front().size.y && e.size.y + e.pos.y > _sprites.front().pos.y)
                    {
                        e.toDraw = false;
                        lifedecrease();
                    }
                }
                for (auto &z : _sprites)
                {
                    t++;
                    if (t == 7 && z.toDraw)
                    {
                        if (e.pos.x < z.pos.x + z.size.x && e.pos.x + e.size.x > z.pos.x && e.pos.y < z.pos.y + z.size.y && e.size.y + e.pos.y > z.pos.y)
                        {
                            e.toDraw = false;
                            z.toDraw = false;
                            score += 1;
                            break;
                        }
                    }
                }
            }
        }
        if (shipClock.getElapsedTime() > 2000)
        {
            if (spaceShipDir == KEYUP)
            {
                if (_sprites.front().pos.y > 100)
                    _sprites.front().pos.y -= 1;
                else
                {
                    lifedecrease();
                }
            }
            if (spaceShipDir == KEYDOWN)
            {
                if (_sprites.front().pos.y < 1000 - 65)
                {
                    _sprites.front().pos.y += 1;
                }
                else
                {
                    lifedecrease();
                }
            }
            if (spaceShipDir == KEYLEFT)
            {
                if (_sprites.front().pos.x > 500)
                    _sprites.front().pos.x -= 1;
                else
                {
                    lifedecrease();
                }
            }
            if (spaceShipDir == KEYRIGHT)
            {
                if (_sprites.front().pos.x < 1400 - 65)
                    _sprites.front().pos.x += 1;
                else
                {
                    lifedecrease();
                }
            }
            shipClock.restart();
        }
        _rectangles.front().toDraw = true;
    }
    if (state == 1)
    {
    }
}

int Arcade::Solarfox::check(const std::vector<Arcade::key> keys)
{
    int i = 0;

    for (const auto &e : keys)
    {
        if (e >= KEY1 && e <= KEY6)
            return (e - KEY0);
        if (e == ESCAPE)
            return (-12);
    }
    if (keys.empty())
        return (0);
    if (state == 0)
    {
        if (keys.front() == KEYDOWN && keys.front() != spaceShipOldDir && keys.front() != spaceShipDir)
        {
            spaceShipOldDir = KEYUP;
            spaceShipDir = KEYDOWN;
            _sprites.front().path = "Resources/Image/solarfox/spaceshipdown.png";
        }
        if (keys.front() == KEYUP && keys.front() != spaceShipOldDir && keys.front() != spaceShipDir)
        {
            spaceShipOldDir = KEYDOWN;
            spaceShipDir = KEYUP;
            _sprites.front().path = "Resources/Image/solarfox/spaceship.png";
        }
        if (keys.front() == KEYLEFT && keys.front() != spaceShipOldDir && keys.front() != spaceShipDir)
        {
            spaceShipOldDir = KEYRIGHT;
            spaceShipDir = KEYLEFT;
            _sprites.front().path = "Resources/Image/solarfox/spaceshipleft.png";
        }
        if (keys.front() == KEYRIGHT && keys.front() != spaceShipOldDir && keys.front() != spaceShipDir)
        {
            spaceShipOldDir = KEYLEFT;
            spaceShipDir = KEYRIGHT;
            _sprites.front().path = "Resources/Image/solarfox/spaceshipright.png";
        }
        if (keys.front() == SPACE)
        {
            for (auto &e : _sprites)
            {
                i++;
                if (i == 7 && !e.toDraw)
                {
                    oldMissilePos.first = _sprites.front().pos.x;
                    oldMissilePos.second = _sprites.front().pos.y;
                    e.pos.x = _sprites.front().pos.x;
                    e.pos.y = _sprites.front().pos.y;
                    shootDir = spaceShipDir;
                    e.toDraw = true;
                    if (spaceShipDir == KEYUP)
                    {
                        e.path = "Resources/Image/solarfox/missilealli.png";
                        e.size.x = 26;
                        e.size.x = 48;
                    }
                    else if (spaceShipDir == KEYDOWN)
                    {
                        e.path = "Resources/Image/solarfox/missileallidown.png";
                        e.size.x = 26;
                        e.size.x = 48;
                    }
                    else if (spaceShipDir == KEYRIGHT)
                    {
                        e.path = "Resources/Image/solarfox/missileallileft.png";
                        e.size.x = 48;
                        e.size.x = 26;
                    }
                    else if (spaceShipDir == KEYLEFT)
                    {
                        e.path = "Resources/Image/solarfox/missilealliright.png";
                        e.size.x = 48;
                        e.size.x = 26;
                    }

                    break;
                }
            }
        }
    }

    if (keys.front() == R && state == 1)
    {
        restart();
    }

    return (0);
}

const std::vector<Arcade::graphical_rectangle_t> Arcade::Solarfox::getRectangles()
{
    return (_rectangles);
}

const std::vector<Arcade::graphical_text_t> Arcade::Solarfox::getTexts()
{
    std::vector<Arcade::graphical_text_t> ret;

    for (const auto &e : _textes)
        ret.push_back(e.second);
    return (ret);
}

const std::vector<Arcade::graphical_box_t> Arcade::Solarfox::getBoxes()
{
    return (_boxes);
}

const std::vector<Arcade::graphical_sprite_t> Arcade::Solarfox::getSprites()
{
    return (_sprites);
}

const std::vector<Arcade::graphical_rectangle_t> Arcade::Solarfox::getSpecials()
{
    return (std::vector<graphical_rectangle_t>());
}

const std::vector<Arcade::graphical_sprite_t> Arcade::Solarfox::getSpecialSprite()
{
    return (std::vector<graphical_sprite_t>());
}

void Arcade::Solarfox::setName(const std::string &name)
{
    _name = name;
}

extern "C" std::shared_ptr<Arcade::IGameModule> entrypoint(void)
{
    return (std::make_shared<Arcade::Solarfox>());
}

void Arcade::Solarfox::lifedecrease()
{
    life -= 1;
    int i = 0;
    for (auto &e : _sprites)
    {
        if (i > 6 && e.toDraw == true)
            e.toDraw = false;
        i++;
    }
    _sprites.front().pos.y = 550;
    _sprites.front().pos.x = 950;
}

void Arcade::Solarfox::reloadSquare()
{
    int i = 0;

    for (auto &e : _rectangles)
    {
        e.toDraw = true;
        if (i != 0)
        {
            e.pos.x = (rand() % 700) + 600;
            e.pos.y = (rand() % 700) + 200;
        }
        if (i < 15)
        {
            e.size.x -= lvl * 0.5;
            e.size.y -= lvl * 0.5;
        }
        else
        {
            e.size.x += lvl * 0.5;
            e.size.y += lvl * 0.5;
        }
        i++;
    }
    nbrect = 15;
    lvl++;
}

const std::vector<std::string> Arcade::Solarfox::getSounds()
{
    return (std::vector<std::string>());
}

void Arcade::Solarfox::setVitesse(const float &speed)
{
    (void)speed;
}

float Arcade::Solarfox::getVitesse() const
{
    return (0.0);
}

void Arcade::Solarfox::restart()
{
    Arcade::Clock clock0;
    Arcade::Clock clock1;
    Arcade::Clock clock2;
    Arcade::Clock clock3;
    Arcade::Clock clock4;
    Arcade::Clock clock5;
    Arcade::Clock clock6;
    Arcade::Clock clock7;

    enemisClock[0] = clock0;
    enemisClock[1] = clock1;
    enemisClock[2] = clock2;
    enemisClock[3] = clock3;
    enemisMissileClock[0] = clock4;
    enemisMissileClock[1] = clock5;
    enemisMissileClock[2] = clock6;
    enemisMissileClock[3] = clock7;

    oldMissilePos.second = 0;
    oldMissilePos.first = 0;

    nbMissile = 0;
    life = 3;
    score = 0;
    nbrect = 15;
    lvl = 0;
    state = 0;
    _textes.clear();
    _rectangles.clear();
    _sprites.clear();
    spaceShipOldDir = KEYDOWN;
    spaceShipDir = KEYUP;
    _textes.clear();
    startGame();
}