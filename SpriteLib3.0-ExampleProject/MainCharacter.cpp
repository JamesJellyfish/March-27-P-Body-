#include "MainCharacter.h"

MainCharacter::MainCharacter()
{
}

MainCharacter::MainCharacter(float health)
{
	SetHealth(health);
}

float MainCharacter::GetHealth() const
{
	return m_health;
}

void MainCharacter::SetHealth(float health)
{
	m_health = health;
}
