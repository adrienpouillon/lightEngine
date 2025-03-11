#include "Saw.h"
#include "Utils.h"
#include "Garden.h"

void Saw::OnInitialize()
{
	SetTag(TYPEPLANTPEAT);
	SetLife(LIFESAW);
}

void Saw::OnCollision(Entity* other)
{
	if (other->GetTag() <= TYPEZOMBIE)
	{
		if(Alive* otherAlive = Garden::GetTypeConvert<Alive*>(other))
		{
			otherAlive->LifeLessLess();
			Alive::LifeLessLess();
		}
	}
}

void Saw::OnUpdate()
{
	Alive::OnUpdate();

	if (GetScene<Garden>()->GetIaPlant())
	{
		IaAction();
	}
}

void Saw::IaAction()
{
	if (!mTarget.isSet)
	{
		bool entityFar = !EUtils::IsAreaEmpty(this, GetRadius() * 5);
		bool entityFarUp = !EUtils::IsAreaEmptyUp(this, GetRadius() * 5);
		bool entityFarDown = !EUtils::IsAreaEmptyDown(this, GetRadius() * 5);

		bool entityMiddle = !EUtils::IsAreaEmpty(this, GetRadius() * 20);
		bool entityMiddleUp = !EUtils::IsAreaEmptyUp(this, GetRadius() * 20);
		bool entityMiddleDown = !EUtils::IsAreaEmptyDown(this, GetRadius() * 20);

		if (entityFar)
		{
			/*il y a un enemie proche sur notre ligne*/
			if (entityFarUp)
			{
				/*il y a un enemie proche sur notre ligne et sur la ligne du dessus*/
				if (entityFarDown)
				{
					/*il y a un enemie proche sur notre ligne et sur la ligne du dessus et la ligne du dessous*/
				}
				else
				{
					/*il y a un enemie proche sur notre ligne et sur la ligne du dessus*/
				}
			}
			else
			{
				/*il y a un enemie proche sur notre ligne*/
				if (entityFarDown)
				{
					/*il y a un enemie proche sur notre ligne et la ligne du dessous*/
				}
				else
				{
					/*il y a un enemie proche sur notre ligne*/
				}
			}
		}
		else
		{
			/*il y a pas d'enemie proche sur notre ligne*/
			if (entityFarUp)
			{
				/*il y a un enemie proche sur la ligne du dessus*/
				if (entityFarDown)
				{
					/*il y a un enemie proche sur la ligne du dessus et du dessous*/
					sf::Vector2f pos = GetPosition();
					if (Garden::GenerateRandomNumber(0, 1) == 0){pos.y += HEIGHTLINE;}
					else{pos.y -= HEIGHTLINE;}
					GoToPosition(pos.x, pos.y - HEIGHTLINE);
				}
				else
				{
					/*il y a un enemie proche sur la ligne du dessus*/
					sf::Vector2f pos = GetPosition();
					GoToPosition(pos.x, pos.y - HEIGHTLINE);
				}
			}
			else
			{
				/*il y a pas d'enemie proche sur la ligne du dessus*/
				if (entityFarDown)
				{
					/*il y a un enemie proche sur la ligne du dessous*/
					sf::Vector2f pos = GetPosition();
					GoToPosition(pos.x, pos.y + HEIGHTLINE);
				}
				else
				{
					/*il y a pas d'enemie proche*/
					if (entityMiddle)
					{
						/*il y a un enemie loin sur notre ligne*/
						if (entityMiddleUp)
						{
							/*il y a un enemie loin sur notre ligne et la ligne du dessus*/
							if (entityMiddleDown)
							{
								/*il y a un enemie loin sur notre ligne et la ligne du dessus et la ligne du dessous*/

							}
							else
							{
								/*il y a un enemie loin sur notre ligne et la ligne du dessus*/

							}
						}
						else
						{
							/*il y a un enemie loin sur notre ligne*/
							if (entityMiddleDown)
							{
								/*il y a un enemie loin sur notre ligne et la ligne du dessous*/

							}
							else
							{
								/*il y a un enemie loin sur notre ligne*/

							}
						}
					}
					else
					{
						/*il y a pas d'enemie loin*/
						if (entityMiddleUp)
						{
							/*il y a un enemie loin sur la ligne du dessus*/
							if (entityMiddleDown)
							{
								/*il y a un enemie loin sur la ligne du dessus et du dessous*/
								sf::Vector2f pos = GetPosition();
								if (Garden::GenerateRandomNumber(0, 1) == 0) { pos.y += HEIGHTLINE; }
								else { pos.y -= HEIGHTLINE; }
								GoToPosition(pos.x, pos.y - HEIGHTLINE);
							}
							else
							{
								/*il y a un enemie loin sur la ligne du dessus*/
								sf::Vector2f pos = GetPosition();
								GoToPosition(pos.x, pos.y - HEIGHTLINE);
							}
						}
						else
						{
							/*il y a pas d'enemie loin*/
							if (entityMiddleDown)
							{
								/*il y a un enemie loin sur la ligne du dessous*/
								sf::Vector2f pos = GetPosition();
								GoToPosition(pos.x, pos.y + HEIGHTLINE);
							}
							else
							{
								/*il y a pas d'enemie loin*/
								sf::Vector2f pos = GetPosition();
								GoToPosition(pos.x, LINETWO);
							}
						}
					}
				}
			}
		}
	}
}

void Saw::ActionDead()
{
	Garden* garden = GetScene<Garden>();
	garden->IncreasePlantEated();
	garden->IncreaseZombieCoin(5000);
	Entity::Destroy();
}

void Saw::SetLife(int life)
{
	Alive::SetLife(life);
}

void Saw::GoToPosition(int x, int line)
{
	Entity::GoToPosition(x, line, SPEEDSAW);
}

void Saw::GoToPosition(sf::Vector2f xLine)
{
	Entity::GoToPosition(xLine.x, xLine.y, SPEEDSAW);
}