/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Arcade
*/

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <chrono>

namespace Arcade
{
    enum COLOR {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    typedef enum {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        KEY0,
        KEY1,
        KEY2,
        KEY3,
        KEY4,
        KEY5,
        KEY6,
        KEY7,
        KEY8,
        KEY9,
        ESCAPE,
        BACKSPACE,
        SPACE,
        ENTER,
        KEYUP,
        KEYDOWN,
        KEYLEFT,
        KEYRIGHT
    }key;

    static std::size_t giveId() {
        static std::size_t id = 0;

        id++;
        return (id);
    }
    typedef struct graphical_vector_s
    {
        graphical_vector_s(const float &x1 = 0, const float &y1 = 0, const float &z1 = 0) {
            x = x1;
            y = y1;
            z = z1;
        };
        float x;
        float y;
        float z;
    } graphical_vector_t;

    typedef struct graphical_color_s
    {
        graphical_color_s (const int &i1= 255, const int &i2= 255, const int &i3=255) {
            r = i1;
            g = i2;
            b = i3;
            a = 255;
        };
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
        Arcade::COLOR ncurse[2];
    } graphical_color_t;

    typedef struct graphical_text_s 
    {
        graphical_text_s(const std::string &txt = "", const graphical_vector_t &vec = graphical_vector_t(), const int &si = 0, const graphical_color_t &col = graphical_color_t(), bool tD = false): id(giveId()), toRefresh(true) {
            text = txt;
            pos = vec;
            size = si;
            color = col;
            toDraw = tD;
        };
        std::size_t id;
        bool toRefresh;
        std::string text;
        graphical_vector_t pos;
        int size;
        graphical_color_t color;
        bool toDraw;
    } graphical_text_t;

    typedef struct graphical_sprite_s
    {
        graphical_sprite_s(const std::string &path1 = "", const graphical_vector_t &pos1 = graphical_vector_t(), const graphical_vector_t &size1 = graphical_vector_t(), graphical_vector_t scale1 = graphical_vector_t(1, 1), float rot = 1, bool tD = false): id(giveId()), toRefresh(true) {
            path = path1;
            pos = pos1;
            size = size1;
            toDraw = tD;
            scale = scale1;
            rotation = rot;
        };
        std::size_t id;
        bool toRefresh;
        std::string path;
        graphical_vector_t pos;
        graphical_vector_t size;
        graphical_vector_t scale;
        float rotation;
        bool toDraw;
    } graphical_sprite_t;

    typedef struct graphical_box_s
    {
        graphical_box_s(const graphical_vector_t &p = graphical_vector_t(), const graphical_vector_t &s = graphical_vector_t(), const std::string &i = "",bool tD = false): id(giveId()), toRefresh(true) {
            pos = p;
            size = s;
            input = i;
            toDraw = tD;
        };
        std::size_t id;
        bool toRefresh;
        graphical_vector_t pos;
        graphical_vector_t size;
        std::string input;
        bool toDraw;
    } graphical_box_t;

    typedef struct graphical_rectangle_s
    {
        graphical_rectangle_s(const graphical_vector_t &p = graphical_vector_t(), const graphical_vector_t &s = graphical_vector_t(), bool fil = false, const graphical_color_t &col = graphical_color_t(), bool tD = false): id(giveId()),toRefresh(true) {
            pos = p;
            size = s;
            color = col;
            filled = fil;
            toDraw = tD;
        };
        std::size_t id;
        bool toRefresh;
        graphical_vector_t pos;
        graphical_vector_t size;
        bool filled;
        graphical_color_t color;
        bool toDraw;
    } graphical_rectangle_t;

    class Clock;
    class IGraphicalModule;
    class AGraphicalModule;
    class IGameModule;
    class WindowsSDL;
    class WindowsNcurses;
    class WindowSFML;
    class Element;
    class AGameModule;
    class Menu;
    class Core;
    class Solarfox;
    class PacMan;
    class Nibbler;
    class Reader;
}

#endif /* !ARCADE_HPP_ */
