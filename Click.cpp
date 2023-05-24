#include "Click.h"

bool Click::isClicked(shared_ptr<Sprite> sprite)
{
	if (Mouse::getPosition().x > sprite->getPosition().x
		&& Mouse::getPosition().x < sprite->getPosition().x + sprite->getTexture()->getSize().x
		&& Mouse::getPosition().y > sprite->getPosition().y
		&& Mouse::getPosition().y < sprite->getPosition().y + sprite->getTexture()->getSize().y
		&& Mouse::isButtonPressed(Mouse::Left))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Click::isClicked(Sprite& sprite)
{
	if (Mouse::getPosition().x > sprite.getPosition().x
		&& Mouse::getPosition().x < sprite.getPosition().x + sprite.getTexture()->getSize().x
		&& Mouse::getPosition().y > sprite.getPosition().y
		&& Mouse::getPosition().y < sprite.getPosition().y + sprite.getTexture()->getSize().y
		&& Mouse::isButtonPressed(Mouse::Left))
	{
		return true;
	}
	else
	{
		return false;
	}
}