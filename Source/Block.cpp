#include "Block.hpp"

Block::Block(Vector2f size, Vector2f position)
{
    Color color(255, 255, 255, 255);
    _block = RectangleShape(size);
    _block.setFillColor(color);
    _block.setPosition({position.x + size.x/2 , position.y + size.y/2 });
    _block.setOrigin(_block.getSize().x/2,_block.getSize().y/2);
}

Vector2f Block::getPosition() {return _block.getPosition();}
Vector2f Block::getSize() {return _block.getSize();}

bool Block::WasClicked(RenderWindow &window)
{
    if (_block.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))) && !_wasClicked)
    {
        if (Mouse::isButtonPressed(Mouse::Button::Left))
        {
            _wasClicked = true;
            return true;
        }
    }
    return false;
}

void Block::setWasClicked(bool click){
    _wasClicked = click;
}
void Block::draw(RenderTarget &target, RenderStates state) const
{
    target.draw(_block);
}