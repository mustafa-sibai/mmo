#include "Core/Engine.h"
#include "Scenes/NetworkScene.h"
#include "Core/Math/Vector2.h"
#include <iostream>

int main()
{
	Vector2f vec1(1.0f, 2.0f);

	std::cout << vec1 << std::endl;

	Engine::GetInstance()->GetSceneManager().AddScene(new NetworkScene());
	Engine::GetInstance()->Run();
}