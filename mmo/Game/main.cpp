#include "Core/Engine.h"
#include "Scenes/NetworkScene.h"

int main()
{
	Engine::GetInstance()->GetSceneManager().AddScene(new NetworkScene());
	Engine::GetInstance()->Run();
}