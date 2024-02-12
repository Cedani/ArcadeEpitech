/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Nibbler
*/

#include "../../../include/Game/Nibbler.hpp"

Arcade::Nibbler::Nibbler(): idxY(0)
{
}

Arcade::Nibbler::~Nibbler()
{
}

void Arcade::Nibbler::startGame()
{
    std::ifstream mapNibbler("Resources/Image/mapnibler.txt");

    std::string tmp;
    while (getline(mapNibbler, tmp))
        _myMap.push_back(tmp);
}

void Arcade::Nibbler::updateGame()
{
    _map.clear();
    _snake.clear();
    for (const auto &e: _myMap)
        createMap(e);
    for (auto beg = _snake.begin(); beg != _snake.cend(); ++beg) {
        if (beg == _snake.begin())
            beg->color = graphical_color_t(255, 255, 0);
        else if (beg + 1 != _snake.cend())
            beg->color = graphical_color_t(255, 0, 0);
        else
            beg->color = graphical_color_t(0, 0, 255);
        beg->toDraw = true;
    }
    idxY = 0;
}

int Arcade::Nibbler::check(const std::vector<Arcade::key>key)
{
    if (key.empty())
        return (0);
    for (const auto &e: key) {
        if (e >= KEY1 && e <= KEY6)
            return (e - KEY0);
        if (e == ESCAPE)
            return (-12);
    }
    if (key[0] == KEYUP || key[0] == KEYDOWN || key[0] == KEYRIGHT || key[0] == KEYLEFT) {
        direction = key[0];
        // toCheckSnakeMovement();
        moveSnake();
    }
    return (0);
}

void Arcade::Nibbler::createMap(const std::string &line)
{
    std::size_t nb = 0;

    for (const auto &e: line) {
        if (e == '*')
            _map.push_back(graphical_rectangle_t(graphical_vector_t(startX + nb * 30, startY + idxY * 30), graphical_vector_t(30,30), true, graphical_color_t(), true));
        if (e == 'X') {
            _snake.push_back(graphical_rectangle_t(graphical_vector_t(startX + nb * 30, startY + idxY * 30), graphical_vector_t(30, 30), true, graphical_color_t(), false));
            (_snakePos.empty()) ? _snakePos.push_back(graphical_vector_t(nb, idxY)) : void(0);
        }
        nb += 1;
    }
    ++idxY;
}

bool Arcade::Nibbler::toCheckSnakeMovement()
{
    _clock.restart();
    if (direction == KEYUP)
        moveSnake(0, -30);
    if (direction == KEYDOWN)
        moveSnake(0, 30);
    if (direction == KEYLEFT)
        moveSnake( -30, 0);
    if (direction == KEYRIGHT)
        moveSnake( 30, 0);
    return (true);
}

void Arcade::Nibbler::change(float &nb)
{
    if (nb == 0)
        return;
    if (nb < 0)
        ++nb;
    else if (nb > 0)
        --nb;
}

void Arcade::Nibbler::change(float &pos, float &newP)
{
    if (pos == pos + newP)
        return;
    else if (pos < pos + newP)
        ++pos;
    else if (pos > pos + newP)
        --pos;
}

void Arcade::Nibbler::moveSnake(float newX, float newY)
{
    while (newX != 0 || newY != 0) {
        if (_clock.getElapsedTime() > 100) {
            change(_snake[0].pos.x, newX);
            change(_snake[0].pos.y, newY);
            change(newX);
            change(newY);
            _clock.restart();
        }
    }
}

void Arcade::Nibbler::moveSnake()
{
    if (direction == KEYUP) {
        _myMap[_snakePos[0].y][_snakePos[0].x] = ' ';
        _myMap[_snakePos[0].y - 1][_snakePos[0].x] = 'X';
        _snakePos[0].y -= 1;
    }
    if (direction == KEYDOWN) {
        _myMap[_snakePos[0].y][_snakePos[0].x] = ' ';
        _myMap[_snakePos[0].y + 1][_snakePos[0].x] = 'X';
        _snakePos[0].y += 1;
    }
    if (direction == KEYLEFT) {
        _myMap[_snakePos[0].y][_snakePos[0].x] = ' ';
        _myMap[_snakePos[0].y][_snakePos[0].x - 1] = 'X';
        _snakePos[0].x -= 1;
    }
    if (direction == KEYRIGHT) {
        _myMap[_snakePos[0].y][_snakePos[0].x] = ' ';
        _myMap[_snakePos[0].y][_snakePos[0].x + 1] = 'X';
        _snakePos[0].x += 1;
    }
}

const std::vector<Arcade::graphical_rectangle_t> Arcade::Nibbler::getRectangles()
{
    std::vector <graphical_rectangle_t> _ret(_map);

    _ret.insert(_ret.end(), _emptySpace.begin(), _emptySpace.end());    
    _ret.insert(_ret.end(), _snake.begin(), _snake.end());    
    return (_ret);
}

const std::vector<Arcade::graphical_text_t> Arcade::Nibbler::getTexts()
{
    return (std::vector<graphical_text_t>());
}

const std::vector<Arcade::graphical_sprite_t> Arcade::Nibbler::getSprites()
{
    return (std::vector<graphical_sprite_t>());
}

const std::vector<Arcade::graphical_box_t> Arcade::Nibbler::getBoxes()
{
    return (std::vector<graphical_box_t>());
}

const std::vector<Arcade::graphical_rectangle_t> Arcade::Nibbler::getSpecials()
{
    return (std::vector<graphical_rectangle_t>());
}

const std::vector<Arcade::graphical_sprite_t> Arcade::Nibbler::getSpecialSprite()
{
    return (std::vector<graphical_sprite_t>());
}

void Arcade::Nibbler::setName(const std::string &name)
{
    _name = name;
}

const std::vector<std::string> Arcade::Nibbler::getSounds()
{
    return (std::vector<std::string>());
}

void Arcade::Nibbler::setVitesse(const float &speed)
{
    (void)speed;
}

float Arcade::Nibbler::getVitesse() const
{
    return (0.0);
}


extern "C" std::shared_ptr<Arcade::IGameModule> entrypoint(void)
{
    return (std::make_shared<Arcade::Nibbler>());
}