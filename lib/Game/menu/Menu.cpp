/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Menu
*/

#include "../../../include/Game/Menu.hpp"

Arcade::Menu::Menu(): _scene(-1), _cursor("SFML", graphical_rectangle_t(graphical_vector_t(), graphical_vector_t(200, 50), true, graphical_color_t(255, 0, 0))), _changed(false)
{
}

Arcade::Menu::~Menu()
{
}


void Arcade::Menu::startGame()
{
    if (_scene == 4)
        return;
    _sprites.push_back(graphical_sprite_t("Resources/Image/coin.png", graphical_vector_t(944, 524), graphical_vector_t(216,216), graphical_vector_t(1,1), 1.0F, true));
    _clockes["coin"] = Clock();
    _textes["coin"] = graphical_text_t("ENTER A COIN", graphical_vector_t(900, 750), 30, graphical_color_t(), true);
    _snake.push_back(graphical_rectangle_t(graphical_vector_t(-30, 530), graphical_vector_t(30, 20), true, graphical_color_t(0, 0, 255), false));
    _snake.push_back(graphical_rectangle_t(graphical_vector_t(-60, 530), graphical_vector_t(30, 20), true, graphical_color_t(255, 255, 0), false));
    _snake.push_back(graphical_rectangle_t(graphical_vector_t(-90, 530), graphical_vector_t(30, 20), true, graphical_color_t(255, 255, 0), false));
    _snake.push_back(graphical_rectangle_t(graphical_vector_t(-120, 530), graphical_vector_t(30, 20), true, graphical_color_t(255, 0, 0), false));
    _boxes.push_back(graphical_box_t(graphical_vector_t(700, 440), graphical_vector_t(400, 100), "", false));
    _sprites.push_back(graphical_sprite_t("Resources/Image/pacman_closed.png", graphical_vector_t(1910, 525), graphical_vector_t(30, 31), graphical_vector_t(-1,1)));
    _sprites.push_back(graphical_sprite_t("Resources/Image/pacman_open.png", graphical_vector_t(1910, 525), graphical_vector_t(30, 35), graphical_vector_t(-1,1)));
}

void Arcade::Menu::updateGame()
{
    if (_scene == -1)
        setCoin();
    if (_scene == 1) {
        for (auto &e: _snake)
            e.toDraw = true;
        for (auto &e: _sprites)
            e.toDraw = true;
        sceneAfter();
    } if (_scene == 2)
        secondAnimation();
    if (_scene == 3)
        sceneFintro();
    if (_scene == 4) {
        sceneFinal();
        if (!_finish)
            (_shown) ? showLateralMenu() : hideLateralMenu();
        drawTextLeaderBoard();
    }
}

void Arcade::Menu::setCoin()
{
    if (_clockes["coin"].getElapsedTime() > 100000) {
        _textes["coin"].toDraw = !_textes["coin"].toDraw;
        _clockes["coin"].restart();
    }
}

bool Arcade::Menu::hasCollision(graphical_rectangle_t &rect, graphical_sprite_t &spr)
{
    return (!(rect.pos.x > spr.pos.x + spr.size.x || spr.pos.x > rect.pos.x + rect.size.x || rect.pos.y > spr.pos.y + spr.size.y || spr.pos.y > rect.pos.y + rect.size.y));
}

bool Arcade::Menu::hasCollision(graphical_sprite_t &rect, graphical_sprite_t &spr)
{
    return (!(rect.pos.x > spr.pos.x + spr.size.x || spr.pos.x > rect.pos.x + rect.size.x || rect.pos.y > spr.pos.y + spr.size.y || spr.pos.y > rect.pos.y + rect.size.y));
}

bool Arcade::Menu::hasCollision(graphical_sprite_t& rect, graphical_rectangle_t &spr)
{
    return (!(rect.pos.x > spr.pos.x || rect.pos.y > spr.pos.y || rect.pos.x + rect.size.x < spr.pos.x || rect.pos.y + rect.size.y < rect.pos.y));
}

