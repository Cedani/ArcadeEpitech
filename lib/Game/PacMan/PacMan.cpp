/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** PacMan
*/

#include "../../../include/Game/PacMan.hpp"

Arcade::PacMan::PacMan()
{
    pac_pos = {0, 0, 0};
    pacDir = {0, 0, 0};
    temppacDir = {0, 0, 0};
    tp1 = {0, 0, 0};
    tp2 = {0, 0, 0};
    spawn = {0, 0, 0};
    phDir1 = {0, 0, 0};
    out1 = false;
    dead1 = false;
    vuln1 = false;
    out2 = false;
    dead2 = false;
    vuln2 = false;
    out3 = false;
    dead3 = false;
    vuln3 = false;
    out4 = false;
    dead4 = false;
    vuln4 = false;
    score = 0;
    endLevel = false;
    killPac = false;
}

Arcade::PacMan::~PacMan()
{
}

void Arcade::PacMan::startGame()
{
    if (!_setSpeed)
        _speed = 2.0;
    float i = 0;
    int j = 0;
    Clock cl;
    std::string line;
    std::ifstream mapFile;
    mapFile.open("Resources/map_pacman.txt");
    while(getline(mapFile, line)) {
        for (std::size_t index = 0; index < line.length(); index ++) {
            if (line[index] == '#')
                _rectangles.push_back(graphical_rectangle_t(graphical_vector_t(i, j), graphical_vector_t(9.5 * 2, 19 * 2), true, graphical_color_t(255, 125, 255), true));
            if (line[index] == '.')
                _sprites.push_back(graphical_sprite_t("Resources/Image/point_pacman.png",graphical_vector_t(i + 2 * 2, j + 4 * 2), graphical_vector_t(4 * 2, 4 * 2), graphical_vector_t(1, 1), 1, true));
            if (line[index] == '*')
                _sprites.push_back(graphical_sprite_t("Resources/Image/point_pacman(1).png",graphical_vector_t(i + 2 * 2, j + 4 * 2), graphical_vector_t(8 * 2, 8 * 2), graphical_vector_t(1, 1), 1, true));
            if (line[index] == 'S') {
                pacSprite = graphical_sprite_t("Resources/Image/pacman_closed.png",graphical_vector_t(i, j), graphical_vector_t(19 * 2, 19 * 2), graphical_vector_t(1, 1), 1, true);
                bonusSprite = graphical_sprite_t("Resources/Image/point_pacman(2).png",graphical_vector_t(i + 2 * 2, j + 4 * 2), graphical_vector_t(16 * 2, 16 * 2), graphical_vector_t(1, 1), 1, false);
            }
            if (line[index] == 'A')
                phSprite1 = graphical_sprite_t("Resources/Image/PacMan/phantom.png",graphical_vector_t(i, j), graphical_vector_t(19 * 2, 19 * 2), graphical_vector_t(1, 1), 1, true);
            if (line[index] == 'B')
                phSprite2 = graphical_sprite_t("Resources/Image/PacMan/phantom1.png",graphical_vector_t(i, j), graphical_vector_t(19 * 2, 19 * 2), graphical_vector_t(1, 1), 1, true);
            if (line[index] == 'C')
                phSprite3 = graphical_sprite_t("Resources/Image/PacMan/phantom2.png",graphical_vector_t(i, j), graphical_vector_t(19 * 2, 19 * 2), graphical_vector_t(1, 1), 1, true);
            if (line[index] == 'D')
                phSprite4 = graphical_sprite_t("Resources/Image/PacMan/phantom3.png",graphical_vector_t(i, j), graphical_vector_t(19 * 2, 19 * 2), graphical_vector_t(1, 1), 1, true);
            i += 9.5 * 2;
        }
        j += 19 * 2 ;
        i = 0;
        _map.push_back(line);
    }
    _sprites.push_back(graphical_sprite_t("Resources/Image/PacMan/score.png",graphical_vector_t(1440, 100), graphical_vector_t(300, 100), graphical_vector_t(1, 1), 0,true));
    _textes.push_back(graphical_text_t(std::to_string(score), graphical_vector_t(1500, 300), 150, graphical_color_t(255, 255, 0), true));
    _clockes.insert(std::make_pair("pacman", cl));
    _clockes.insert(std::make_pair("phantom", cl));
    _clockes.insert(std::make_pair("bonus", cl));
    find_pacman();
}

void Arcade::PacMan::bonusSpawn()
{
    if (_clockes["bonus"].getElapsedTime() > 10000000 && _map[pac_pos.y][pac_pos.x] != _map[startPac.y][startPac.x]) {
        bonusSprite.toDraw = true;
    }
}

