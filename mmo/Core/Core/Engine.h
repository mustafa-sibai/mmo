#pragma once
#include "Core/API.h"
#include "Core/Window.h"
#include "Core/Scene/SceneManager.h"
#include "Core/Input/Keyboard.h"
#include "Core/Input/Mouse.h"

class CORE_API Engine
{
private:
	Window m_window;
	SceneManager m_sceneManager;
	Keyboard m_keyboard;
	Mouse m_mouse;

	static Engine instance;

public:
	static Engine* GetInstance();

private:
	Engine();
	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine& operator=(const Engine&) = delete;

public:
	~Engine() = default;

	void Run();

	inline Window& GetWindow() { return m_window; }
	inline SceneManager& GetSceneManager() { return m_sceneManager; }
	inline Keyboard& GetKeyboard() { return m_keyboard; }
	inline Mouse& GetMouse() { return m_mouse; }
};