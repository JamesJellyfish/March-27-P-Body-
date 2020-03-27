#pragma once

#include "Scene.h"

class Menu : public Scene
{
public:
	Menu(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

};

struct MenuButton
{
	int buttonID;

};