void Arcade::PacMan::find_pacman()
{
    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map[i].length(); j++) {
            if ( _map[i][j] == 'S') {
                pac_pos.x = j;
                pac_pos.y = i;
                startPac.x = j;
                startPac.y = i;
            }
            if ( _map[i][j] == 'T') {
                tp1.x = j;
                tp1.y = i;
            }
            if ( _map[i][j] == 'U') {
                tp2.x = j;
                tp2.y = i;
            }
            if ( _map[i][j] == 'G') {
                spawn.x = j;
                spawn.y = i;
            }
            if ( _map[i][j] == 'A') {
                phPos1.x = j;
                phPos1.y = i;
                prison.x = j;
                prison.y = i;
            }
            if ( _map[i][j] == 'B') {
                phPos2.x = j;
                phPos2.y = i;
            }
            if ( _map[i][j] == 'C') {
                phPos3.x = j;
                phPos3.y = i;
            }
            if ( _map[i][j] == 'D') {
                phPos4.x = j;
                phPos4.y = i;
            }
        }
    }
}

void Arcade::PacMan::updateGame()
{
    phatomMov();
    if (_clockes["pacman"].getElapsedTime() > 10000) {
        checkNextLvl();
        deadPac();
        pacGum();
        checkDamage();
    }
    if (_clockes["pacman"].getElapsedTime() > 80000) {
        if (dead1 == false)
            collisionMapPhantom1();
        else if (dead1 == true)
            findHome1();
        if (dead2 == false)
            collisionMapPhantom2();
        else
            findHome2();
        if (dead3 == false)
            collisionMapPhantom3();
        else
            findHome3();
        if (dead4 == false)
            collisionMapPhantom4();
        else
            findHome4();
        collisionMap();
        teleportation();
        _clockes["pacman"].restart();
    }
    bonusSpawn();
    if (_clockes["dead_time"].getElapsedTime() > 15000000 && dead1 == true) {
        phSprite1.pos.x = prison.x * 19;
        phSprite1.pos.y = prison.y * 38;
        phPos1.x = prison.x;
        phPos1.y = prison.y;
        phSprite1.path = "Resources/Image/PacMan/phantom.png";
        dead1 = false;
        out1 = false;
        vuln1 = false;
        _clockes["dead_time"].restart();
    }
    if (_clockes["dead_time"].getElapsedTime() > 15000000 && dead2 == true) {
        phSprite2.pos.x = prison.x * 19;
        phSprite2.pos.y = prison.y * 38;
        phPos2.x = prison.x;
        phPos2.y = prison.y;
        phSprite2.path = "Resources/Image/PacMan/phantom1.png";
        dead2 = false;
        out2 = false;
        vuln2 = false;
        _clockes["dead_time"].restart();
    }
    if (_clockes["dead_time"].getElapsedTime() > 15000000 && dead3 == true) {
        phSprite3.pos.x = prison.x * 19;
        phSprite3.pos.y = prison.y * 38;
        phPos3.x = prison.x;
        phPos3.y = prison.y;
        phSprite3.path = "Resources/Image/PacMan/phantom2.png";
        dead3 = false;
        out3 = false;
        vuln3 = false;
        _clockes["dead_time"].restart();
    }
    if (_clockes["dead_time"].getElapsedTime() > 15000000 && dead4 == true) {
        phSprite4.pos.x = prison.x * 19;
        phSprite4.pos.y = prison.y * 38;
        phPos4.x = prison.x;
        phPos4.y = prison.y;
        phSprite4.path = "Resources/Image/PacMan/phantom3.png";
        dead4 = false;
        out4 = false;
        vuln4 = false;
        _clockes["dead_time"].restart();
    }
    if (_clockes["reset_ph"].getElapsedTime() > 10000000 && vuln1 == true) {
        vuln1 = false;
        vuln2 = false;
        vuln3 = false;
        vuln4 = false;
        phSprite1.path = "Resources/Image/PacMan/phantom.png";
        phSprite2.path = "Resources/Image/PacMan/phantom1.png";
        phSprite3.path = "Resources/Image/PacMan/phantom2.png";
        phSprite4.path = "Resources/Image/PacMan/phantom3.png";
        _clockes["reset_ph"].restart();
    }
}

void Arcade::PacMan::findHome1()
{
    if (phPos1.x > prison.x) {
        phPos1.x -= 1;
        phSprite1.pos.x = phPos1.x * 19;
    }
    if (phPos1.x < prison.x) {
        phPos1.x += 1;
        phSprite1.pos.x = phPos1.x * 19;
    }
    if (phPos1.y > prison.y) {
        phPos1.y -= 1;
        phSprite1.pos.y = phPos1.y * 38;
    }
    if (phPos1.y < prison.y) {
        phPos1.y += 1;
        phSprite1.pos.y = phPos1.y * 38;
    }
}

