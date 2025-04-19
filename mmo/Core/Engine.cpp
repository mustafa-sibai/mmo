#include "Engine.h"

Engine Engine::instance;

Engine* Engine::GetInstance()
{
	return &instance;
}

void Engine::Run()
{
	m_window.Create(L"Engine", 1280, 720);
	m_sceneManager.LoadScene(0);

	while (m_window.IsOpen())
	{
		m_window.Update();
		m_sceneManager.Update();
		m_sceneManager.Render();
	}
}