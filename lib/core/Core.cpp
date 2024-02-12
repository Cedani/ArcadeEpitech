/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Core
*/

#include "../../include/Core.hpp"

Arcade::Core::Core(const std::string &path)
try : _game("arcade_menu.so"), _event(0), _reader(){
    std::vector <std::string> paths;
    std::string tmp;
    std::size_t idx = 0;
    for (struct dirent *all = _reader.getAll(); all; all = _reader.getAll()) {
        tmp = all->d_name;
        idx = tmp.find('.');
        if (idx == tmp.npos || tmp.substr(idx) != ".so")
            continue;
        paths.push_back(tmp);
    }
    for (const auto &e: paths) {
        try {
            _handles[e] = Opener<graphics>::openLib("./lib/" + e);
        } catch (const Errors::ArcadeError &e){
            throw e;
        }
    }
    _actualLibs["arcade_sdl2.so"] = Opener<graphics>::getFunctions(_handles["arcade_sdl2.so"], "entrypoint")();
    getGame(path);
}  catch (const Errors::ArcadeError &e) {
    throw e;
}

Arcade::Core::~Core()
{
    _actualLibs.clear();
    _actualGames.clear();
    // for (auto &e: _handles) {
    //     Opener<graphics>::closeLib(e.second);
    // }
}

void Arcade::Core::getGame(const std::string &path)
{
    std::ifstream stre(path);

    if (!stre.is_open())
        throw Errors::ArcadeError(path + ": no such file or directory", "Core.cpp, Arcade::Core::getGame, line 54");
    _lib = path.substr(path.find("arcade"));
    // std::cout << _lib << std::endl;
    loadLib();
    loadGame();
    loopGame();
}

void Arcade::Core::draw(const graphical_text_t &text)
{
    _actualLibs[_lib]->drawText(text);
}

void Arcade::Core::draw(const graphical_sprite_t &sprite)
{
    _actualLibs[_lib]->drawSprite(sprite);
}

void Arcade::Core::draw(const graphical_box_t &box)
{
    _actualLibs[_lib]->showInputBox(box);
}

void Arcade::Core::draw(const graphical_rectangle_t &rect)
{
    _actualLibs[_lib]->drawRectangle(rect);
}

void Arcade::Core::openWindow()
{
    _actualLibs[_lib]->openWindow();
    // if (debug ==  1)
    //     exit (84);
    _actualLibs[_lib]->clearWin();
}

void Arcade::Core::closeWindow()
{
    _actualLibs[_lib]->closeWindow();
}

void Arcade::Core::display()
{
    // _actualLibs[_lib]->clearWin();
    _actualLibs[_lib]->refreshWin();
}

const std::vector <Arcade::key> Arcade::Core::getEvent()
{
    return (_actualLibs[_lib]->check());
}

void Arcade::Core::setActualLib(const std::string &path)
{
    _lib = path;
}

void Arcade::Core::loadLib(void)
{
    graphics graph = Opener<graphics>::getFunctions(_handles[_lib], "entrypoint");

    _actualLibs.clear();
    _actualLibs.insert(std::pair<std::string, std::shared_ptr<IGraphicalModule>>(_lib, graph()));
}

void Arcade::Core::loadGame(void)
{
    games graph = Opener<games>::getFunctions(_handles[_game], "entrypoint");

    changedGame = true;
    _actualGames.clear();
    // std::cout << "lib" << std::endl;
    _actualGames.insert(std::pair<std::string, std::shared_ptr<IGameModule>>(_game, graph()));
}

void Arcade::Core::loopGame()
{
    std::string tmp = _lib;
    openWindow();
    if (changedGame) {
        _actualGames[_game]->setName(_name);
        _actualGames[_game]->startGame();
        changedGame = !changedGame;
    }
    if (changedSpeed) {
        _actualGames[_game]->setVitesse(_speed);        
        changedSpeed = false;
    }
    while (1) {
        _event = _actualGames[_game]->check(getEvent());
        if (_event != 0)
            break;
        _actualGames[_game]->updateGame();
        _actualLibs[_lib]->clearWin();
        drawer();
        display();
    }
    closeWindow();
    debug++;
    check();
}

