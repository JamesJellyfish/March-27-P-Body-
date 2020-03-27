#include "Ground.h"

Ground::Ground()
{
}

Ground::Ground(float health)
{
	SetHealth(health);
}

float Ground::GetHealth() const
{
	return m_health;
}

void Ground::SetHealth(float health)
{
	m_health = health;
}
