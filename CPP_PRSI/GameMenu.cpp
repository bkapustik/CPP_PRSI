#include "GameMenu.h"

Menu::Menu(float width, float height, unique_ptr<Texture> startTexture, unique_ptr<Texture> restartTexture)
{
	this->startTexture = move(startTexture);
	this->restartTexture = move(restartTexture);
	this->menuButton = Sprite(*this->startTexture);
	this->menuButton.setPosition((width - this->startTexture->getSize().x) / 2, (height - this->startTexture->getSize().y) / 2);
}

bool Menu::isSpriteClicked()
{
	if (Mouse::getPosition().x > menuButton.getPosition().x
		&& Mouse::getPosition().x < menuButton.getPosition().x + this->menuButton.getTexture()->getSize().x
		&& Mouse::getPosition().y > menuButton.getPosition().y
		&& Mouse::getPosition().y < menuButton.getPosition().y + this->menuButton.getTexture()->getSize().y
		&& Mouse::isButtonPressed(Mouse::Left))
	{
		return true;
	}
	else
	{
		return false;
	}
}