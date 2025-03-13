#include "Mouse.h"
#include "Garden.h"

void Mouse::OnInitialize()
{
	SetTag(TYPENO);
}

void Mouse::OnUpdate()
{
	Garden* garden = GetScene<Garden>();
	sf::Vector2f pos = garden->GetMousePosition();
	SetPosition(pos.x,pos.y);

	int modeCreator = garden->GetModeCreator();
	if (modeCreator == MODEPLANT)
	{
		mShape.setFillColor(sf::Color::Green);
	}
	else if (modeCreator == MODEZOMBIE)
	{
		mShape.setFillColor(sf::Color::Red);
	}
}

int Mouse::GetType()
{
	return TYPENO;
}