void Arcade::Menu::firstAnimation(void)
{
    graphical_sprite_t spr = _sprites[0];


    spr.pos.x -=  spr.size.x * 3;
    if (_snake.empty()) {
        _sprites[1].toDraw = false;
        return;
    }
    if (hasCollision(spr, _snake[0])) {
        _sprites[0].toDraw = false;
        _sprites[1].toDraw = true;
    } else {
        _sprites[0].toDraw = true;
        _sprites[1].toDraw = false;
    }
}

void Arcade::Menu::checkSnake(void)
{
    graphical_sprite_t spr = _sprites[0];

    spr.pos.x -= spr.size.x * 2;
    if (!_snake.empty() && hasCollision(spr, _snake[0])) {
        _snake.erase(_snake.begin());
        _sprites[0].scale.x -= 0.5;
        _sprites[1].scale.x -= 0.5;
        _sprites[0].scale.y += 0.5;
        _sprites[1].scale.y += 0.5;
        _sprites[0].pos.y -= 10;
        _sprites[1].pos.y -= 10;
    }
    if (!_snake.empty())
        _snake[0].color = graphical_color_t(0, 0, 255);
}

void Arcade::Menu::sceneAfter()
{
    // if (_scene == -1)
    //     eventCoin();
    if (_snake.empty()) {
        _scene = 2;
        _clockes["snake"].restart();
        _sprites.pop_back();
        soundMario = true;
        _sounds.push_back("Resources/Sound/mario.wav");
        return;
    }
    firstAnimation();
    if (_clockes["snake"].getElapsedTime() > 4000) {
        for (auto &e: _snake)
            e.pos.x += 1;
        for (auto &e: _sprites)
            e.pos.x -= 1;
        _clockes["snake"].restart();
    }
    checkSnake();
}

void Arcade::Menu::eventCoin()
{
    _scene = 0;
    _boxes[0].toDraw = true;
    _clockes.erase("coin");
    _sprites.erase(_sprites.begin());
    _textes.erase("coin");
    _sounds.push_back("Resources/Sound/coin.wav");
}

void Arcade::Menu::secondAnimation()
{
    if (soundMario == true)
        return;
    if (_sprites[0].scale.x == 0 && _sprites[0].scale.y == 0) {
        _clockes.clear();
        _scene = 3;
        _sprites.clear();
        initFintro();
        return;
    }
    if (_clockes["snake"].getElapsedTime() > 100000) {
        // if (_sprites[0].scale.x > 0)
        //     _sprites[0].scale.x -= 0.5;
        // else if (_sprites[0].scale.x < 0)
            _sprites[0].scale.x += 0.5;

        // if (_sprites[0].scale.y > 0)
            _sprites[0].scale.y -= 0.5;
        // else if (_sprites[0].scale.y < 0)
        //     _sprites[0].scale.y += 0.5;
        _sprites[0].pos.y += 10;
        _clockes["snake"].restart();
    }
    // std::cout << _sprites[0].scale.x << " " <<_sprites[0].scale.y << std::endl;
}

int Arcade::Menu::check(const std::vector<Arcade::key> keys)
{
    if (_nbQuitMenu != -1) {
        // std::cout << _nbQuitMenu << std::endl;
        return (_nbQuitMenu);
    }
    if (_scene == 0 && soundCoin == true) {
        _sounds.clear();
        soundCoin = false;
    } if (_scene == 2 && soundMario == true) {
        _sounds.clear();
        soundMario = false;
    }
    if (keys.empty())
        return (0);
    for (const auto &e: keys) {
        if (e >= KEY1 && e <= KEY6)
            return (e - KEY0);
        if (e == ESCAPE)
            return (-12);
    }
    if (_scene == -1) {
        eventCoin();
        return (0);
    }
    if (_scene == 0 && !keys.empty()) {
        sceneMenu(keys[0]);
    }
    if (_scene == 4)
        moveCursor(keys);
    return (0);
}

