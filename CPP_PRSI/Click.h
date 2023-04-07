#pragma once

#include "SFML/Graphics.hpp"
#include "memory"

using namespace sf;
using namespace std;

class Click
{
public:
	static bool isClicked(shared_ptr<Sprite> sprite);
	static bool isClicked(Sprite& sprite);
};

