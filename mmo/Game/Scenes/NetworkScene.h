#pragma once
#include "Core/Scene/Scene.h"
#include "Core/Networking/TCPServer.h"
#include "Core/Networking/TCPClient.h"

class NetworkScene : public Scene
{
private:
	TCPServer server;
	TCPClient client;

public:
	NetworkScene() = default;
	virtual ~NetworkScene() override = default;

	void Initialize() override;
	void Load() override;
	void PostInitialize() override;
	void Update() override;
	void Render() override;
};