void Arcade::PacMan::findHome2()
{
    if (phPos2.x > prison.x) {
        phPos2.x -= 1;
        phSprite2.pos.x = phPos2.x * 19;
    }
    if (phPos2.x < prison.x) {
        phPos2.x += 1;
        phSprite2.pos.x = phPos2.x * 19;
    }
    if (phPos2.y > prison.y) {
        phPos2.y -= 1;
        phSprite2.pos.y = phPos2.y * 38;
    }
    if (phPos2.y < prison.y) {
        phPos2.y += 1;
        phSprite2.pos.y = phPos2.y * 38;
    }
}

void Arcade::PacMan::findHome3()
{
    if (phPos3.x > prison.x) {
        phPos3.x -= 1;
        phSprite3.pos.x = phPos3.x * 19;
    }
    if (phPos3.x < prison.x) {
        phPos3.x += 1;
        phSprite3.pos.x = phPos3.x * 19;
    }
    if (phPos3.y > prison.y) {
        phPos3.y -= 1;
        phSprite3.pos.y = phPos3.y * 38;
    }
    if (phPos3.y < prison.y) {
        phPos3.y += 1;
        phSprite3.pos.y = phPos3.y * 38;
    }
}

void Arcade::PacMan::findHome4()
{
    if (phPos4.x > prison.x) {
        phPos4.x -= 1;
        phSprite4.pos.x = phPos4.x * 19;
    }
    if (phPos4.x < prison.x) {
        phPos4.x += 1;
        phSprite4.pos.x = phPos4.x * 19;
    }
    if (phPos4.y > prison.y) {
        phPos4.y -= 1;
        phSprite4.pos.y = phPos4.y * 38;
    }
    if (phPos4.y < prison.y) {
        phPos4.y += 1;
        phSprite4.pos.y = phPos4.y * 38;
    }
}

void Arcade::PacMan::phatomMov()
{
    if (_clockes["phantom"].getElapsedTime() > 10000000 && out1 == false) {
        phSprite1.pos.x = spawn.x * 19;
        phSprite1.pos.y = spawn.y * 38;
        phPos1.x = spawn.x;
        phPos1.y = spawn.y;
        out1 = true;
        _clockes["phatom"].restart();
    }
    if (_clockes["phantom"].getElapsedTime() > 12500000 && out2 == false) {
        phSprite2.pos.x = spawn.x * 19;
        phSprite2.pos.y = spawn.y * 38;
        phPos2.x = spawn.x;
        phPos2.y = spawn.y;
        out2 = true;
    }
    if (_clockes["phantom"].getElapsedTime() > 17500000 && out3 == false) {
        phSprite3.pos.x = spawn.x * 19;
        phSprite3.pos.y = spawn.y * 38;
        phPos3.x = spawn.x;
        phPos3.y = spawn.y;
        out3 = true;
    }
    if (_clockes["phantom"].getElapsedTime() > 22500000 && out4 == false) {
        phSprite4.pos.x = spawn.x * 19;
        phSprite4.pos.y = spawn.y * 38;
        phPos4.x = spawn.x;
        phPos4.y = spawn.y;
        out4 = true;
    }
}

void Arcade::PacMan::rotatePac()
{
    if (pacDir.x == 1) {
        if (strcmp(pacSprite.path.c_str(), "Resources/Image/pacman_closed.png") == 0)
            pacSprite.path = "Resources/Image/pacman_open.png";
        else
            pacSprite.path = "Resources/Image/pacman_closed.png";
    }
    if (pacDir.x == -1) {
        if (strcmp(pacSprite.path.c_str(), "Resources/Image/pacman_closedG.png") == 0)
            pacSprite.path = "Resources/Image/pacman_openG.png";
        else
            pacSprite.path = "Resources/Image/pacman_closedG.png";
    }
    if (pacDir.y == 1) {
        if (strcmp(pacSprite.path.c_str(), "Resources/Image/pacman_closedD.png") == 0)
            pacSprite.path = "Resources/Image/pacman_openD.png";
        else
            pacSprite.path = "Resources/Image/pacman_closedD.png";
    }
    if (pacDir.y == -1) {
        if (strcmp(pacSprite.path.c_str(), "Resources/Image/pacman_closedU.png") == 0)
            pacSprite.path = "Resources/Image/pacman_openU.png";
        else
            pacSprite.path = "Resources/Image/pacman_closedU.png";
    }
}

