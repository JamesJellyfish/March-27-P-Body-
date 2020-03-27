#pragma once

class MainCharacter
{
public:

	MainCharacter();
	MainCharacter(float health);

	float GetHealth() const;
	void SetHealth(float health);

private:
	float m_health = 1.f;
};