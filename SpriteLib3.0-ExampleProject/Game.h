#ifndef __GAME_H__
#define __GAME_H__

#include "BackEnd.h"
#include "ExampleBaseScene.h"
#include "Menu.h"
#include <Windows.h>
#include <mmsystem.h>
#include <cmath> 

//Our main class for running our game
class Game
{
public:
	//Empty constructor
	Game() { };
	//Deconstructor for game
	//*Unloads window
	~Game();

	//Initiaiizes game
	//*Seeds random
	//*Initializes SDL
	//*Creates Window
	//*Initializes GLEW
	//*Create Main Camera Entity
	//*Creates all other entities and adds them to register
	void InitGame();

	//Runs the game
	//*While window is open
	//*Clear window
	//*Update 
	//*Draw
	//*Poll events
	//*Flip window
	//*Accept input
	bool Run();
	
	//Updates the game
	//*Update timer
	//*Update the rendering system
	//*Update the animation system
	void Update();

	//Runs the GUI
	//*Uses ImGUI for this
	void GUI();

	//Check events
	//*Checks the results of the events that have been polled
	void CheckEvents();

	/*Input Functions*/
	void AcceptInput();
	void GamepadInput();

	void GamepadStroke(XInputController* con);
	void GamepadUp(XInputController* con);
	void GamepadDown(XInputController* con);
	void GamepadStick(XInputController* con);
	void GamepadTrigger(XInputController* con);
	void KeyboardHold();
	void KeyboardDown();
	void KeyboardUp();

	//Mouse input
	void MouseMotion(SDL_MouseMotionEvent evnt);
	void MouseClick(SDL_MouseButtonEvent evnt);
	void MouseWheel(SDL_MouseWheelEvent evnt);

	void CreateMenuButton();
	
	void UpdateBox();
	void StartBox();
	void GameOverScreen();

	void createGameOverScreen();

	bool menuMusic = true;
private:
	//The window
	Window *m_window = nullptr;
	
	//The main register for our ECS
	entt::registry* m_register = nullptr;

	//Scenes
	Scene* m_activeScene = nullptr;
	std::vector<Scene*> m_scenes;
	
	int m_sceneID = 0;

	//Imgui stuff
	bool m_guiActive = false;

	//Hooks for events
	bool m_close = false;
	bool m_motion = false;
	bool m_click = false;
	bool m_wheel = false;

	XInputManager input;

	//Menu List
	int m_activeMenuButton = 0;
	std::vector<MenuButton> m_menuList;

	bool isCreditScreen = false;
	bool isGuideScreen = false;

	double autoScroll;
	bool autoS = false;
	int timeStamp;

	float gameOver;
	float playerOver;

	bool onceEnter = false;
	
};



#endif // !__GAME_H__

