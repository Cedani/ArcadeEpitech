/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Error
*/

#include "../../../include/Errors.hpp"

Errors::ArcadeError::ArcadeError(const std::string &message, const std::string &whe) noexcept: _message(message), _where(whe)
{
}

Errors::ArcadeError::~ArcadeError()
{
}

const char *Errors::ArcadeError::what() const noexcept
{
    return (_message.c_str());
}

const std::string &Errors::ArcadeError::where() const
{
    return (_where);
}