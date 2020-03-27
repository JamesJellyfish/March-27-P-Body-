#pragma once

class Ground
{
public:
	Ground();
	Ground(float health);

	float GetHealth() const;
	void SetHealth(float health);

private:
	float m_health = 1.f;
};