void Arcade::PacMan::collisionMapPhantom1()
{
    int i = 0;
    std::vector<graphical_vector_t> temp;

    if (_map[phPos1.y + 1][phPos1.x] != '#' && _map[phPos1.y + 1][phPos1.x] != 'x') {
        temp.push_back(graphical_vector_t(0, 1));
    }
    if (_map[phPos1.y - 1][phPos1.x] != '#' && _map[phPos1.y - 1][phPos1.x] != 'x') {
        temp.push_back(graphical_vector_t(0, -1));
    }
    if (_map[phPos1.y][phPos1.x + 1] != '#' && _map[phPos1.y][phPos1.x + 1] != 'x') {
        temp.push_back(graphical_vector_t(1, 0));
    }
    if (_map[phPos1.y][phPos1.x - 1] != '#' && _map[phPos1.y][phPos1.x - 1] != 'x') {
        temp.push_back(graphical_vector_t(-1, 0));
    }
    if (temp.size() == 0)
        return;
    i = rand() % temp.size();
    if (phDir1.x == 0 && phDir1.y == 0) {
        phDir1.x = temp[i].x;
        phDir1.y = temp[i].y;
    }
    if (phDir1.x == -temp[i].x && phDir1.y == -temp[i].y) {
        phDir1.x = -temp[i].x;
        phDir1.y = -temp[i].y;
    } else {
        phDir1.x = temp[i].x;
        phDir1.y = temp[i].y;
    }
    if ((_map[phPos1.y + phDir1.y][phPos1.x + phDir1.x] == '#' ||  _map[phPos1.y + phDir1.y][phPos1.x + phDir1.x] == 'x') && temp.size() >= 2) {
        if (temp.size() == 2) {
            if (i == 0) {
                phDir1.x = temp[1].x;
                phDir1.y = temp[1].y;
            } else if (i == 1) {
                phDir1.x = temp[0].x;
                phDir1.y = temp[0].y;
            }
        } else if (temp.size() == 3) {
            if (i == 0) {
                phDir1.x = temp[1].x;
                phDir1.y = temp[1].y;
            } else if (i == 1) {
                phDir1.x = temp[2].x;
                phDir1.y = temp[2].y;
            } else if (i == 2) {
                phDir1.x = temp[1].x;
                phDir1.y = temp[1].y;
            }
        }
    }
    phPos1.x += phDir1.x;
    phPos1.y += phDir1.y;
    phSprite1.pos.x += phDir1.x * (9.5 * _speed);
    phSprite1.pos.y += phDir1.y * (19 * _speed);
    return;
}

void Arcade::PacMan::collisionMapPhantom2()
{
    int i = 0;
    std::vector<graphical_vector_t> temp;

    if (_map[phPos2.y + 1][phPos2.x] != '#' && _map[phPos2.y + 1][phPos2.x] != 'x') {
        temp.push_back(graphical_vector_t(0, 1));
    }
    if (_map[phPos2.y - 1][phPos2.x] != '#' && _map[phPos2.y - 1][phPos2.x] != 'x') {
        temp.push_back(graphical_vector_t(0, -1));
    }
    if (_map[phPos2.y][phPos2.x + 1] != '#' && _map[phPos2.y][phPos2.x + 1] != 'x') {
        temp.push_back(graphical_vector_t(1, 0));
    }
    if (_map[phPos2.y][phPos2.x - 1] != '#' && _map[phPos2.y][phPos2.x - 1] != 'x') {
        temp.push_back(graphical_vector_t(-1, 0));
    }
    if (temp.size() == 0)
        return;
    i = rand() % temp.size();
    if (phDir2.x == 0 && phDir2.y == 0) {
        phDir2.x = temp[i].x;
        phDir2.y = temp[i].y;
    }
    if (phDir2.x == -temp[i].x && phDir2.y == -temp[i].y) {
        phDir2.x = -temp[i].x;
        phDir2.y = -temp[i].y;
    } else {
        phDir2.x = temp[i].x;
        phDir2.y = temp[i].y;
    }
    if ((_map[phPos2.y + phDir2.y][phPos2.x + phDir2.x] == '#' ||  _map[phPos2.y + phDir2.y][phPos2.x + phDir2.x] == 'x') && temp.size() >= 2) {
        if (temp.size() == 2) {
            if (i == 0) {
                phDir2.x = temp[1].x;
                phDir2.y = temp[1].y;
            } else if (i == 1) {
                phDir2.x = temp[0].x;
                phDir2.y = temp[0].y;
            }
        } else if (temp.size() == 3) {
            if (i == 0) {
                phDir2.x = temp[1].x;
                phDir2.y = temp[1].y;
            } else if (i == 1) {
                phDir2.x = temp[2].x;
                phDir2.y = temp[2].y;
            } else if (i == 2) {
                phDir2.x = temp[1].x;
                phDir2.y = temp[1].y;
            }
        }
    }
    phPos2.x += phDir2.x;
    phPos2.y += phDir2.y;
    phSprite2.pos.x += phDir2.x * (9.5 * _speed);
    phSprite2.pos.y += phDir2.y * (19 * _speed);
    return;
}