const std::vector<Arcade::graphical_rectangle_t> Arcade::Menu::getRectangles()
{
    std::vector <graphical_rectangle_t> _vec;

    for (const auto &e: _rectangles)
        _vec.push_back(e.second);
    for (const auto &e: _snake)
        _vec.push_back(e);
    return (_vec);
}

const std::vector<Arcade::graphical_text_t> Arcade::Menu::getTexts()
{
    std::vector<Arcade::graphical_text_t> ret;


    for (const auto &e: _textes)
        ret.push_back(e.second);
    for (const auto &e: _leader)
        ret.push_back(e);
    return (ret);
}

const std::vector<std::string> Arcade::Menu::getSounds()
{
    return (_sounds);
}

void Arcade::Menu::sceneMenu(Arcade::key keys)
{
    if (keys == ENTER)
        if (!_boxes[0].input.empty()) {
            _scene = 1;
            _boxes[0].toDraw = false;
            _clockes["snake"] = Clock();
            return;
        }
    if (keys == BACKSPACE) {
        _boxes[0].input.pop_back();
        return;
    }
    if (_boxes[0].input.size() == 9)
        return;
    for (char i = 0; i < 'Z' - 'A'; i += 1)
        if (i == keys)
            _boxes[0].input.push_back(i + 'A');
    if (keys == SPACE)
        _boxes[0].input += ' ';
}

const std::vector<Arcade::graphical_box_t> Arcade::Menu::getBoxes()
{
    return (_boxes);
}

const std::vector<Arcade::graphical_sprite_t> Arcade::Menu::getSprites()
{
    return (_sprites);
}

const std::vector<Arcade::graphical_rectangle_t> Arcade::Menu::getSpecials()
{
    std::vector<graphical_rectangle_t> _ret;

    for (const auto &e: _specialRec)
        _ret.push_back(e.second);
    _ret.push_back(_special);
    return (_ret);
}

void Arcade::Menu::initFintro()
{
    _special = graphical_rectangle_t(graphical_vector_t(0, 0), graphical_vector_t(1920, 1080), false, graphical_color_t(0,0,0), true);
    _sprites.push_back(graphical_sprite_t("Resources/Image/Parallax.png", graphical_vector_t(0, 0), graphical_vector_t(1920, 1080), graphical_vector_t(1,1), 1.0F, true));
    _sprites.push_back(graphical_sprite_t("Resources/Image/Parallax.png", graphical_vector_t(0, 1080), graphical_vector_t(1920, 1080), graphical_vector_t(1,1), 1.0F, true));
    _Specialsprites.push_back(graphical_sprite_t("Resources/Image/cursor_normal.png", graphical_vector_t(935, 515), graphical_vector_t(50, 50), graphical_vector_t(1,1), 1.0F, true));
    _Specialsprites.push_back(graphical_sprite_t("Resources/Image/cursor_clicked.png", graphical_vector_t(935, 515), graphical_vector_t(50, 51), graphical_vector_t(1,1), 1.0F));
    _clockes["special"] = Clock();
    _clockes["background"] = Clock();
    _clockes["clicked"] = Clock();
    drawLateralMenu();
    drawOptions();
    drawLeaderboard();
}

