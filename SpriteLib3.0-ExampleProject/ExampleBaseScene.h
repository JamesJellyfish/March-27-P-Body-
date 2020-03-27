#pragma once

#include "Scene.h"
#include "MyContactListener.h"

class ExampleBaseScene : public Scene
{
public:
	ExampleBaseScene(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	//Effects & camera stuff
	void RainbowBackground();
	void AdjustScrollOffset();

	//Controls
	void Aiming(vec2 mousePosition);

	//Input overrides
	void KeyboardHold() override;

	void MouseMotion(SDL_MouseMotionEvent evnt) override;
	void MouseClick(SDL_MouseButtonEvent evnt) override;

	bool getFace();
	void setFace(bool);
protected:
	//Mouse position in world
	vec2 m_mouseGL = vec2(0.f, 0.f);

	//Time needed for colors to lerp to and fro
	float m_repeatTime = 5.f;
	float m_lerpVal = 0.f;

	//Colors to be lerped between
	vec4 m_clearColor1 = vec4(0.153f, 0.992f, 0.961f, 1.f);
	vec4 m_clearColor2 = vec4(0.969f, 0.396f, 0.722f, 1.f);

	bool m_isInit = false;

	bool m_face;
};
