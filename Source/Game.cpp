#include <iostream>
#include "Block.hpp"
#include "Player.hpp"
#include "WinScreen.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "list"

using namespace std;
using namespace sf;

#define NUMBERINROW 3

void PrintWinLostTable(char **Table);
list<int> minmax(char **actualTable, int layers, bool actualPlayer, int moves);

main(int argc, char const *argv[])
{
    srand(time(NULL));
    char **WinLoseTable = new char *[NUMBERINROW];
    for (int i = 0; i < NUMBERINROW; i++)
    {
        WinLoseTable[i] = new char[NUMBERINROW];
        for (int j = 0; j < NUMBERINROW; j++)
        {
            WinLoseTable[i][j] = 'E';
        }
    }
    Player Player1 = {"Resources\\OsignTransparent.png", NUMBERINROW};
    Player Computer = {"Resources\\XsignTransparetn.png", NUMBERINROW};
    RenderWindow window(VideoMode(800, 600), "TicTacToe");
    WinScreen winScreen = {"Resources\\arial.ttf", "Resources\\XsignTransparetn.png", "Resources\\OsignTransparent.png", window.getSize()};
    window.setActive(true);
    std::list<Block> _blocks;
    bool gameover = false;
    int moves = 0;
    bool _PlayerSwitch = (rand() % 100) < 50 ? true : false;
    float sizeX = (800 - 59) / 3;
    float sizeY = (600 - 59) / 3;
    Time t1;
    Clock clock;
    for (int i = 0; i < NUMBERINROW; i++)
    {
        for (int j = 0; j < NUMBERINROW; j++)
        {
            _blocks.push_back({{sizeX, sizeY},
                               {i * sizeX + 30 * i, j * sizeY + 30 * j}});
        }
    }
    window.setFramerateLimit(60);
    Event ev;
    while (window.isOpen())
    {
        window.clear();
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
            {
                window.close();
            }
        }
        if (gameover)
        {

            if (Mouse::isButtonPressed(Mouse::Button::Left) && (t1.asSeconds() + 1 < clock.getElapsedTime().asSeconds()) )
            {
                Computer = {"Resources\\XsignTransparetn.png", NUMBERINROW};
                Player1 = {"Resources\\OsignTransparent.png", NUMBERINROW};
                gameover = false;
                moves = 0;
                clock.restart();
                t1 = Time::Zero;
                _PlayerSwitch = (rand() % 100) < 50 ? true : false;
                _blocks.clear();
                for (int i = 0; i < NUMBERINROW; i++)
                {
                    for (int j = 0; j < NUMBERINROW; j++)
                    {
                        WinLoseTable[i][j] = 'E';
                        _blocks.push_back({{sizeX, sizeY},
                                           {i * sizeX + 30 * i, j * sizeY + 30 * j}});
                    }
                }
            }
            window.clear(Color::White);
            window.draw(winScreen);
            window.display();
            continue;
        }
        if (!_PlayerSwitch)
        {
            list<int> selectedField = minmax(WinLoseTable, 0, true, moves);
            int y = selectedField.front();
            selectedField.pop_front();
            int x = selectedField.front();
            list<Block>::iterator it = _blocks.begin();
            advance(it, y * NUMBERINROW + x);
            it->setWasClicked(true);
            Computer.setSpriteSizeAndPosition(it->getSize(), it->getPosition(), window.getSize());
            WinLoseTable[y][x] = 'X';
            PrintWinLostTable(WinLoseTable);
            _PlayerSwitch = !_PlayerSwitch;
            moves++;
        }
        for (auto &block : _blocks)
        {
            if (_PlayerSwitch && block.WasClicked(window))
            {
                list<int> selectedField = Player1.setSpriteSizeAndPosition(block.getSize(), block.getPosition(), window.getSize());
                _PlayerSwitch = !_PlayerSwitch;
                int i = selectedField.front();
                selectedField.pop_front();
                int j = selectedField.front();
                WinLoseTable[i][j] = 'O';
                PrintWinLostTable(WinLoseTable);
                moves++;
            }
            window.draw(block);
        }

        window.draw(Player1);
        window.draw(Computer);
        if (Player1.win())
        {
            window.clear(Color::White);
            winScreen.setWinner(_PlayerSwitch);
            gameover = true;
            t1 = clock.getElapsedTime();
            continue;
        }
        if (Computer.win())
        {
            window.clear(Color::White);
            winScreen.setWinner(_PlayerSwitch);
            gameover = true;
            t1 = clock.getElapsedTime();
            continue;
        }
        if (NUMBERINROW * NUMBERINROW == moves)
        {
            window.clear(Color::White);
            winScreen.setWinner();
            gameover = true;
            t1 = clock.getElapsedTime();
            continue;
        }
        window.display();
    }

    for (int i = 0; i < NUMBERINROW; i++)
    {
        delete WinLoseTable[i];
    }
    delete WinLoseTable;
    return 0;
}

