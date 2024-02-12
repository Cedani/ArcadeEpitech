/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Clock
*/

#include "../../include/Clock.hpp"

Arcade::Clock::Clock(): _start(std::chrono::steady_clock::now())
{
}

Arcade::Clock::~Clock()
{
}

float Arcade::Clock::getElapsedTime()
{

    std::chrono::duration<float> mSeconds;

    _checkPoint = std::chrono::steady_clock::now();
    mSeconds = std::chrono::duration_cast<std::chrono::microseconds>(_checkPoint - _start);
    return (mSeconds.count() * 1000000.0);
}

void Arcade::Clock::restart(void)
{
    _start = std::chrono::steady_clock::now();
}
