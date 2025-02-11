#include "Scene.h"

#include "GameManager.h"

int Scene::GetWindowWidth() const
{
	return mpGameManager->mWindowWidth;
}

int Scene::GetWindowHeight() const
{
	return mpGameManager->mWindowHeight;
}

float Scene::GetDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}

int Scene::GenerateRandomNumber(int min, int max)
{
	int range = max - min + 1;
	int value = rand() % range + min;
	return value;
}

sf::Color Scene::ChooseColor(int index)
{
	switch (index)
	{
	case WHITE:
		return sf::Color::White;
		break;
	case YELLOW:
		return sf::Color::Yellow;
		break;
	case RED:
		return sf::Color::Red;
		break;
	case GREEN:
		return sf::Color::Green;
		break;
	case CYAN:
		return sf::Color::Cyan;
		break;
	case BLUE:
		return sf::Color::Blue;
		break;
	case MAGENTA:
		return sf::Color::Magenta;
		break;
	case BLACK:
		return sf::Color::Black;
		break;
	}
	return sf::Color::White;
}