void PrintWinLostTable(char **Table)
{
    for (int i = 0; i < NUMBERINROW; i++)
    {
        cout << "|"
             << "\t";
        for (int j = 0; j < NUMBERINROW; j++)
        {
            cout << Table[j][i] << "\t"
                 << "|"
                 << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

list<int> minmax(char **actualTable, int layers, bool actualPlayer, int moves)
{
    if (moves == NUMBERINROW * NUMBERINROW || layers == 3)
    {
        return {0};
    }
    int BestX, BestY;
    int signToScore = actualPlayer ? 1 : -1;
    int BestScore = -1 * signToScore * 99999999;
    char signToPut = actualPlayer ? 'X' : 'O'; // IF it is true then computers turn if not Player's one.
    list<list<int>> movesAndScore;
    for (int y = 0; y < NUMBERINROW; y++)
    {
        for (int x = 0; x < NUMBERINROW; x++)
        {
            if (actualTable[y][x] == 'E')
            {
                actualTable[y][x] = signToPut;
                movesAndScore.push_back({y, x, minmax(actualTable, layers + 1, !actualPlayer, moves + 1).back()});
                actualTable[y][x] = 'E';
            }
        }
    }
    for (auto i : movesAndScore)
    {
        int score = i.back();
        i.pop_back();
        int x = i.back();
        i.pop_back();
        int y = i.back();
        int Vertical = 0;
        int Horizontal = 0;
        int diagonal1 = 0, diagonal2 = 0;
        actualTable[y][x] = signToPut;
        for (int z = 0; z < NUMBERINROW; z++)
        {
            if (actualTable[z][x] == signToPut && Horizontal >= 0)
            {
                Horizontal += 1;
            }
            else if (actualTable[z][x] != signToPut && actualTable[z][x] != 'E')
            {
                Horizontal = -1;
            }
            if (actualTable[y][z] == signToPut && Vertical >= 0)
            {
                Vertical += 1;
            }
            else if (actualTable[y][z] != signToPut && actualTable[y][z] != 'E')
            {
                Vertical = -1;
            }
            if (x == y && actualTable[z][z] == signToPut && diagonal1 >= 0)
            {
                diagonal1 += 1;
            }
            else if (actualTable[z][z] != signToPut && actualTable[z][z] != 'E')
            {
                diagonal1 = -1;
            }
            if (actualTable[z][NUMBERINROW - z - 1] == signToPut && diagonal2 >= 0)
            {
                diagonal2 += 1;
            }
            else if (actualTable[z][NUMBERINROW - z - 1] != signToPut && actualTable[z][NUMBERINROW - z - 1] != 'E')
            {
                diagonal2 = -1;
            }
        }
        score += signToScore * (Vertical > 0 ? pow(10, Vertical) : 0) +
                 signToScore * (Horizontal > 0 ? pow(10, Horizontal) : 0) +
                 signToScore * (diagonal1 > 0 ? pow(10, diagonal1) : 0) +
                 signToScore * (diagonal2 > 0 ? pow(10, diagonal2) : 0);
        score = layers != 0 ? score / layers : score;

        actualTable[y][x] = 'E';
        if (actualPlayer ? score >= BestScore : score <= BestScore)
        {
            BestScore = score;
            BestX = x;
            BestY = y;
        }
    }
    return {BestY, BestX, BestScore};
}