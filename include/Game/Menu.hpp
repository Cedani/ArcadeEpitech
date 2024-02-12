/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "../IGameModule.hpp"
#include "../Arcade.hpp"
#include "../Clock.hpp"
template <typename T>
const std::vector<T> getGraphicalElement(std::map<std::string, T>m) {
    std::vector <T> ret;
    for (const auto &e: m)
        ret.push_back(e);
    return (ret);
};

class Arcade::Menu : public IGameModule {
    public:
        Menu();
        ~Menu();

        void startGame() final;
        void updateGame() final;
        int check(const std::vector<Arcade::key>) final;
        const std::vector<graphical_rectangle_t> getRectangles() final;
        const std::vector<graphical_text_t> getTexts() final;
        const std::vector<graphical_box_t> getBoxes() final;
        const std::vector<graphical_rectangle_t> getSpecials() final;
        const std::vector<graphical_sprite_t> getSprites() final;
        const std::vector<graphical_sprite_t> getSpecialSprite() final;
        void setName(const std::string &name) final;
        void sceneMenu(const Arcade::key);
        void sceneAfter();
        void drawOptions();
        void sceneFintro();
        void initFintro();
        void sceneFinal();
        void firstAnimation();
        void secondAnimation();
        void moveBackgroud();
        void moveParallax();
        void checkPos(graphical_sprite_t &);
        void moveCursor(const std::vector<key> &);
        void drawLateralMenu();
        bool hasCollision(graphical_rectangle_t &, graphical_sprite_t &);
        bool hasCollision(graphical_sprite_t &, graphical_sprite_t &);
        bool hasCollision(graphical_sprite_t &, graphical_rectangle_t &);
        void checkSnake(void);
        void eventClicked(void);
        void checkClicked(void);
        void showLateralMenu(void);
        void hideLateralMenu(void);
        void stopClicked();
        void drawSelection();
        void eventSelection();
        void resetLib();
        void resetGame();
        void setCoin();
        void eventCoin();
        const std::vector<std::string> getSounds();
        void quitMenu();
        void selectLib();
        void selectGame();
        void setVitesse(const float &) final;
        float getVitesse() const final;
        void drawLeaderboard();
        // void showLeaderboard(void);
        // void hideLeaderboard(void);
        void drawTextLeaderBoard(void);

    protected:
        int _scene;
        std::pair<std::string, graphical_rectangle_t> _cursor;
        bool _changed;
        std::vector<graphical_rectangle_t> _snake;
        std::map <std::string, graphical_rectangle_t> _rectangles;
        // std::vector<graphical_rectangle_t> _rectangles;
        std::map <std::string, graphical_text_t> _textes;
        std::vector <graphical_box_t> _boxes;
        std::vector <graphical_sprite_t> _sprites;
        std::vector <graphical_sprite_t> _Specialsprites;
        std::vector <graphical_rectangle_t> _Specials;
        Arcade::key _key;
        std::unordered_map<std::string, Clock> _clockes;
        graphical_rectangle_t _special;
        std::map<std::string, graphical_rectangle_t>_specialRec;
        bool _incr;
        bool _shown = false;
        bool _finish = false;
        std::vector<std::string> _sounds;
        bool soundCoin = true;
        bool soundMario = false;
        int _nbLib = 0;
        int _nbGame = 0;
        int _nbQuitMenu = -1;
        bool _shownL = false;
        bool  _finishL = false;
        std::vector<std::pair<std::string, std::string>> _scores;
        std::vector<graphical_text_t> _leader;
};

// box 1
// box 0
// small 1
// small 0
// 184, 133, 107


// 2 sfml
// 3 sdl2
// 4 ncurses
// 5 pacman
// 6 solarfox

#endif /* !MENU_HPP_ */
