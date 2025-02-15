#pragma once

#include "Module.h"

struct ModulesConfig
{
	bool aimAssist, clickAssist;
};

class AimBotModule : public Module
{
	AimConfig config;
	uintptr_t currentTargetPtr;

	bool UpdateConfigs()
	{
		config.aimCircle.p = ClientCenterPosition;

		// uses home to toggle visibility of aim circle (fov)
		if (GetAsyncKeyState(VK_HOME) & 1)
			config.showAimCircle = !config.showAimCircle;

		// uses up to increment smoothness
		if (GetAsyncKeyState(VK_UP) & 1)
			config.smoothness += 0.05F;

		// uses down to decrement smoothness
		if (GetAsyncKeyState(VK_DOWN) & 1)
			config.smoothness -= 0.05F;

		// VK_XBUTTON1 (Mouse 4) toggles aim lock
		if (GetAsyncKeyState(VK_XBUTTON1) & 1)
			config.isAimActive = !config.isAimActive;

		// VK_XBUTTON2 (Mouse 5) hold for auto shoot on target
		config.isClickActive = GetAsyncKeyState(VK_XBUTTON2) && GetAsyncKeyState(VK_XBUTTON2);

		return config.isActive && config.isReady;
	}

	void UpdateTarget()
	{
		if (!config.isAimActive)
		{
			currentTargetPtr = NULL;
			return;
		}

		Player target;
		uintptr_t ptrFound = NULL;
		float minDistance = NULL;

		for (Player &player : ENEMIES)
		{
			if (!player.IsValidTarget())
				continue;

			if (!InterSects(player.screenBox, config.aimCircle))
				continue;

			if (currentTargetPtr && currentTargetPtr == player.entity)
			{
				ptrFound = player.entity;
				target = player;
				break;
			}

			float distance = player.position.EuclideanDistance(MyLocalPlayer.position);
			if (!minDistance || distance < minDistance)
			{
				minDistance = distance;
				ptrFound = player.entity;
				target = player;
			}
		}

		if (ptrFound)
		{
			currentTargetPtr = ptrFound;
			MyLocalPlayer.SetViewAngles(target.aimAngle, config.smoothness);
		}
	}

	void Execute() override
	{
		if (!UpdateConfigs())
			return;

		UpdateTarget();
		if (MyLocalPlayer.crossIndex >= 0 && config.isClickActive)
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}

	void RenderAimZone()
	{
		if (!config.showAimCircle)
			return;

		DrawCircle(config.aimCircle.p, config.aimCircle.radius, config.aimCircle.color);
		DrawFilledCircle(config.aimCircle.p, config.aimCircle.radius, config.aimCircle.borderColor);
	}

public:
	void Init(Module *rootModule) override
	{
		this->config.isActive = true;
		this->UpdatePointers(rootModule);
		this->config.isReady = true;
	}

	void Render() override
	{
		if (config.isHidden || !config.isActive || !config.isReady)
			return;

		RenderAimZone();
	};
};