void Arcade::PacMan::collisionMapPhantom3()
{
    int i = 0;
    std::vector<graphical_vector_t> temp;

    if (_map[phPos3.y + 1][phPos3.x] != '#' && _map[phPos3.y + 1][phPos3.x] != 'x') {
        temp.push_back(graphical_vector_t(0, 1));
    }
    if (_map[phPos3.y - 1][phPos3.x] != '#' && _map[phPos3.y - 1][phPos3.x] != 'x') {
        temp.push_back(graphical_vector_t(0, -1));
    }
    if (_map[phPos3.y][phPos3.x + 1] != '#' && _map[phPos3.y][phPos3.x + 1] != 'x') {
        temp.push_back(graphical_vector_t(1, 0));
    }
    if (_map[phPos3.y][phPos3.x - 1] != '#' && _map[phPos3.y][phPos3.x - 1] != 'x') {
        temp.push_back(graphical_vector_t(-1, 0));
    }
    if (temp.size() == 0)
        return;
    i = rand() % temp.size();
    if (phDir3.x == 0 && phDir3.y == 0) {
        phDir3.x = temp[i].x;
        phDir3.y = temp[i].y;
    }
    if (phDir3.x == -temp[i].x && phDir3.y == -temp[i].y) {
        phDir3.x = -temp[i].x;
        phDir3.y = -temp[i].y;
    } else {
        phDir3.x = temp[i].x;
        phDir3.y = temp[i].y;
    }
    if ((_map[phPos3.y + phDir3.y][phPos3.x + phDir3.x] == '#' ||  _map[phPos3.y + phDir3.y][phPos3.x + phDir3.x] == 'x') && temp.size() >= 2) {
        if (temp.size() == 2) {
            if (i == 0) {
                phDir3.x = temp[1].x;
                phDir3.y = temp[1].y;
            } else if (i == 1) {
                phDir3.x = temp[0].x;
                phDir3.y = temp[0].y;
            }
        } else if (temp.size() == 3) {
            if (i == 0) {
                phDir3.x = temp[1].x;
                phDir3.y = temp[1].y;
            } else if (i == 1) {
                phDir3.x = temp[2].x;
                phDir3.y = temp[2].y;
            } else if (i == 2) {
                phDir3.x = temp[1].x;
                phDir3.y = temp[1].y;
            }
        }
    }
    phPos3.x += phDir3.x;
    phPos3.y += phDir3.y;
    phSprite3.pos.x += phDir3.x * (9.5 * _speed);
    phSprite3.pos.y += phDir3.y * (19 * _speed);
    return;
}

void Arcade::PacMan::collisionMapPhantom4()
{
    int i = 0;
    std::vector<graphical_vector_t> temp;

    if (_map[phPos4.y + 1][phPos4.x] != '#' && _map[phPos4.y + 1][phPos4.x] != 'x') {
        temp.push_back(graphical_vector_t(0, 1));
    }
    if (_map[phPos4.y - 1][phPos4.x] != '#' && _map[phPos4.y - 1][phPos4.x] != 'x') {
        temp.push_back(graphical_vector_t(0, -1));
    }
    if (_map[phPos4.y][phPos4.x + 1] != '#' && _map[phPos4.y][phPos4.x + 1] != 'x') {
        temp.push_back(graphical_vector_t(1, 0));
    }
    if (_map[phPos4.y][phPos4.x - 1] != '#' && _map[phPos4.y][phPos4.x - 1] != 'x') {
        temp.push_back(graphical_vector_t(-1, 0));
    }
    if (temp.size() == 0)
        return;
    i = rand() % temp.size();
    if (phDir4.x == 0 && phDir4.y == 0) {
        phDir4.x = temp[i].x;
        phDir4.y = temp[i].y;
    }
    else if (phDir4.x == -temp[i].x && phDir4.y == -temp[i].y) {
        phDir4.x = -temp[i].x;
        phDir4.y = -temp[i].y;
    } else {
        phDir4.x = temp[i].x;
        phDir4.y = temp[i].y;
    }
    if ((_map[phPos4.y + phDir4.y][phPos4.x + phDir4.x] == '#' ||  _map[phPos4.y + phDir4.y][phPos4.x + phDir4.x] == 'x') && temp.size() >= 2) {
        if (temp.size() == 2) {
            if (i == 0) {
                phDir4.x = temp[1].x;
                phDir4.y = temp[1].y;
            } else if (i == 1) {
                phDir4.x = temp[0].x;
                phDir4.y = temp[0].y;
            }
        } else if (temp.size() == 3) {
            if (i == 0) {
                phDir4.x = temp[1].x;
                phDir4.y = temp[1].y;
            } else if (i == 1) {
                phDir4.x = temp[2].x;
                phDir4.y = temp[2].y;
            } else if (i == 2) {
                phDir4.x = temp[1].x;
                phDir4.y = temp[1].y;
            }
        }
    }
    phPos4.x += phDir4.x;
    phPos4.y += phDir4.y;
    phSprite4.pos.x += phDir4.x * (9.5 * _speed);
    phSprite4.pos.y += phDir4.y * (19 * _speed);
    return;
}

