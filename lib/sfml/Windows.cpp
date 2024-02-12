/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** WindowSFML
*/

#include "../../include/sfml/Windows.hpp"

Arcade::WindowSFML::WindowSFML(): toDisplay(true)
{
    _winSize.x = 800;
    _winSize.y = 600;
}

Arcade::WindowSFML::WindowSFML(const WindowSFML &other)
{
    (void)other;
}

Arcade::WindowSFML::~WindowSFML()
{
}

void Arcade::WindowSFML::drawText(const graphical_text_s &text)
{
    sf::Font font;
    sf::Text toDraw;

    if (!text.toDraw)
        return;
    font.loadFromFile("Resources/Roboto/Roboto-Black.ttf");
    toDraw.setFont(font);
    toDraw.setString(text.text);
    toDraw.setPosition(sf::Vector2f(text.pos.x, text.pos.y));
    toDraw.setFillColor(sf::Color(text.color.r, text.color.g, text.color.b));
    toDraw.setCharacterSize(text.size);
    _window.draw(toDraw);
}

void Arcade::WindowSFML::drawSprite(const graphical_sprite_t &sprite)
{
    // sf::Texture texture;
    sf::Sprite toDraw;

    if (!sprite.toDraw)
        return;
    if (_sprites.find(sprite.path) == _sprites.cend()) {
        _sprites[sprite.path] = sf::Texture();
        _sprites[sprite.path].loadFromFile(sprite.path);
    }
    //toDraw.setOrigin(sprite.size.x/2, sprite.size.y/2);
    //std::cout<<sprite.size.x/2<<std::endl;
    // std::cout << sprite.path << std::endl;
    // _sprites[sprite.path] = sf::Sprite();
    toDraw.setTexture(_sprites[sprite.path], true);
    toDraw.setPosition(sf::Vector2f(sprite.pos.x, sprite.pos.y));
    toDraw.setScale(sf::Vector2f(sprite.scale.x, sprite.scale.y));
    toDraw.setRotation(sprite.rotation);
    toDraw.scale(sf::Vector2f(sprite.size.x /_sprites[sprite.path].getSize().x, sprite.size.y / _sprites[sprite.path].getSize().y));
    // toDraw.setRotation(sprite.rotation);
    _window.draw(toDraw);
}

void Arcade::WindowSFML::drawRectangle(const graphical_rectangle_t &rect)
{
    sf::RectangleShape rectangle;

    if (!rect.toDraw)
        return;
    rectangle.setPosition(sf::Vector2f(rect.pos.x, rect.pos.y));
    rectangle.setSize(sf::Vector2f(rect.size.x, rect.size.y));
    rectangle.setOutlineColor(sf::Color(rect.color.r, rect.color.g, rect.color.b));
    rectangle.setOutlineThickness(-1);
    (rect.filled) ? rectangle.setFillColor(sf::Color(rect.color.r, rect.color.g, rect.color.b, rect.color.a)) : rectangle.setFillColor(sf::Color::Black);
    _window.draw(rectangle);
}

void Arcade::WindowSFML::drawCursor(float size, const graphical_box_t &box)
{
    graphical_vector_t pos(size * 45 + box.pos.x, box.pos.y + 5);
    graphical_vector_t sizeVec(1, 90);

    time = cl.getElapsedTime();
    if (time.asSeconds() > 1.0) {
        toDisplay = !toDisplay;
        cl.restart();
    }
    if (toDisplay)
        drawRectangle(graphical_rectangle_t(pos, sizeVec, true, graphical_color_t(), true));
}

void Arcade::WindowSFML::clearWin()
{
    _window.clear(sf::Color::Black);
}

void Arcade::WindowSFML::refreshWin()
{
    _window.display();
}

void Arcade::WindowSFML::openWindow()
{
    _window.create(sf::VideoMode(1920, 1080, 32), "myWindow", sf::Style::Fullscreen);
}

void Arcade::WindowSFML::closeWindow()
{
    _window.close();
}

void Arcade::WindowSFML::checkKey(std::vector<Arcade::key> &key)
{
    for (int i = 0; i <= sf::Keyboard::Escape; ++i) {
        if (_event.key.code == i)
            key.push_back(Arcade::key(i));
    }
    if (_event.key.code == sf::Keyboard::Quote)
        key.push_back(KEY4);
    if (_event.key.code == sf::Keyboard::Hyphen)
        key.push_back(KEY6);
    if (_event.key.code == sf::Keyboard::Backspace)
        key.push_back(BACKSPACE);
    if (_event.key.code == sf::Keyboard::Enter)
        key.push_back(ENTER);
    if (_event.key.code == sf::Keyboard::Space)
        key.push_back(SPACE);
    if (_event.key.code == sf::Keyboard::Up)
        key.push_back(KEYUP);
    if (_event.key.code == sf::Keyboard::Down)
        key.push_back(KEYDOWN);
    if (_event.key.code == sf::Keyboard::Left)
        key.push_back(KEYLEFT);
    if (_event.key.code == sf::Keyboard::Right)
        key.push_back(KEYRIGHT);
}

const std::vector<Arcade::key> Arcade::WindowSFML::check()
{
    std::vector<key> _ret;

    if (!_window.pollEvent(_event))
        return (_ret);
    if (_event.type == sf::Event::Closed)
        _ret.push_back(ESCAPE);
    if (_event.type == sf::Event::KeyPressed)
        checkKey(_ret);
    return (_ret);
}

void Arcade::WindowSFML::showInputBox(const graphical_box_t &box)
{
    if (!box.toDraw)
        return;
    drawRectangle(graphical_rectangle_t(box.pos, box.size, false, graphical_color_t(), true));
    drawText(graphical_text_t(box.input, box.pos, 70, graphical_color_t(), true));
    drawCursor(box.input.size(), box);
}

sf::Vector2f Arcade::WindowSFML::getNewVector(const graphical_vector_t &vec)
{
    sf::Vector2f newVec;
    sf::Vector2u winSize = _window.getSize();

    newVec.x = winSize.x * vec.x / 800;
    newVec.y = winSize.y * vec.y / 600;
    return (newVec);
}

void Arcade::WindowSFML::playSound(const std::string &path)
{
    sf::Sound sound;

    if (_sounds.find(path) == _sounds.cend()) {
        _sounds[path] = sf::SoundBuffer();
        _sounds[path].loadFromFile(path);
    }
    sound.setBuffer(_sounds[path]);
    sound.setVolume(50.0F);
    sound.setLoop(false);
    sound.play();
    while (sound.getStatus() != sf::Sound::Stopped);
    // sound.stop();
}

extern "C" std::shared_ptr<Arcade::IGraphicalModule> entrypoint(void)
{
    return (std::make_shared<Arcade::WindowSFML>());
}