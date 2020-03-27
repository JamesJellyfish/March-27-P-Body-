#include "MyContactListener.h"
#include "Game.h"
#include "ECS.h"
#include "Box2D/Box2D.h"
#include "entt/entity/registry.hpp"
#include <iostream>

ContactListener::ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
	//Identifies the first body
	auto fixtureA = contact->GetFixtureA();
	auto bodyA = fixtureA->GetBody();
	unsigned int entityA = (unsigned int)bodyA->GetUserData();
	auto identifierA = ECS::GetComponent<EntityIdentifier>(entityA).GetIdentifier();

	//Identifies the second body
	auto fixtureB = contact->GetFixtureB();
	auto bodyB = fixtureB->GetBody();
	unsigned int entityB = (unsigned int)bodyB->GetUserData();
	auto identifierB = ECS::GetComponent<EntityIdentifier>(entityB).GetIdentifier();

	//Checks to make sure the bodies are valid
	if (fixtureA == NULL || fixtureB == NULL)
		return;
	if (fixtureA->GetUserData() == NULL || fixtureB->GetUserData() == NULL)
		return;

	//when they are touching the ground
	if (identifierA & EntityIdentifier::MainCharacterBit())
	{
		if (identifierB & EntityIdentifier::GroundBit())
		{
			m_jump = true;
			isGrounded = true;
		}
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	//Identifies the first body
	auto fixtureA = contact->GetFixtureA();
	auto bodyA = fixtureA->GetBody();
	unsigned int entityA = (unsigned int)bodyA->GetUserData();
	auto identifierA = ECS::GetComponent<EntityIdentifier>(entityA).GetIdentifier();

	//Identifies the second body
	auto fixtureB = contact->GetFixtureB();
	auto bodyB = fixtureB->GetBody();
	unsigned int entityB = (unsigned int)bodyB->GetUserData();
	auto identifierB = ECS::GetComponent<EntityIdentifier>(entityB).GetIdentifier();

	//Checks to make sure the bodies are valid
	if (fixtureA == NULL || fixtureB == NULL)
		return;
	if (fixtureA->GetUserData() == NULL || fixtureB->GetUserData() == NULL)
		return;

	//when they leave ground
	if (identifierA & EntityIdentifier::MainCharacterBit())
	{
		if (identifierB & EntityIdentifier::GroundBit())
		{
			m_jump = false;
			isGrounded = false;
		}
	}
}

bool ContactListener::GetJump()
{
	return m_jump;
}

void ContactListener::SetJump(bool jump)
{
	m_jump = jump;
}

bool ContactListener::GetGrounded()
{
	return isGrounded;
}

void ContactListener::SetGrounded(bool grounded)
{
	isGrounded = grounded;
}
