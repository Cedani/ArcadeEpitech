/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** main
*/
#include <iostream>
#include <memory>
#include "../include/Opener.hpp"
#include "../include/Errors.hpp"

int main(int ac, char **av)
{
    try  {
        if (ac < 2)
            throw Errors::ArcadeError("no Initial library mentioned", "main.cpp, main function, line 18");
        void *handle = Opener<coreFunc>::openLib("./lib/arcade_core.so");
        coreFunc func = Opener<coreFunc>::getFunctions(handle, "entrypoint");
        std::shared_ptr<Arcade::Core> core = func(av[1]);
        Opener<coreFunc>::closeLib(handle);
    } catch (const Errors::ArcadeError &e){
        std::cout << e.what() << " in " + e.where() << std::endl;
        return (84);
    }
    return (0);
}