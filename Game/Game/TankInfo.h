#pragma once
#include "stdafx.h"

enum TankType
{
	pz4,
	tiha,
	nonType
};
struct STankData {
	wchar_t* filePath_00;
	wchar_t* filePath_01;
	float hp = 100.0f;
	float speed = 150.0f;
	float bodyturn = 0.01f;
	float cameraturn = 0.02f;
	float power = 100.0f;
	float defense = 100.0f;
};