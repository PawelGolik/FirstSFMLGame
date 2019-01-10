
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

enum GameOver
{
    WIN,
    DRAW
};

class WinScreen : public Drawable
{
  private:
    GameOver gameover = GameOver::WIN;
    Texture _player1, _player2;
    Sprite _winPlayer1, _winPlayer2;
    Text _text;
    Font _font;
    bool _playerWon;

  public:
    WinScreen(std::string fontPath, std::string Player1, std::string Player2, Vector2u windowSize);
    ~WinScreen();
    void setWinner(bool playerWon);
    void setWinner();
    void draw(RenderTarget &target, RenderStates state) const override;
};

WinScreen::WinScreen(std::string fontPath, std::string Player1, std::string Player2, Vector2u windowSize)
{
    _player1.loadFromFile(Player1);
    _player2.loadFromFile(Player2);
    _winPlayer1.setTexture(_player1);
    _winPlayer2.setTexture(_player2);
    _winPlayer1.setOrigin({_winPlayer1.getLocalBounds().width/2, _winPlayer1.getLocalBounds().height/2});
    _winPlayer2.setOrigin({_winPlayer2.getLocalBounds().width/2, _winPlayer2.getLocalBounds().height/2});
    _font.loadFromFile(fontPath);
    _text.setFont(_font);
    _text.setFillColor(Color::Black);
    _text.setString("Won !");
    _text.setCharacterSize(60);
    _text.setOrigin(_text.getGlobalBounds().width/2, _text.getGlobalBounds().height/2);
    _text.setPosition({(float)windowSize.x/2,100});
    _winPlayer1.setPosition({(float)windowSize.x / 2, _text.getGlobalBounds().height + 100 + _winPlayer1.getLocalBounds().height / 2});
    _winPlayer2.setPosition({(float)windowSize.x / 2, _text.getGlobalBounds().height + 100 + _winPlayer2.getLocalBounds().height / 2});
}

void WinScreen::setWinner(bool playerWon)
{
    _playerWon = playerWon;
}
void WinScreen::setWinner()
{
    _text.setString("Draw !");
    gameover = GameOver::DRAW;
}

WinScreen::~WinScreen()
{
}

void WinScreen::draw(RenderTarget &target, RenderStates state) const
{
    target.draw(_text);
    if (gameover == GameOver::DRAW){
        return;
    }
    if (_playerWon){
        target.draw(_winPlayer1);
        return;
    }
    target.draw(_winPlayer2);
}