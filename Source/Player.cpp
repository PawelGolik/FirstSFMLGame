#include "Player.hpp"

Player::Player(std::string texture, int numberinrow)
{
    _texture.loadFromFile(texture);
    _numberinrow = numberinrow;
    _placedCrosses = new int *[_numberinrow];
    for (int i = 0; i < _numberinrow; i++)
    {
        _placedCrosses[i] = new int[_numberinrow];
        for (int j = 0; j < _numberinrow; j++)
        {
            _placedCrosses[i][j] = 0;
        }
    }
}

Player::~Player()
{
    for (int i = 0; i < _numberinrow; i++)
    {
        delete _placedCrosses[i];
    }
    delete _placedCrosses;
}

std::list<int> Player::setSpriteSizeAndPosition(Vector2f size, Vector2f positon, Vector2u windowSize)
{
    int bPx = positon.x;
    int bPy = positon.y;
    float wSx = windowSize.x / 3;
    float wSy = windowSize.y / 3;
    int x = wSx > bPx ? 0 : wSx * 2 > bPx ? 1 : 2;
    int y = wSy > bPy ? 0 : wSy * 2 > bPy ? 1 : 2;
    Sprite sprite;
    sprite.setTexture(_texture);
    sprite.setPosition(positon);
    sprite.setScale(_texture.getSize().x / size.x, _texture.getSize().y / size.y);
    sprite.setOrigin(sprite.getScale().x * _texture.getSize().x, sprite.getScale().y * _texture.getSize().y);
    _sprite.push_back(sprite);
    _placedCrosses[y][x] = 1;
    return {x, y};
}
void Player::draw(RenderTarget &target, RenderStates state) const
{
    for (auto sprite : _sprite)
    {
        target.draw(sprite);
    }
}
bool Player::win()
{
    for (int y = 0; y < _numberinrow; y++)
    {
        int diagonal1Win = 0;
        int diagonal2Win = 0;
        int verticalWin = 0;
        int horisontalWin = 0;
        for (int x = 0; x < _numberinrow; x++)
        {
            if (this->_placedCrosses[y][x] == 1)
            {
                verticalWin++;
            }
            if (this->_placedCrosses[x][y] == 1)
            {
                horisontalWin++;
            }
            if (diagonal({x, x}))
            {
                diagonal1Win++;
            }
            if (diagonal({x, (_numberinrow-1)-x}))
            {
                diagonal2Win++;
            }
            if (verticalWin == 3 || horisontalWin == 3 || diagonal1Win == 3 || diagonal2Win == 3)
            {
                return true;
            }
        }
    }
    return false;
}


bool Player::diagonal(Vector2i xy)
{
    if (_placedCrosses[xy.y][xy.x] == 1)
    {
        return true;
    }
    return false;
}