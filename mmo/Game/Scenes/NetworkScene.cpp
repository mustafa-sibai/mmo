#include "NetworkScene.h"
#include "Core/Engine.h"
#include <iostream>
#include <Core/Debug.h>

void NetworkScene::Initialize()
{
	server.Initialize("3000");
	client.Initialize();
	client.Connect("127.0.0.1", "3000");
}

void NetworkScene::Load()
{
	Debug::LogInfo("This is an info message");
	Debug::LogWarning("This is an warning message");
	Debug::LogError("This is an error message");
}

void NetworkScene::PostInitialize()
{
}

void NetworkScene::Update()
{
	if (Engine::GetInstance()->GetKeyboard().IsKeyPressed(Keyboard::KeyCode::Space))
	{
		std::cout << "Space key pressed!" << std::endl;
	}

	if (Engine::GetInstance()->GetKeyboard().IsKeyHeld(Keyboard::KeyCode::A))
	{
		std::cout << "A key pressed!" << std::endl;
	}

	if (Engine::GetInstance()->GetKeyboard().IsKeyReleased(Keyboard::KeyCode::A))
	{
		std::cout << "A key released!" << std::endl;
	}

	if (Engine::GetInstance()->GetMouse().IsButtonPressed(Mouse::ButtonCode::LeftButton))
	{
		std::cout << "Left mouse button pressed!" << std::endl;
	}

	if (Engine::GetInstance()->GetMouse().IsButtonHeld(Mouse::ButtonCode::LeftButton))
	{
		std::cout << "Left mouse button held!" << std::endl;
	}

	if (Engine::GetInstance()->GetMouse().IsButtonReleased(Mouse::ButtonCode::LeftButton))
	{
		std::cout << "Left mouse button released!" << std::endl;
	}

	if (Engine::GetInstance()->GetMouse().IsButtonPressed(Mouse::ButtonCode::RightButton))
	{
		std::cout << "Right mouse button pressed!" << std::endl;
	}

	//std::cout << "Mouse Position: " << Engine::GetInstance()->GetMouse().GetPosition(true) << std::endl;
}

void NetworkScene::Render()
{
}