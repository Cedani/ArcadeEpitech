/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Error
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_
#include "Arcade.hpp"
#include <exception>

namespace Errors {
    class ArcadeError;
};

class Errors::ArcadeError : public std::exception {
    public:
        ArcadeError(const std::string &, const std::string &) noexcept;
        ~ArcadeError();

        const char *what() const noexcept override;
        const std::string &where() const;
    private:
        std::string _message;
        std::string _where;
};

#endif /* !ERRORS_HPP_ */
