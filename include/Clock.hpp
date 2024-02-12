/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_
#include "Arcade.hpp"

class Arcade::Clock {
    public:
        Clock();
        ~Clock();
        
        float getElapsedTime(void);
        void restart();
     protected:
        std::chrono::_V2::steady_clock::time_point _start;
        std::chrono::_V2::steady_clock::time_point _checkPoint;
};

#endif /* !CLOCK_HPP_ */