void Arcade::Core::check()
{
    if (_event == -12)
        return;
    else if (_event == 1) {
        --*this;
        loadLib();
    } else if (_event == 2) {
        ++*this;
        loadLib();
    } else if (_event == 3) {
        previousGame();
        loadGame();
        // exit (84);
    } else if (_event == 4) {
        nextGame();
        loadGame();
    } else if (_event == 5)
        loadGame();
    else if (_event == 6) {
        _game = "arcade_menu.so";
        loadGame();
    } else if (_event == 7) {
        _speed = _actualGames[_game]->getVitesse();
        changedSpeed = true;
        loadGame();
    }
    else if (_event > 7) {
        if (_event == 11) {
            _lib = "arcade_sfml.so";
            _game = "arcade_pacman.so";
        } if (_event == 12) {
            _lib = "arcade_sfml.so";
            _game = "arcade_solarfox.so";
        } if (_event == 21) {
            _lib = "arcade_sdl2.so";
            _game = "arcade_pacman.so";
        } if (_event == 22) {
            _lib = "arcade_sdl2.so";
            _game = "arcade_solarfox.so";
        } if (_event == 31) {
            _lib = "arcade_ncurses.so";
            _game = "arcade_pacman.so";
        } if (_event == 32) {
            _lib = "arcade_ncurses.so";
            _game = "arcade_solarfox.so";
        }
        loadGame();
        loadLib();
    }
    // exit (83);
    loopGame();
}

void Arcade::Core::drawer()
{
    const std::vector<Arcade::graphical_rectangle_t> rects = _actualGames[_game]->getRectangles();
    const std::vector<Arcade::graphical_rectangle_t> specials = _actualGames[_game]->getSpecials();
    const std::vector<Arcade::graphical_text_t> texts = _actualGames[_game]->getTexts();
    const std::vector<Arcade::graphical_box_t> boxes = _actualGames[_game]->getBoxes();
    const std::vector<Arcade::graphical_sprite_t> sprites = _actualGames[_game]->getSprites();
    const std::vector<Arcade::graphical_sprite_t> SpecialSprites = _actualGames[_game]->getSpecialSprite();
    const std::vector<std::string> sounds = _actualGames[_game]->getSounds();

    for (const auto &e: sounds)
        _actualLibs[_lib]->playSound(e);
    for (const auto &e: boxes)
        draw(e);
    for (const auto &e: rects)
        draw(e);
    for (const auto &e: sprites)
        draw(e);
    for (const auto &e: specials)
        draw(e);
    for (const auto &e: texts)
        draw(e);
    for (const auto &e: SpecialSprites)
        draw(e);
    if (_game == "arcade_menu.so" && !boxes.empty())
        _name = boxes[0].input;
}

// menu pacman solarfox

void Arcade::Core::nextGame()
{
    if (_game == "arcade_menu.so")
        _game = "arcade_pacman.so";
    else if (_game == "arcade_pacman.so")
        _game = "arcade_solarfox.so";
    else if (_game == "arcade_solarfox.so")
        _game = "arcade_menu.so";
}

void Arcade::Core::previousGame()
{
    // std::cout << _game << std::endl;
    if (_game == "arcade_menu.so")
        _game = "arcade_solarfox.so";
    else if (_game == "arcade_solarfox.so")
        _game = "arcade_pacman.so";
    else if (_game == "arcade_pacman.so")
        _game = "arcade_menu.so";
}

// sdl2 sfml ncurses
// menu nibler pacman

Arcade::Core &Arcade::Core::operator++()
{
    if (_lib == "arcade_sfml.so")
        _lib = "arcade_ncurses.so";
    else if (_lib == "arcade_ncurses.so")
        _lib = "arcade_sdl2.so";
    else if (_lib  == "arcade_sdl2.so")
        _lib = "arcade_sfml.so";
    return (*this);
}

Arcade::Core &Arcade::Core::operator--()
{
    if (_lib == "arcade_sfml.so")
        _lib = "arcade_sdl2.so";
    else if (_lib == "arcade_sdl2.so")
        _lib = "arcade_ncurses.so";
    else if (_lib  == "arcade_ncurses.so")
        _lib = "arcade_sfml.so";
    return (*this);
}

extern "C" std::shared_ptr<Arcade::Core> entrypoint(const std::string &path)
{
    return (std::make_shared<Arcade::Core>(path));
}

//                                  Core
//  game                                                        graphics