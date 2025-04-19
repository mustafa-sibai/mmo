#pragma once
#include "Core/Scene/Scene.h"
#include "Core/Networking/Server.h"
#include "Core/Networking/Client.h"

class NetworkScene : public Scene
{
private:
	Server server;
	Client client;

public:
	NetworkScene() = default;
	virtual ~NetworkScene() override = default;

	void Initialize() override;
	void Load() override;
	void PostInitialize() override;
	void Update() override;
	void Render() override;
};