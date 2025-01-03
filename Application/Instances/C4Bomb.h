#pragma once

#include "../Modules/Module.h"

class C4Bomb
{
public:
	uintptr_t plantedPtr;
	std::string name = "C4Bomb";
	Timer FuseChrono = Timer(40500);
	Timer DefuseChrono = Timer(30500);
	Timer DefuseKitChrono = Timer(35500);

	int team;
	Vector3 position;
	Dimension screen_d, esp_d;
	Position screenPos, esp_p;

	bool isPlanted;
	bool isTeammate;

	void Update()
	{
		isPlanted = BombIsPlanted();

		if (!isPlanted)
		{
			DefuseKitChrono.Reset();
			DefuseChrono.Reset();
			FuseChrono.Reset();
			return;
		}

		if (!FuseChrono.IsRunning())
		{
			DefuseKitChrono.Start();
			DefuseChrono.Start();
			FuseChrono.Start();
		}
	}
};
