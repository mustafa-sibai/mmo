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
}

void NetworkScene::Render()
{
}