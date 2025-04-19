#pragma once
#include "Core/API.h"
#include "Core/Window.h"
#include "Core/Scene/SceneManager.h"

class CORE_API Engine
{
private:
	Window m_window;
	SceneManager m_sceneManager;

	static Engine instance;

public:
	static Engine* GetInstance();

private:
	// Private constructor to prevent direct instantiation
	Engine() = default;

	// Delete copy constructor and assignment operator
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

public:
	~Engine() = default;

	void Run();

	inline Window& GetWindow() { return m_window; }
	inline SceneManager& GetSceneManager() { return m_sceneManager; }
};