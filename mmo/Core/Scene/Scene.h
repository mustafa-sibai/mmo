#pragma once
#include "Core/API.h"

class CORE_API Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Initialize() = 0;
	virtual void Load() = 0;
	virtual void PostInitialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};