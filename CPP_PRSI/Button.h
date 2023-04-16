#pragma once

#include <memory>
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;

class Button
{
private:
	unique_ptr<Texture> texture;
public:
	shared_ptr<Sprite> sprite;
	shared_ptr<Text> text;
	Button(unique_ptr<Texture> texture, shared_ptr<Text> text);
	Button() {}
	void setPosition(float width, float height);
	void setSize(float width, float height);
};

