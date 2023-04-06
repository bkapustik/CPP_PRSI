#include "Menu.h"

Menu::Menu(float width, float height, unique_ptr<Texture> startTexture, unique_ptr<Texture> restartTexture)
{
	this->gameState = initial;


	const string startImage = "start.jpg";
	auto pathParts = vector<string>{ "Textures", "Menu", startImage };
	string path = ".";
	for (auto i = 0; i < pathParts.size(); ++i)
	{
		path += '/' + pathParts[i];
	}
	unique_ptr<Texture> texture = make_unique<Texture>();
	if (!texture->loadFromFile(path))
	{
		cout << "shit";
	}
	startButton = Sprite(*texture);

	std::cout << startButton.getPosition().x << "," << startButton.getPosition().y << std::endl;
	std::cout << startButton.getGlobalBounds().width << "x" << startButton.getGlobalBounds().height << std::endl;
	std::cout << startButton.getColor().a << std::endl;
}