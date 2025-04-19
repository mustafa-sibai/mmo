#pragma once
#include "Core/API.h"
#include "Core/Scene/Scene.h"
#include <vector>

class CORE_API SceneManager
{
private:
	std::vector<Scene*> m_scenes;
	int m_currentSceneIndex;

public:
	SceneManager();
	~SceneManager();

	void AddScene(Scene* scene);
	void RemoveScene(int sceneIndex);
	void LoadScene(int sceneIndex);

	void Update();
	void Render();

	inline const Scene* GetCurrentScene() const { return m_scenes[m_currentSceneIndex]; }
};