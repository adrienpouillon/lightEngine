#pragma once

class GameManager;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#define WHITE 0
#define YELLOW WHITE + 1
#define RED YELLOW + 1
#define GREEN RED + 1
#define CYAN GREEN + 1
#define BLUE CYAN + 1
#define MAGENTA BLUE + 1
#define BLACK MAGENTA + 1 // 7


class Scene
{
private:
	GameManager* mpGameManager;

private:
	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	
protected:
	Scene() = default;

	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;

public:
	template<typename T>
	T* CreateEntity(float radius, const sf::Color& color);

	float GetDeltaTime() const;

	int GenerateRandomNumber(int min, int max);

	sf::Color ChooseColor(int index);

	int GetWindowWidth() const;
	int GetWindowHeight() const;

	friend GameManager;
};

#include "Scene.inl"