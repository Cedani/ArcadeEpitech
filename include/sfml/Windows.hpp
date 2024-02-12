/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** WindowSFML
*/

#ifndef WINDOWS_HPP_
#define WINDOWS_HPP_
#include "../IGraphicalModule.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

class Arcade::WindowSFML : public IGraphicalModule{
    public:
        WindowSFML();
        WindowSFML(const WindowSFML &);
        ~WindowSFML();

        void drawText(const graphical_text_t &text) final;
        void drawSprite(const graphical_sprite_t &sprite) final;
        void showInputBox(const graphical_box_t &box) final;
        void drawRectangle(const graphical_rectangle_t &rect) final;
        void clearWin() final;
        void refreshWin() final;
        const std::vector<Arcade::key> check() final;
        void openWindow() final;
        void closeWindow() final;
        void playSound(const std::string &) final;
        void checkKey(std::vector<Arcade::key> &);
        sf::Vector2f getNewVector(const graphical_vector_t &);
        void drawCursor(float, const graphical_box_t &);
    protected:
        bool toDisplay;
        sf::RenderWindow _window;
        sf::Event _event;
        graphical_vector_t _winSize;
        sf::Clock cl;
        sf::Time time;
        std::unordered_map<std::string, sf::Texture> _sprites;
        std::unordered_map<std::string, sf::SoundBuffer> _sounds;
};

#endif /* !WINDOWS_HPP_ */

// SFML             
// 
//                      NIBLER
// SDL2
//                      PACMAN
//
// NCURSES
// 
// 
// 
// 
// 
// 
// 
// 