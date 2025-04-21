#include "Engine.h"
#include "Core/Debug.h"

Engine Engine::instance;

Engine* Engine::GetInstance()
{
	return &instance;
}

Engine::Engine() :
	m_mouse(m_window)
{
}

void Engine::Run()
{
	m_window.Create(L"Engine", 1280, 720);
	m_sceneManager.LoadScene(0);

	while (m_window.IsOpen())
	{
		m_window.Update();
		m_mouse.Update();
		m_keyboard.Update();
		m_sceneManager.Update();
		m_sceneManager.Render();
	}
}