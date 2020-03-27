#include "Game.h"
#include "ExampleBaseScene.h"
#include "MyContactListener.h"
#include <random>

ContactListener listener;

Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}
//ExampleBaseScene::ExampleBaseScene(std::string name)
//	: Scene(name)
//{
//	////No gravity, this is top down
//	m_gravity = b2Vec2(0.f, -250.f);
//	m_physicsWorld->SetGravity(m_gravity);
//}
void Game::InitGame()
{
	////No gravity, this is top down
	//m_gravity = b2Vec2(0.f, -250.f);
	//m_physicsWorld->SetGravity(m_gravity);

	//Initializes the backend x y
	//BackEnd::InitBackEnd(719.f, 436.f);
	BackEnd::InitBackEnd(1400.f, 800.f);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//Creates a new HelloWorld scene
	m_scenes.push_back(new ExampleBaseScene("Seasonal Shifters"));
	//m_scenes.push_back(new ExampleBaseScene("Level 2"));
	//m_scenes.push_back(new Scene("Level 3"));
	//Sets active scene reference to our scene
	m_activeScene = m_scenes[0];

	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));

	//*m_activeScene = File::LoadJSON("Hello World.json");

	//Menu Button
	/*if (m_sceneID == 0)
	{
		CreateMenuButton();
		PlaySound(TEXT("OPening_SOng.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	}*/
	//PlaySound(TEXT("Cool_song.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	PlaySound(TEXT("OPening_SOng.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);


	autoScroll = 120;

	//Sets m_register to point to the register in the active scene
	m_register = m_activeScene->GetScene();

	BackEnd::SetWindowName(m_activeScene->GetName());

	PhysicsSystem::Init();

	m_activeScene->GetPhysicsWorld().SetContactListener(&listener);
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with activescene clearColor
		m_window->Clear(m_activeScene->GetClearColor());
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();

		//Flips the windows
		m_window->Flip();

		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}
	}

	return true;
}

void Game::Update()
{
	//Makes the camera focus on this entity
	/*ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));*/

	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(5));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(5));
	
	//When the remainder of time is equal to 0 move the box
	timeStamp = Timer::time;
	if (remainder(timeStamp, 1) == 0) {
		UpdateBox();
	}
	
	StartBox();
	//GameOverScreen();

	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);

	//Update Physics System
	PhysicsSystem::Update(m_register, m_activeScene->GetPhysicsWorld());

	//Updates the active scene
	m_activeScene->Update();
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	//if (m_motion)
		//MouseMotion(BackEnd::GetMotionEvent());

	//if (m_click)
		//MouseClick(BackEnd::GetClickEvent());

	//if (m_wheel)
		//MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	XInputManager::Update();

	//Just calls all the other input functions 
	GamepadInput();

	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

void Game::GamepadInput()
{
	XInputController* tempCon;
	//Gamepad button stroked (pressed)
	for (int i = 0; i < 3; i++)
	{
		if (XInputManager::ControllerConnected(i))
		{
			tempCon = XInputManager::GetController(i);
			tempCon->SetStickDeadZone(0.1f);

			//If the controller is connected, we run the different input types
			GamepadStroke(tempCon);
			GamepadUp(tempCon);
			GamepadDown(tempCon);
			GamepadStick(tempCon);
			GamepadTrigger(tempCon);
		}
	}
}

void Game::GamepadStroke(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadStroke(con);
}

void Game::GamepadUp(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadUp(con);
}

void Game::GamepadDown(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadDown(con);
}

void Game::GamepadStick(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadStick(con);
}

void Game::GamepadTrigger(XInputController * con)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->GamepadTrigger(con);
}

