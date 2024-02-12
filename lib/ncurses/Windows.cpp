/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Windows
*/

#include "../../include/ncurses/Windows.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ncurses.h>
#include <curses.h>
#include <fcntl.h>
#include <iterator>
#include <iostream>
#include <string>
#include <fstream>

Arcade::WindowsNcurses::WindowsNcurses()
{
    // this->openWindow();
}

Arcade::WindowsNcurses::~WindowsNcurses()
{
    // this->closeWindow();
}

Arcade::WindowsNcurses::WindowsNcurses(const WindowsNcurses &other)
{
    // winCPU = newwin(56, 204, 255, 255);
    (void)other;
}

void Arcade::WindowsNcurses::refreshWin()
{
    refresh();
    for (auto &e : windowMapRect)
    {
        wrefresh(e.second.first);
    }
    for (auto &e : windowMapBox)
    {
        wrefresh(e.second.first);
    }
}

void Arcade::WindowsNcurses::clearWin()
{
    erase();
    for (auto &e : windowMapRect)
    {
        werase(e.second.first);
        if (e.second.second.toDraw == true)
            box(e.second.first, 0, 0);
    }
    for (auto &e : windowMapBox)
    {
        werase(e.second.first);
        if (e.second.second.toDraw == true)
        {
            box(e.second.first, 0, 0);
            mvprintw(e.second.second.pos.y * 55 / 1080 + 2, e.second.second.pos.x * 203 / 1920 + 3, e.second.second.input.c_str());
        }
    }
}

void Arcade::WindowsNcurses::openWindow()
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    cbreak();
    scrollok(stdscr, TRUE);
    start_color();
    // mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    // insertln();
    curs_set(0);
}

void Arcade::WindowsNcurses::closeWindow()
{
    endwin();
}

void Arcade::WindowsNcurses::drawText(const graphical_text_t &displaytext)
{
    if (!displaytext.toDraw)
        return;
    int x = 0;
    int y = 0;
    for (int i = 0; displaytext.text[i]; i++, x++)
    {
        if (displaytext.text[i] == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        std::string display;
        display.push_back(displaytext.text.at(i));
        mvprintw(displaytext.pos.y * 55 / 1080 + y, displaytext.pos.x * 203 / 1920 + x, display.c_str());
    }
}

void Arcade::WindowsNcurses::drawRectangle(const graphical_rectangle_t &rect)
{
    // if (!rect.toDraw)
    //     return;
    // std::cout << rect.toDraw << std::endl;
    // if (windowMapRect.find(rect.id) == windowMapRect.end())
    // {
        if (rect.filled == true) {
            init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA);
            attron(COLOR_PAIR(1));
            mvprintw(rect.pos.y * LINES / 1080, rect.pos.x * COLS / 1920, "  ");
            attroff(COLOR_PAIR(1));
            return;
        }
        int x = 0;
        std::string display = "";
        for (int i = 0; i < rect.size.x * COLS / 1920; i++) {
            if (i == 0) {
                display += " ";
                continue;
            }
            display += "_";
        }
        display += " ";
        mvprintw(rect.pos.y * LINES / 1080, rect.pos.x * COLS / 1920, display.c_str());
        for (; x <  rect.size.y * LINES / 1080 - 1; x++) {
            display = "";
            for (int i = 0; i < rect.size.x * COLS / 1920; i++) {
                if (i == 0) {
                    display += "|";
                    continue;
                }
                display += " ";
            }
            display += "|";
            mvprintw(rect.pos.y * LINES / 1080 + x + 1, rect.pos.x * COLS / 1920, display.c_str());
        }
        display = "";
        for (int i = 0; i < rect.size.x * COLS / 1920; i++) {
            if (i == 0) {
                display += "|";
                continue;
            }
            display += "_";
        }
        display += "|";
        mvprintw(rect.pos.y * LINES / 1080 + x + 1, rect.pos.x * COLS / 1920,display.c_str());
}

void Arcade::WindowsNcurses::showInputBox(const graphical_box_t &boxi)
{
    // if (!boxi.toDraw)
    //     return;
    if (windowMapBox.find(boxi.id) == windowMapBox.end())
    {
        mvprintw(boxi.pos.y * 55 / 1080 + 2, boxi.pos.x * 203 / 1920 + 3, boxi.input.c_str());
        windowMapBox[boxi.id].first = subwin(stdscr, boxi.size.y * 55 / 1080, boxi.size.x * 203 / 1920, boxi.pos.y * 55 / 1080, boxi.pos.x * 203 / 1920);
        windowMapBox[boxi.id].second = boxi;
    }
    else
    {
        windowMapBox.at(boxi.id).second = boxi;
    }
}

void Arcade::WindowsNcurses::drawSprite(const graphical_sprite_t &sprite)
{
    std::ifstream file;
    std::string tmp;
    std::string buffer;

    int y = 0;
    if (sprite.toDraw == false)
        return;
    file.open(sprite.path.substr(0, sprite.path.length() - 4) + ".txt");
    // if (!file)
    //     exit (84);
    while (getline(file, tmp))
    {
        y++;
        buffer = tmp;
        mvprintw(sprite.pos.y * 55 / 1080 - 1 + y, sprite.pos.x * 203 / 1920, buffer.c_str());
    }
    file.close();
}

const std::vector<Arcade::key> Arcade::WindowsNcurses::check()
{
    std::vector<Arcade::key> _ret;
    int b = getch();

    if (b == 27)
    {
        _ret.push_back(ESCAPE);
        return (_ret);
    }
    for (int i = 97; i <= 122; i++)
    {
        if (b == i)
            _ret.push_back(Arcade::key(i - 97));
    }
    if (b == 32)
        _ret.push_back(Arcade::key(SPACE));
    if (b == KEY_UP)
        _ret.push_back(Arcade::key(KEYUP));
    if (b == KEY_DOWN)
        _ret.push_back(Arcade::key(KEYDOWN));
    if (b == KEY_RIGHT)
        _ret.push_back(Arcade::key(KEYRIGHT));
    if (b == KEY_LEFT)
        _ret.push_back(Arcade::key(KEYLEFT));
    if (b == 10)
        _ret.push_back(Arcade::key(ENTER));
    if (b == 263)
        _ret.push_back(Arcade::key(BACKSPACE));
    // for (int i = 48; i <= 57; i++) {
    //     if (b == i)
    //         _ret.push_back(Arcade::key(i - 48 + 26));
    // }
    if (b == 38)
        _ret.push_back(Arcade::key(KEY1));
    if (b == 169)
        _ret.push_back(Arcade::key(KEY2));
    if (b == 34)
        _ret.push_back(Arcade::key(KEY3));
    if (b == 39)
        _ret.push_back(Arcade::key(KEY4));
    if (b == 40)
        _ret.push_back(Arcade::key(KEY5));
    if (b == 45)
        _ret.push_back(Arcade::key(KEY6));
    if (b == 168)
        _ret.push_back(Arcade::key(KEY7));
    if (b == 95)
        _ret.push_back(Arcade::key(KEY8));
    if (b == 167)
        _ret.push_back(Arcade::key(KEY9));
    if (b == 160)
        _ret.push_back(Arcade::key(KEY0));
    return (_ret);
}

void Arcade::WindowsNcurses::playSound(const std::string &path)
{
    (void)path;
}

extern "C" std::shared_ptr<Arcade::IGraphicalModule> entrypoint(void)
{
    return (std::make_shared<Arcade::WindowsNcurses>());
}