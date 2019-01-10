#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

using namespace sf;

class Player : public Drawable
{
private:
  Texture _texture;
  std::list<Sprite> _sprite;
  int **_placedCrosses;
  bool diagonal(Vector2i position);
  int _numberinrow; 

public:
  Player(std::string texture,int numberinrow);
  ~Player();
  std::list<int> setSpriteSizeAndPosition(Vector2f size, Vector2f postion, Vector2u windowSize);
  void draw(RenderTarget &targer, RenderStates state) const override;
  bool win();
};