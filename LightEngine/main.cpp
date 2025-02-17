
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "SampleScene.h"
#include "Garden.h"

#include <cstdlib>
#include <crtdbg.h>

void CreatSampleScene(GameManager* pInstance);
void CreatGardenScene(GameManager* pInstance);

int main() 
{
    GameManager* pInstance = GameManager::Get();
	
	//CreatSampleScene(pInstance);
	CreatGardenScene(pInstance);

	return 0;
}

void CreatSampleScene(GameManager* pInstance)
{
	pInstance->CreateWindow(1920, 1080, "Agare.io");
	pInstance->LaunchScene<SampleScene>();
}

void CreatGardenScene(GameManager* pInstance)
{
	pInstance->CreateWindow(1280, 720, "Plant Vs Zombie");
	pInstance->LaunchScene<Garden>();
}