int Arcade::PacMan::collisionMap()
{
    if ((temppacDir.x == pacDir.x && temppacDir.y == pacDir.y) && (_map[pac_pos.y + pacDir.y][pac_pos.x] == '#' || _map[pac_pos.y][pac_pos.x + pacDir.x] == 'x' || _map[pac_pos.y + pacDir.y][pac_pos.x] == 'x')) {
        pacSprite.path = "Resources/Image/pacman_open.png";
        return 1;
    }
    if (_map[pac_pos.y + temppacDir.y][pac_pos.x] != '#' && _map[pac_pos.y][pac_pos.x + temppacDir.x] != 'x' && _map[pac_pos.y + temppacDir.y][pac_pos.x] != 'x') {
        pacDir.x = temppacDir.x;
        pacDir.y = temppacDir.y;
    }
    if (_map[pac_pos.y + pacDir.y][pac_pos.x + pacDir.x] == '#' || _map[pac_pos.y + pacDir.y][pac_pos.x + pacDir.x] == 'x') {
        pacSprite.path = "Resources/Image/pacman_open.png";
        return 1;
    }
    pac_pos.y += pacDir.y;
    pac_pos.x += pacDir.x;
    pacSprite.pos.x += pacDir.x * (9.5 * 2);
    pacSprite.pos.y += pacDir.y * (19 * 2);
    rotatePac();
    if (_map[pac_pos.y][pac_pos.x] == '.' || _map[pac_pos.y][pac_pos.x] == '*') {
        for (auto &e: _sprites) {
            if (has_collision(pacSprite, e) == true && e.toDraw == true) {
                if (_map[pac_pos.y][pac_pos.x] == '.')
                    score += 1;
                else if (_map[pac_pos.y][pac_pos.x] == '*')
                    score += 5;
                _textes[0].text = std::to_string(score);
            }
            if (has_collision(pacSprite, e) == true) {
                e.toDraw = false;
            }
        }
    }
    if (has_collision(pacSprite, bonusSprite) == true && bonusSprite.toDraw == true) {
        bonusSprite.toDraw = false;
        score += 250;
        _textes[0].text = std::to_string(score);
        _clockes["bonus"].restart();
    }
    return 0;
}

void Arcade::PacMan::checkNextLvl()
{
    int nbr = 0;

    for (auto &e: _sprites) {
        if (strcmp(e.path.c_str(), "Resources/Image/point_pacman.png") == 0 && e.toDraw == false) {
            nbr ++;
        }
    }
    if (nbr == 252)
        endLevel = true;
}

void Arcade::PacMan::pacGum()
{
    Clock cl;

    if (_map[pac_pos.y][pac_pos.x] == '*') {
        for (auto &e: _sprites) {
            if (has_collision(pacSprite, e) == true) {
                phSprite1.path = "Resources/Image/PacMan/dead_phantom.gif";
                phSprite2.path = "Resources/Image/PacMan/dead_phantom.gif";
                phSprite3.path = "Resources/Image/PacMan/dead_phantom.gif";
                phSprite4.path = "Resources/Image/PacMan/dead_phantom.gif";
                vuln1 = true;
                vuln2 = true;
                vuln3 = true;
                vuln4 = true;
                _textes[0].text = std::to_string(score);
            }
        }
    }
    _clockes.insert(std::make_pair("reset_ph", cl));
}
// TO DO LIST :

// - enregistrement du high score pour la personne;
// - si map fini reload avec ghost plus rapide;