void Arcade::Menu::drawSelection()
{
    _sprites.push_back(graphical_sprite_t("Resources/Image/button.png", graphical_vector_t(500, 495), graphical_vector_t(200, 50), graphical_vector_t(1,1), 1.0F, true));
    _textes.insert(std::pair<std::string, graphical_text_t>("SFML", graphical_text_t("SFML", graphical_vector_t(570, 510), 20, graphical_color_t(230,176,80), true)));
    _sprites.push_back(graphical_sprite_t("Resources/Image/button.png", graphical_vector_t(810, 495), graphical_vector_t(200, 50), graphical_vector_t(1,1), 1.0F, true));
    _textes.insert(std::pair<std::string, graphical_text_t>("SDL2", graphical_text_t("SDL2", graphical_vector_t(880, 510), 20, graphical_color_t(230,176,80), true)));
    _sprites.push_back(graphical_sprite_t("Resources/Image/button.png", graphical_vector_t(1120, 495), graphical_vector_t(200, 50), graphical_vector_t(1,1), 1.0F, true));
    _textes.insert(std::pair<std::string, graphical_text_t>("NCURSES", graphical_text_t("NCURSES", graphical_vector_t(1170, 510), 20, graphical_color_t(230,176,80), true)));
    _sprites.push_back(graphical_sprite_t("Resources/Image/button.png", graphical_vector_t(650, 695), graphical_vector_t(200, 50), graphical_vector_t(1,1), 1.0F, true));
    _textes.insert(std::pair<std::string, graphical_text_t>("PACMAN", graphical_text_t("PACMAN", graphical_vector_t(700, 710), 20, graphical_color_t(230,176,80), true)));
    _sprites.push_back(graphical_sprite_t("Resources/Image/button.png", graphical_vector_t(970, 695), graphical_vector_t(200, 50), graphical_vector_t(1,1), 1.0F, true));
    _textes.insert(std::pair<std::string, graphical_text_t>("SOLARFOX", graphical_text_t("SOLARFOX", graphical_vector_t(1020, 710), 20, graphical_color_t(230,176,80), true)));
    _sprites.push_back(graphical_sprite_t("Resources/Image/button.png", graphical_vector_t(810, 895), graphical_vector_t(200, 50), graphical_vector_t(1,1), 1.0F, true));
    _textes.insert(std::pair<std::string, graphical_text_t>("LAUNCH", graphical_text_t("LAUNCH", graphical_vector_t(860, 905), 20, graphical_color_t(230,176,80), true)));
}

void Arcade::Menu::eventSelection()
{
    for (std::size_t i = 2; i <= 4; i += 1)
        if (hasCollision(_Specialsprites[0], _sprites[i])) {
            resetLib();
            _sprites[i].scale.x = 1.2;
            _sprites[i].scale.y = 1.2;
        }
    for (std::size_t i = 5; i <= 6; i += 1)
        if (hasCollision(_Specialsprites[0], _sprites[i])) {
            resetGame();
            _sprites[i].scale.x = 1.2;
            _sprites[i].scale.y = 1.2;
        }
    if (hasCollision(_Specialsprites[0], _sprites[7]))
        quitMenu();
}

void Arcade::Menu::resetLib()
{
    _sprites[2].scale.x = 1.0;   
    _sprites[2].scale.y = 1.0;
    _sprites[3].scale.x = 1.0; 
    _sprites[3].scale.y = 1.0;
    _sprites[4].scale.x = 1.0;   
    _sprites[4].scale.y = 1.0;
}

void Arcade::Menu::resetGame()
{
    _sprites[5].scale.x = 1.0;
    _sprites[5].scale.y = 1.0;
    _sprites[6].scale.x = 1.0;   
    _sprites[6].scale.y = 1.0;
}

void Arcade::Menu::quitMenu()
{
    if (_sprites[2].scale.x == 1.0 && _sprites[3].scale.x == 1.0 && _sprites[4].scale.x == 1.0)
        return;
    if (_sprites[5].scale.x == 1.0 && _sprites[6].scale.x == 1.0)
        return;
    selectLib();
    selectGame();
    _nbQuitMenu = _nbLib + _nbGame;
}

void Arcade::Menu::selectLib()
{
    if (_sprites[2].scale.x > 1.0)
        _nbLib = 10;
    if (_sprites[3].scale.x > 1.0)
        _nbLib = 20;
    if (_sprites[4].scale.x > 1.0)
        _nbLib = 30;
}

void Arcade::Menu::selectGame()
{
    if (_sprites[5].scale.x > 1.0)
        _nbGame = 1;
    if (_sprites[6].scale.x > 1.0)
        _nbGame = 2;
}

void Arcade::Menu::sceneFinal()
{
    stopClicked();
    moveParallax();
}

void Arcade::Menu::sceneFintro()
{
    if (_special.pos.y == 1080) {
        _scene = 4;
        _special.toDraw = false;
        drawSelection();
        return;
    }
    moveBackgroud();
    moveParallax();
}

