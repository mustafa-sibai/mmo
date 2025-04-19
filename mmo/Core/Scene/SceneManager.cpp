#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager()
	: m_currentSceneIndex(0)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::AddScene(Scene* scene)
{
	m_scenes.emplace_back(scene);
}

void SceneManager::RemoveScene(int sceneIndex)
{
	if (sceneIndex < 0 || sceneIndex >= static_cast<int>(m_scenes.size()))
	{
		std::cerr << "Scene index out of range: " << sceneIndex << std::endl;
		return;
	}

	delete m_scenes[sceneIndex];
	m_scenes.erase(m_scenes.begin() + sceneIndex);
}

void SceneManager::LoadScene(int sceneIndex)
{
	if (sceneIndex < 0 || sceneIndex >= static_cast<int>(m_scenes.size()))
	{
		std::cerr << "Scene index out of range: " << sceneIndex << std::endl;
		return;
	}

	m_currentSceneIndex = sceneIndex;

	m_scenes[m_currentSceneIndex]->Initialize();
	m_scenes[m_currentSceneIndex]->Load();
	m_scenes[m_currentSceneIndex]->PostInitialize();
}

void SceneManager::Update()
{
	m_scenes[m_currentSceneIndex]->Update();
}

void SceneManager::Render()
{
	m_scenes[m_currentSceneIndex]->Render();
}