void Arcade::PacMan::deadPac()
{
    if (has_collision(pacSprite, phSprite1) == true && vuln1 == false) {
        killPac = true;
    }
    if (has_collision(pacSprite, phSprite2) == true && vuln2 == false) {
        killPac = true;
    }
    if (has_collision(pacSprite, phSprite3) == true && vuln3 == false) {
        killPac = true;
    }
    if (has_collision(pacSprite, phSprite4) == true && vuln4 == false) {
        killPac = true;
    }
}

void Arcade::PacMan::checkDamage()
{
    Clock cl;

    if (has_collision(pacSprite, phSprite1) == true && vuln1 == true) {
        phSprite1.path = "Resources/Image/PacMan/eaten_phantom.png";
        dead1 = true;
        score += 100;
        _textes[0].text = std::to_string(score);
    }
    if (has_collision(pacSprite, phSprite2) == true && vuln2 == true) {
        phSprite2.path = "Resources/Image/PacMan/eaten_phantom.png";
        dead2 = true;
        score += 100;
        _textes[0].text = std::to_string(score);
    }
    if (has_collision(pacSprite, phSprite3) == true && vuln3 == true) {
        phSprite3.path = "Resources/Image/PacMan/eaten_phantom.png";
        dead3 = true;
        score += 100;
        _textes[0].text = std::to_string(score);
    }
    if (has_collision(pacSprite, phSprite4) == true && vuln4 == true) {
        phSprite4.path = "Resources/Image/PacMan/eaten_phantom.png";
        dead4 = true;
        score += 100;
        _textes[0].text = std::to_string(score);
    }
    _clockes.insert(std::make_pair("dead_time", cl));
}

void Arcade::PacMan::teleportation()
{
    if (_map[phPos1.y][phPos1.x] == 'T') {
        phSprite1.pos.x = tp2.x * (9.5 * 2);
        phSprite1.pos.y = tp2.y * (19 * 2);
        phPos1.x = tp2.x;
        phPos1.y = tp2.y;
        return;
    }
    if (_map[phPos1.y][phPos1.x] == 'U') {
        phSprite1.pos.x = tp1.x * (9.5 * 2);
        phSprite1.pos.y = tp1.y * (19 * 2);
        phPos1.x = tp1.x;
        phPos1.y = tp1.y;
    }

    if (_map[phPos2.y][phPos2.x] == 'T') {
        phSprite2.pos.x = tp2.x * (9.5 * 2);
        phSprite2.pos.y = tp2.y * (19 * 2);
        phPos2.x = tp2.x;
        phPos2.y = tp2.y;
        return;
    }
    if (_map[phPos2.y][phPos2.x] == 'U') {
        phSprite2.pos.x = tp1.x * (9.5 * 2);
        phSprite2.pos.y = tp1.y * (19 * 2);
        phPos2.x = tp1.x;
        phPos2.y = tp1.y;
    }

    if (_map[phPos3.y][phPos3.x] == 'T') {
        phSprite3.pos.x = tp2.x * (9.5 * 2);
        phSprite3.pos.y = tp2.y * (19 * 2);
        phPos3.x = tp2.x;
        phPos3.y = tp2.y;
        return;
    }
    if (_map[phPos3.y][phPos3.x] == 'U') {
        phSprite3.pos.x = tp1.x * (9.5 * 2);
        phSprite3.pos.y = tp1.y * (19 * 2);
        phPos3.x = tp1.x;
        phPos3.y = tp1.y;
    }

    if (_map[phPos4.y][phPos4.x] == 'T') {
        phSprite4.pos.x = tp2.x * (9.5 * 2);
        phSprite4.pos.y = tp2.y * (19 * 2);
        phPos4.x = tp2.x;
        phPos4.y = tp2.y;
        return;
    }
    if (_map[phPos4.y][phPos4.x] == 'U') {
        phSprite4.pos.x = tp1.x * (9.5 * 2);
        phSprite4.pos.y = tp1.y * (19 * 2);
        phPos4.x = tp1.x;
        phPos4.y = tp1.y;
    }

    if (_map[pac_pos.y][pac_pos.x] == 'T') {
        pacSprite.pos.x = tp2.x * (9.5 * 2);
        pacSprite.pos.y = tp2.y * (19 * 2);
        pac_pos.x = tp2.x;
        pac_pos.y = tp2.y;
        return;
    }
    if (_map[pac_pos.y][pac_pos.x] == 'U') {
        pacSprite.pos.x = tp1.x * (9.5 * 2);
        pacSprite.pos.y = tp1.y * (19 * 2);
        pac_pos.x = tp1.x;
        pac_pos.y = tp1.y;
    }
    return;
}