void Arcade::Menu::moveParallax()
{
    if (_clockes["background"].getElapsedTime() > 5000) {
        _sprites[0].pos.y -= 1;
        _sprites[1].pos.y -= 1;
        if (_sprites[0].pos.y == -1080)
            _sprites[0].pos.y = 1080;
        if (_sprites[1].pos.y == -1080)
            _sprites[1].pos.y = 1080;
        _clockes["background"].restart();
    }
}

void Arcade::Menu::moveBackgroud()
{
    if (_clockes["special"].getElapsedTime() > 1000) {
        _special.pos.y += 1;
        _clockes["special"].restart();
    }
}

void Arcade::Menu::eventClicked()
{
    _clockes["clicked"] = Clock();
    _Specialsprites[0].toDraw = false;
    _Specialsprites[1].toDraw = true;
    if (_clockes["clicked"].getElapsedTime() > 4000) {
        _Specialsprites[1].toDraw = false;
        _Specialsprites[0].toDraw = true;
        _clockes["clicked"].restart();
    }
}

void Arcade::Menu::stopClicked()
{
    if (!_Specialsprites[1].toDraw)
        return;
    if (_clockes["clicked"].getElapsedTime() > 200000) {
        _Specialsprites[1].toDraw = false;
        _Specialsprites[0].toDraw = true;
        _clockes["clicked"].restart();
    }
}

void Arcade::Menu::checkPos(graphical_sprite_t &spr)
{
    if (spr.pos.x < 0)
        spr.pos.x = 0;
    if (spr.pos.x > 1920 - spr.size.x)
        spr.pos.x = 1920 - spr.size.x;
    if (spr.pos.y < 0)
        spr.pos.y = 0;
    if (spr.pos.y > 1080 - spr.size.y)
        spr.pos.y = 1080 - spr.size.y;
}

void Arcade::Menu::drawLateralMenu()
{
    _specialRec["small0"] = graphical_rectangle_t(graphical_vector_t(0, 99), graphical_vector_t(51, 52), false, graphical_color_t(0, 0, 255), true);
    _specialRec["small1"] = graphical_rectangle_t(graphical_vector_t(0, 100), graphical_vector_t(50, 50), true, graphical_color_t(), true);
    _Specialsprites.push_back(graphical_sprite_t("Resources/Image/left.png", graphical_vector_t(10, 110), graphical_vector_t(30,30), graphical_vector_t(1, 1), 1.0F));
    _Specialsprites.push_back(graphical_sprite_t("Resources/Image/right.png", graphical_vector_t(10, 110), graphical_vector_t(30,30), graphical_vector_t(1, 1), 1.0F, true));
    // _sprites.push_back(graphical_sprite_t("Resources/Image/right.png"));
}

void Arcade::Menu::moveCursor(const std::vector<key> &keys)
{
    for (const auto &key : keys) {
        if (key == KEYUP) {
            _Specialsprites[0].pos.y -= 20;
            _Specialsprites[1].pos.y -= 20;
        } if (key == KEYDOWN) {
            _Specialsprites[0].pos.y += 20;
            _Specialsprites[1].pos.y += 20;
        } if (key == KEYLEFT) {
            _Specialsprites[0].pos.x -= 20;
            _Specialsprites[1].pos.x -= 20;
        } if (key == KEYRIGHT) {
            _Specialsprites[0].pos.x += 20;
            _Specialsprites[1].pos.x += 20;
        } if (key == ENTER) {
            eventClicked();
            checkClicked();
            eventSelection();
        }
    }
    checkPos(_Specialsprites[0]);
    checkPos(_Specialsprites[1]);
}

