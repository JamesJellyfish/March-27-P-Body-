#pragma once
#include "Box2D/Box2D.h"
#include "entt/entity/registry.hpp"

class ContactListener : public b2ContactListener
{
public:
	ContactListener();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	//getters and setters
	bool GetJump();
	void SetJump(bool jump);
	bool GetGrounded();
	void SetGrounded(bool grounded);

private:
	bool m_jump = true;
	bool isGrounded = false;
};