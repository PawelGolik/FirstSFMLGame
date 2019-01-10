#include <iostream>
#include "Block.hpp"
#include "Player.hpp"
#include "WinScreen.hpp"
#include <SFML/Graphics.hpp>
#include "list"

using namespace std;
using namespace sf;

#define NUMBERINROW 3

void PrintWinLostTable(int **Table);

main(int argc, char const *argv[])
{
    int **WinLoseTable = new int *[NUMBERINROW];
    for (int i = 0; i < NUMBERINROW; i++)
    {
        WinLoseTable[i] = new int[NUMBERINROW];
        for (int j = 0; j < NUMBERINROW; j++)
        {
            WinLoseTable[i][j] = 0;
        }
    }
    Player Player1 = {"Resources\\OsignTransparent.png", NUMBERINROW};
    Player Player2 = {"Resources\\XsignTransparetn.png", NUMBERINROW};
    RenderWindow window(VideoMode(800, 600), "TicTacToe");
    WinScreen winScreen = {"Resources\\arial.ttf", "Resources\\XsignTransparetn.png", "Resources\\OsignTransparent.png", window.getSize()};
    window.setActive(true);
    std::list<Block> _blocks;
    bool gameover = false;
    int moves = 0;
    bool _PlayerSwitch = true;
    float sizeX = (800 - 59) / 3;
    float sizeY = (600 - 59) / 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
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
            window.clear(Color::White);
            window.draw(winScreen);
            window.display();
            continue;
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
                WinLoseTable[i][j] = -1;
                WinLoseTable[i][j] = 1;
                PrintWinLostTable(WinLoseTable);
                moves++;
            }
            else if (!_PlayerSwitch && block.WasClicked(window))
            {
                list<int> selectedField = Player2.setSpriteSizeAndPosition(block.getSize(), block.getPosition(), window.getSize());
                _PlayerSwitch = !_PlayerSwitch;
                int i = selectedField.front();
                selectedField.pop_front();
                int j = selectedField.front();
                WinLoseTable[i][j] = -1;
                PrintWinLostTable(WinLoseTable);
                moves++;
            }
            window.draw(block);
        }
        window.draw(Player1);
        window.draw(Player2);
        if (Player1.win())
        {
            window.clear(Color::White);
            winScreen.setWinner(_PlayerSwitch);
            gameover = true;            
        }
        if (Player2.win())
        {
            window.clear(Color::White);
            winScreen.setWinner(_PlayerSwitch);
            gameover = true;
        }
        if (NUMBERINROW * NUMBERINROW == moves)
        {
            window.clear(Color::White);
            winScreen.setWinner();
            gameover = true;
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

void PrintWinLostTable(int **Table)
{
    for (int i = 0; i < 3; i++)
    {
        cout << "|"
             << "\t";
        for (int j = 0; j < 3; j++)
        {
            cout << Table[j][i] << "\t"
                 << "|"
                 << "\t";
        }
        cout << endl;
    }
    cout << endl;
}