void Game::KeyboardHold()
{
	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

	/*
	if (Input::GetKeyDown(Key::W))
	{
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(++position.y);
	}
	if (Input::GetKeyDown(Key::S))
	{
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionY(--position.y);
	}
	if (Input::GetKeyDown(Key::A))
	{
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(--position.x);
	}
	if (Input::GetKeyDown(Key::D))
	{
		m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPositionX(++position.x);
	}*/

	/*auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();
	b2Vec2 velocity = b2Vec2(0.f, 0.f);
	float inputVal = 15.f;
	if (Input::GetKeyDown(Key::E))
	{
		velocity += b2Vec2(inputVal + 200, 0.f);
	}
	body->SetLinearVelocity(velocity);*/
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.

	if (Input::GetKey(Key::C))
	{
		autoScroll += 5;
		ECS::GetComponent<Transform>(5).SetPositionX(autoScroll);
		
	}
	
	m_activeScene->KeyboardHold();
}

void Game::KeyboardDown()
{
	if (onceEnter == false) {
		if (Input::GetKeyDown(Key::Enter))
		{
			ECS::DestroyEntity(6);
			PlaySound(TEXT("Cool_song.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
			//autoS = true;
			ECS::GetComponent<Transform>(5).SetPositionX(120);
			//ECS::GetComponent<Transform>(5).SetPositionY(0);
			onceEnter == true;
		}
		
	}

	auto body = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).GetBody();

	//jump only on ground
	if (listener.GetJump() || listener.GetGrounded())
	{
		if (Input::GetKeyDown(Key::W))
		{
		float impulse = body->GetMass() * 30;
		body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);
		listener.SetGrounded(false);
		}
	}

	if (Input::GetKeyDown(Key::E))
	{
		float impulse = body->GetMass() * 20;
		body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
	}
	
	if (Input::GetKeyDown(Key::F))
	{
		autoS = false;
		
	}

	if (Input::GetKeyDown(Key::G))
	{
		autoS = true;
		std::cout << ECS::GetComponent<Transform>(5).GetPositionX();

	}

	/*if (Input::GetKeyDown(Key::K))
	{
		ECS::DestroyEntity(2);
		
	}*/

	
	
	//Menu input
	//if (m_sceneID == 0)
	//{
	//	if (Input::GetKeyDown(Key::UpArrow))
	//	{
	//		m_activeMenuButton--;
	//		if (m_activeMenuButton < 0)
	//		{
	//			m_activeMenuButton = 3;
	//		}
	//	}
	//	if (Input::GetKeyDown(Key::DownArrow))
	//	{
	//		m_activeMenuButton++;
	//		if (m_activeMenuButton > 3)
	//		{
	//			m_activeMenuButton = 0;
	//		}
	//	}
	//	//Play button
	//	if (m_activeMenuButton == 0)
	//	{
	//		ECS::GetComponent<Transform>(m_menuList[0].buttonID).SetPosition(vec3(0.f, 0.f, 4.f));
	//		ECS::GetComponent<Transform>(m_menuList[1].buttonID).SetPosition(vec3(0.f, 0.f, 3.f));
	//		ECS::GetComponent<Transform>(m_menuList[2].buttonID).SetPosition(vec3(0.f, 0.f, 2.f));
	//		ECS::GetComponent<Transform>(m_menuList[3].buttonID).SetPosition(vec3(0.f, 0.f, 1.f));
	//	}
	//	//Instruction Button
	//	if (m_activeMenuButton == 1)
	//	{
	//		ECS::GetComponent<Transform>(m_menuList[0].buttonID).SetPosition(vec3(0.f, 0.f, 3.f));
	//		ECS::GetComponent<Transform>(m_menuList[1].buttonID).SetPosition(vec3(0.f, 0.f, 4.f));
	//		ECS::GetComponent<Transform>(m_menuList[2].buttonID).SetPosition(vec3(0.f, 0.f, 2.f));
	//		ECS::GetComponent<Transform>(m_menuList[3].buttonID).SetPosition(vec3(0.f, 0.f, 1.f));
	//	}
	//	//Credit Button
	//	if (m_activeMenuButton == 2)
	//	{
	//		ECS::GetComponent<Transform>(m_menuList[0].buttonID).SetPosition(vec3(0.f, 0.f, 3.f));
	//		ECS::GetComponent<Transform>(m_menuList[1].buttonID).SetPosition(vec3(0.f, 0.f, 2.f));
	//		ECS::GetComponent<Transform>(m_menuList[2].buttonID).SetPosition(vec3(0.f, 0.f, 4.f));
	//		ECS::GetComponent<Transform>(m_menuList[3].buttonID).SetPosition(vec3(0.f, 0.f, 1.f));
	//	}
	//	//Exit Button
	//	if (m_activeMenuButton == 3)
	//	{
	//		ECS::GetComponent<Transform>(m_menuList[0].buttonID).SetPosition(vec3(0.f, 0.f, 3.f));
	//		ECS::GetComponent<Transform>(m_menuList[1].buttonID).SetPosition(vec3(0.f, 0.f, 2.f));
	//		ECS::GetComponent<Transform>(m_menuList[2].buttonID).SetPosition(vec3(0.f, 0.f, 1.f));
	//		ECS::GetComponent<Transform>(m_menuList[3].buttonID).SetPosition(vec3(0.f, 0.f, 4.f));
	//	}
	//	if (Input::GetKeyDown(Key::Enter) && m_activeMenuButton >= 0 && m_activeMenuButton <= 3)
	//	{
	//		//Play Game
	//		if (m_activeMenuButton == 0)
	//		{
	//			m_sceneID = 1;
	//			
	//			m_activeScene = m_scenes[/*m_sceneID*/0];
	//			m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	//			m_register = m_activeScene->GetScene();
	//			menuMusic = false;
	//			isGuideScreen = false;
	//			isCreditScreen = false;
	//			PlaySound(TEXT("Cool_song.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	//		}
	//		//Instruction Screen
	//		if (m_activeMenuButton == 1)
	//		{
	//			ECS::GetComponent<Transform>(m_menuList[4].buttonID).SetPosition(vec3(0.f, 0.f, 10.f));
	//			isGuideScreen = true;
	//			isCreditScreen = false;
	//		}
	//		//Credit Screen
	//		if (m_activeMenuButton == 2)
	//		{
	//			ECS::GetComponent<Transform>(m_menuList[5].buttonID).SetPosition(vec3(0.f, 0.f, 10.f));
	//			isGuideScreen = false;
	//			isCreditScreen = true;
	//		}
	//	}
	//	//Exit Instruction or guide screen
	//	if (Input::GetKeyDown(Key::Escape) && (isGuideScreen | isCreditScreen))
	//	{
	//		ECS::GetComponent<Transform>(m_menuList[4].buttonID).SetPosition(vec3(0.f, 0.f, 1.1f));
	//		ECS::GetComponent<Transform>(m_menuList[5].buttonID).SetPosition(vec3(0.f, 0.f, 1.2f));
	//	}
	//}

	


	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->KeyboardDown();
}