void Arcade::Menu::drawOptions()
{
    _textes.insert(std::pair<std::string, graphical_text_t>("1", graphical_text_t("1-  previous library", graphical_vector_t(20, 140 - 10), 40, graphical_color_t(241, 163, 173))));
    _textes.insert(std::pair<std::string, graphical_text_t>("2", graphical_text_t("2-  next library", graphical_vector_t(20, 185 - 10), 40, graphical_color_t(241, 163, 173))));
    _textes.insert(std::pair<std::string, graphical_text_t>("3", graphical_text_t("3-  previous game", graphical_vector_t(20, 230 - 10), 40, graphical_color_t(241, 163, 173))));
    _textes.insert(std::pair<std::string, graphical_text_t>("4", graphical_text_t("4-  next game", graphical_vector_t(20, 275 - 10), 40, graphical_color_t(241, 163, 173))));
    _textes.insert(std::pair<std::string, graphical_text_t>("5", graphical_text_t("5-  restart the game", graphical_vector_t(20, 320 - 10), 40, graphical_color_t(241, 163, 173))));
    _textes.insert(std::pair<std::string, graphical_text_t>("6", graphical_text_t("6-  go back to the menu", graphical_vector_t(20, 365 - 10), 40, graphical_color_t(241, 163, 173))));
    _textes.insert(std::pair<std::string, graphical_text_t>("7", graphical_text_t("7 && escape -  exit", graphical_vector_t(20, 410 - 10), 40, graphical_color_t(241, 163, 173))));
    _textes.insert(std::pair<std::string, graphical_text_t>("name", graphical_text_t("welcome " + _boxes[0].input, graphical_vector_t(880, 100), 40, graphical_color_t(), true)));
    _specialRec["name"] = graphical_rectangle_t(graphical_vector_t(850, 100), graphical_vector_t(100 + ((8 + _boxes[0].input.size()) * _textes["name"].size / 2), 50), true, graphical_color_t(151, 99, 73), true);
    _specialRec["boxText0"] = graphical_rectangle_t(graphical_vector_t(-500, 99), graphical_vector_t(500, 402), false, graphical_color_t(0, 0, 255), true);
    _specialRec["boxText1"] = graphical_rectangle_t(graphical_vector_t(-500, 100), graphical_vector_t(500, 400), true, graphical_color_t(), true);
}

void Arcade::Menu::checkClicked()
{
    if (hasCollision(_specialRec["small1"], _Specialsprites[0])) {
        _shown = !_shown;
        _clockes["lateralMenu"] = Clock();
        _finish = false;
    }
}

float Arcade::Menu::getVitesse() const
{
    return (0.0);
}

void Arcade::Menu::showLateralMenu()
{
    if (_finish)
        return;
    if (_clockes["lateralMenu"].getElapsedTime() > 1000) {
        _specialRec["boxText1"].pos.x += 1;
        _specialRec["boxText0"].pos.x += 1;
        _specialRec["small1"].pos.x += 1;
        _specialRec["small0"].pos.x += 1;
        _Specialsprites[2].pos.x += 1;
        _Specialsprites[3].pos.x += 1;
        _clockes["lateralMenu"].restart();
    }
    if (_specialRec["small1"].pos.x == 500) {
        for (auto &e: _textes)
            if (e.first != "name")
                e.second.toDraw = true;
        _finish = true;
        _Specialsprites[2].toDraw = true;
        _Specialsprites[3].toDraw = false;
    }
    // exit (84);
}

void Arcade::Menu::drawTextLeaderBoard(void)
{
    selectGame();
    std::string path;
    std::ifstream file;
    int nb = 0;

    _leader.clear();
    _scores.clear();
    if (_nbGame == 0)
        return;
    else if (_nbGame == 2)
        path = "Resources/Leaderords/leaderboardSolarFox.txt";
    else
        path = "Resources/Leaderords/leaderboardPacman.txt";
    file.open(path);
    while (getline(file, path) && nb < 10) {
        _scores.push_back(std::make_pair(path.substr(0, path.find(' ')), path.substr(path.find(' ') + 1)));
        ++nb;
    }
    nb = 1;
    for (auto end = _scores.end() - 1; end >= _scores.cbegin(); --end) {
        _leader.push_back(graphical_text_t(std::to_string(nb) + "- " + end->first + ": " + end->second, graphical_vector_t(1500, 110 + (nb - 1) * 50), 30, graphical_color_t(0,0,0), true));
        if (nb == 1)
            _leader[nb - 1].color = graphical_color_t(255,215,0);
        else if (nb == 2)
            _leader[nb - 1].color = graphical_color_t(211,211,211);
        else if (nb == 3)
            _leader[nb - 1].color = graphical_color_t(205,127,50);
        nb += 1;
    }
}

