#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;

class Block : public Drawable
{
private:
    RectangleShape _block;
    bool _wasClicked = false;
public:
    Block(Vector2f size, Vector2f position);
    bool WasClicked(RenderWindow &window);
    Vector2f getPosition();
    Vector2f getSize();
    void setWasClicked(bool click);
    void draw(RenderTarget &target, RenderStates state) const override ;
};