bool Arcade::PacMan::has_collision(graphical_sprite_t &spr1, graphical_sprite_t &spr2)
{
    return (!(spr1.pos.x > spr2.pos.x || spr1.pos.y > spr2.pos.y || spr1.pos.x + spr1.size.x < spr2.pos.x || spr1.pos.y + spr1.size.y < spr2.pos.y));
}

void Arcade::PacMan::saveScore()
{
    std::ifstream file;
    std::string tmp;
    std::string buffer;
    bool drawn = false;

    scoreArr.clear();
    scoreMap.clear();
    file.open("Resources/Leaderords/leaderboardPacman.txt");
    if (!file)
        exit(84);
    while (getline(file, tmp)) {
        scoreArr.push_back(tmp);
    }
    for (const auto &e: scoreArr)
    {
        // scoreMap[std::stoi(scoreArr.back().substr(0, scoreArr.back().find(" ") + 1))] = scoreArr.back().substr(scoreArr.back().find(" ") + 1, scoreArr.back().size());
        scoreMap.push_back(std::make_pair(e.substr(e.find(' ') + 1), atoi(e.substr(0, e.find(' ')).c_str())));
        // scoreArr.pop_back();
    }
    // int j = scoreMap.size() - 1;
    file.close();

    std::ofstream myfile;
    std::cout << score << std::endl;
    myfile.open("Resources/Leaderords/leaderboardPacman.txt", std::ofstream::out | std::ofstream::trunc);
    for (auto &e : scoreMap)
    {
        if (!drawn && score <= e.second)
        {
            if (_name.empty())
                myfile << std::to_string(score) + " " + "max" << std::endl;
            else
                myfile << std::to_string(score) + " " + _name << std::endl;
            drawn = true;
        }
        myfile << std::to_string(e.second) + " " + e.first << std::endl;
    } if (!drawn) {
        if (_name.empty())
            myfile << std::to_string(score) + " " + "max" << std::endl;
        else
            myfile << std::to_string(score) + " " + _name << std::endl;
    }
    myfile.close();
}

int Arcade::PacMan::check(const std::vector<Arcade::key> key) {
    if (!key.empty() && key[0] == ESCAPE)
        return (-12);
    if (!key.empty() && key[0] == KEYRIGHT) {
        temppacDir.x = 1;
        temppacDir.y = 0;
    }
    if (!key.empty() && key[0] == KEYLEFT) {
        temppacDir.x = -1;
        temppacDir.y = 0;
    }
    if (!key.empty() && key[0] == KEYUP) {
        temppacDir.x = 0;
        temppacDir.y = -1;
    }
    if (!key.empty() && key[0] == KEYDOWN) {
        temppacDir.x = 0;
        temppacDir.y = 1;
    }
    if (!key.empty()) {
        if (key[0] == KEY1)
            return 1;
        if (key[0] == KEY2)
            return 2;
        if (key[0] == KEY3)
            return 3;
        if (key[0] == KEY4)
            return 4;
        if (key[0] == KEY5)
            return 5;
        if (key[0] == KEY6 || killPac == true) {
            saveScore();
            return 6;
        }
        if (endLevel == true)
            return 7;
    }
    return (0);
}

const std::vector<Arcade::graphical_rectangle_t> Arcade::PacMan::getRectangles() {
    return (_rectangles);
}

const std::vector<Arcade::graphical_text_t> Arcade::PacMan::getTexts() {
    return (_textes);
}

const std::vector<Arcade::graphical_box_t> Arcade::PacMan::getBoxes() {
    return (_boxes);
}

const std::vector<Arcade::graphical_sprite_t> Arcade::PacMan::getSprites() {
    std::vector<graphical_sprite_t> check (_sprites);
    check.push_back(bonusSprite);
    check.push_back(pacSprite);
    check.push_back(phSprite1);
    check.push_back(phSprite2);
    check.push_back(phSprite3);
    check.push_back(phSprite4);
    return (check);
}

const std::vector<Arcade::graphical_rectangle_t> Arcade::PacMan::getSpecials()
{
    return (std::vector<graphical_rectangle_t>());
}

const std::vector<Arcade::graphical_sprite_t> Arcade::PacMan::getSpecialSprite()
{
    return (std::vector<graphical_sprite_t>());
}

void Arcade::PacMan::setName(const std::string &name)
{
    _name = name;
}

const std::vector<std::string> Arcade::PacMan::getSounds()
{
    return (std::vector<std::string>());
}

void Arcade::PacMan::setVitesse(const float &speed)
{
    _speed = speed;
    _setSpeed = true;
}

float Arcade::PacMan::getVitesse() const
{
    return (_speed + 0.5);
}

extern "C" std::shared_ptr<Arcade::IGameModule> entrypoint(void)
{
    return (std::make_shared<Arcade::PacMan>());
}