/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_
#include <iostream>
#include <unordered_map>
#include <dirent.h>
#include <vector>
#include "Arcade.hpp"
#include "Opener.hpp"
#include "Errors.hpp"
#include "IGameModule.hpp"

class Factory {
    public:
        Factory(const std::string &);
        ~Factory();

        const std::unordered_map<std::string, void *> getHandles(void) const;
        void getGame(const std::string &);
        void manage();
    protected:
        std::shared_ptr<Arcade::IGameModule> _actualGame;
        std::unordered_map<std::string, void *> _handles;
        // std::unordered_map<std::string, std::shared_ptr<Arcade::IGameModule>> _game;
};
#endif /* !FACTORY_HPP_ */