// void Arcade::Menu::showLeaderboard()
// {
//     if (_finishL)
//         return;
//     if (_clockes["leaderboard"].getElapsedTime() > 1000) {
//         _specialRec["leaderboard1"].pos.x -= 1;
//         _specialRec["leaderboard0"].pos.x -= 1;
//         _specialRec["small1"].pos.x -= 1;
//         _specialRec["small0"].pos.x -= 1;
//         _Specialsprites[4].pos.x += 1;
//         _Specialsprites[5].pos.x += 1;
//         _clockes["lateralMenu"].restart();
//     }
//     if (_specialRec["small1"].pos.x == 1470) {
//         for (auto &e: _textes)
//             if (e.first != "name")
//                 e.second.toDraw = true;
//         _finish = true;
//         _Specialsprites[4].toDraw = true;
//         _Specialsprites[5].toDraw = false;
//     }
//     // exit (84);
// }

void Arcade::Menu::drawLeaderboard()
{
    _specialRec["leaderboard1"] = graphical_rectangle_t(graphical_vector_t(1470, 100), graphical_vector_t(450, 800), true, graphical_color_t(), true);
    _specialRec["leaderboard0"] = graphical_rectangle_t(graphical_vector_t(1469, 99), graphical_vector_t(452, 802), false, graphical_color_t(0,0,255), true);
    // _Specialsprites.push_back(graphical_sprite_t("Resources/Image/Right.png", graphical_vector_t(1190, 110), graphical_vector_t(30,30), graphical_vector_t(1,1), 1.0F, true));
    // _Specialsprites.push_back(graphical_sprite_t("Resources/Image/Right.png", graphical_vector_t(1190, 110), graphical_vector_t(30,30), graphical_vector_t(1,1), 1.0F, false));
}

void Arcade::Menu::hideLateralMenu()
{
    if (_finish)
        return;
    if (_specialRec["small1"].pos.x == 500) {
        for (auto &e: _textes)
            if (e.first != "name")
                e.second.toDraw = false;
    }
    if (_clockes["lateralMenu"].getElapsedTime() > 1000) {
        _specialRec["boxText1"].pos.x -= 1;
        _specialRec["boxText0"].pos.x -= 1;
        _specialRec["small1"].pos.x -= 1;
        _specialRec["small0"].pos.x -= 1;
        _Specialsprites[2].pos.x -= 1;
        _Specialsprites[3].pos.x -= 1;
        _Specialsprites[2].toDraw = false;
        _Specialsprites[3].toDraw = true;
        _clockes["lateralMenu"].restart();
    }
    if (_specialRec["small1"].pos.x == 0) {
        _finish = true;
        _Specialsprites[2].toDraw = false;
        _Specialsprites[3].toDraw = true;
    }
}

void Arcade::Menu::setVitesse(const float &speed)
{
    (void)speed;
}

const std::vector<Arcade::graphical_sprite_t> Arcade::Menu::getSpecialSprite()
{
    return (_Specialsprites);
}

void Arcade::Menu::setName(const std::string &name)
{
    if (!name.empty()) {
        _scene = 4;
        _textes.clear();
        _sprites.clear();
        _rectangles.clear();
        _snake.clear();
        _boxes.push_back(graphical_box_t(graphical_vector_t(700, 440), graphical_vector_t(400, 100), name, false));
        initFintro();
        drawSelection();
        _special.pos.y = 1080;
    }
}

// faut faire cette fonction là dans pacman.cpp

extern "C" std::shared_ptr<Arcade::IGameModule> entrypoint(void)
{
    return (std::make_shared<Arcade::Menu>());
}