void Game::KeyboardUp()
{
	

	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
	if (Input::GetKeyUp(Key::P))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}

	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->KeyboardUp();
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->MouseMotion(evnt);

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->MouseClick(evnt);

	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	//Active scene now captures this input and can use it
	//Look at base Scene class for more info.
	m_activeScene->MouseWheel(evnt);

	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}

void Game::CreateMenuButton()
{
{
		MenuButton ButtonID;

		//Creates Main Menu
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string MenuScreen = "Play.png"; //400, 200
		ECS::GetComponent<Sprite>(entity).LoadSprite(MenuScreen, 250, 150);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 6.f));
		//Setup up the Identifier
		unsigned int bitHolder = 0x0;

		ECS::SetUpIdentifier(entity, bitHolder, "Play Button");

		//Record menu ID
		ButtonID.buttonID = entity;

		m_menuList.push_back(ButtonID);
	}
	{
		MenuButton ButtonID;

		//Creates Instruction Button
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string MenuScreen = "Instructions.png"; //380, 200
		ECS::GetComponent<Sprite>(entity).LoadSprite(MenuScreen, 250, 150);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 5.f));
		//Setup up the Identifier
		unsigned int bitHolder = 0x0;

		ECS::SetUpIdentifier(entity, bitHolder, "Instruction Button");

		//Record menu ID
		ButtonID.buttonID = entity;

		m_menuList.push_back(ButtonID);
	}
	{
		MenuButton ButtonID;

		//Creates Credit Button
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string MenuScreen = "Credit.png"; //400, 200
		ECS::GetComponent<Sprite>(entity).LoadSprite(MenuScreen, 250, 150);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 4.f));
		//Setup up the Identifier
		unsigned int bitHolder = 0x0;

		ECS::SetUpIdentifier(entity, bitHolder, "Credit Button");

		//Record menu ID
		ButtonID.buttonID = entity;

		m_menuList.push_back(ButtonID);
	}
	{
		MenuButton ButtonID;

		//Creates Exit Button
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string MenuScreen = "Exit.png"; //400, 200
		ECS::GetComponent<Sprite>(entity).LoadSprite(MenuScreen, 250, 150);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 3.f));
		//Setup up the Identifier
		unsigned int bitHolder = 0x0;

		ECS::SetUpIdentifier(entity, bitHolder, "Exit Button");

		//Record menu ID
		ButtonID.buttonID = entity;

		m_menuList.push_back(ButtonID);
	}
	{
		MenuButton ButtonID;

		//Creates Instruction Screen
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string MenuScreen = "guide.png"; //400, 200
		ECS::GetComponent<Sprite>(entity).LoadSprite(MenuScreen, 250, 150);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 2.f));
		//Setup up the Identifier
		unsigned int bitHolder = 0x0;

		ECS::SetUpIdentifier(entity, bitHolder, "Instruction Screen");

		//Record menu ID
		ButtonID.buttonID = entity;

		m_menuList.push_back(ButtonID);
	}
	{
		MenuButton ButtonID;

		//Creates Instruction Screen
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string MenuScreen = "creditScreen.png"; //400, 200
		ECS::GetComponent<Sprite>(entity).LoadSprite(MenuScreen, 250, 150);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 1.f));
		//Setup up the Identifier
		unsigned int bitHolder = 0x0;

		ECS::SetUpIdentifier(entity, bitHolder, "Credit Screen");

		//Record menu ID
		ButtonID.buttonID = entity;

		m_menuList.push_back(ButtonID);
	}
}

void Game::UpdateBox()
{
	if (autoS == true) 
	{
		autoScroll += 0.10;
		ECS::GetComponent<Transform>(5).SetPositionX(autoScroll);

		//ECS::GetComponent<Transform>(1).GetPositionX();
		//ECS::GetComponent<Transform>(5).SetPositionY(1);
	}
}

void Game::StartBox()
{
	float player;

	player = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX();
	
	if (player >= 90 && player <=120) {
		autoS = true;
		
	}

}

void Game::GameOverScreen()
{
	gameOver = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPositionX();
	playerOver = ECS::GetComponent<Transform>(5).GetPositionX();

	if ((playerOver - gameOver) >= 270.f) 
	{
		autoS = false;
		ECS::GetComponent<Transform>(5).SetPositionX(0);
		ECS::GetComponent<Transform>(5).SetPositionY(0);
		createGameOverScreen();		
	};

}

void Game::createGameOverScreen()
{
	//Creates entity Game Over Screen
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);

	//Sets up components
	std::string fileName = "GameOver.jpg";//20 20
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, (1024 / 4) + 7, 608 / 4);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(122.f, 0.f, 10));

	//Sets up the Identifier
	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	ECS::SetUpIdentifier(entity, bitHolder, "GameOver");

}

