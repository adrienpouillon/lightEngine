#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#define TYPENO 0
#define TYPEPLANT TYPENO + 1
#define TYPEZOMBIE TYPEPLANT + 1

#define NOSPEED sf::Vector2f(0,0)

namespace sf 
{
	class Shape;
    class Color;
}

class Scene;

class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:
    sf::CircleShape mShape;
    sf::Vector2f mDirection;
	Target mTarget;
    float mSpeed = 0.f;
    bool mToDestroy = false;
    int mTag = -1;
	bool mRigidBody = false;

public:
	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	void SetDirection(float x, float y, float speed = -1.f);
	sf::Vector2f GetDirection();
	float GetSpeed();
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetTag(int tag) { mTag = tag; }
	float GetRadius() const { return mShape.getRadius(); }
	void SetRigidBody(bool isRigitBody) { mRigidBody = isRigitBody; }
	bool IsRigidBody() const { return mRigidBody; }

    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::Shape* GetShape() { return &mShape; }

	bool IsTag(int tag) const { return mTag == tag; }
	//if entity collide with other
	//this fonction call OnCollision with entity* other
    bool IsColliding(Entity* other) const;
	//if entity collide with point
	bool IsInside(float x, float y) const;
	//if entity out of window more extentionLeftWindow or extentionRightWindow
	//this fonction call OnCollision with entity* other = nullptr
	void OutWindow(sf::Vector2f extentionLeftWindow, sf::Vector2f extentionRightWindow);
	void OutWindow(float extentionLeftWindow, float extentionRightWindow);

	//if entity is destroy
    void Destroy();
	bool ToDestroy() const { return mToDestroy; }
	
	//for get id scene
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

	//for creat entity
    template<typename T>
    T* CreateEntity(float radius, const sf::Color& color);

	virtual int GetType();

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	
private:
    void Update();
	void Initialize(float radius, const sf::Color& color);
	void Repulse(Entity* other);

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"