#include "NetworkScene.h"

void NetworkScene::Initialize()
{
	server.Initialize("3000");
	client.Initialize();
	client.Connect("127.0.0.1", "3000");
}

void NetworkScene::Load()
{
}

void NetworkScene::PostInitialize()
{
}

void NetworkScene::Update()
{
}

void NetworkScene::Render()
{
}