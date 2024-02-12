/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include <iostream>
#include <unordered_map>
#include <string>
#include <dirent.h>
#include <vector>
#include <fstream>
#include "Arcade.hpp"
#include "Opener.hpp"
#include "Errors.hpp"
#include "IGameModule.hpp"
#include "IGraphicalModule.hpp"

class Arcade::Reader {
    public:
        Reader(const std::string &path = "./lib"): _directory(opendir(path.c_str())), _all(nullptr) {
            if (!_directory)
                throw Errors::ArcadeError("no such file or directory", "Rea.hpp, Reader::Reader(), line 62");
        };
        ~Reader() {
            closedir(_directory);
        };
    
        struct dirent *getAll() {
            _all = readdir(_directory);
            return (_all);
        };
    private:
        DIR *_directory;
        struct dirent *_all;
};

class Arcade::Core {
    public:
        Core(const std::string &path);
        ~Core();

        void draw(const graphical_text_t &);
        void draw(const graphical_sprite_t &);
        void draw(const graphical_box_t &);
        void draw(const graphical_rectangle_t &);
        void getGame(const std::string &path);
        const std::vector <Arcade::key> getEvent(void);
        void openWindow();
        void display();
        void closeWindow();
        void setActualLib(const std::string &);
        Core & operator++();
        Core & operator--();
        void check();
        void loadLib(void);
        void loopGame();
        void loadGame();
        void nextGame();
        void previousGame();
        void drawer();

    private:
        std::string _game;
        int _event;
        Reader _reader;
        std::unordered_map<std::string, void *> _handles;
        std::unordered_map<std::string, std::shared_ptr<IGraphicalModule>> _actualLibs;
        std::unordered_map<std::string, std::shared_ptr<IGameModule>> _actualGames;
        std::string _lib;
        bool changedGame = true;
        std::string _name;
        int debug = 0;
        float _speed;
        bool changedSpeed = false;
};


#endif /* !CORE_HPP_ */
