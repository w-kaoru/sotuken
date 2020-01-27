#pragma once
#include "stdafx.h"

enum TankType
{
	pz4,
	tiha,
	nonType
};
enum BulletType
{
	HE,
	AP,
	num
};
struct STankData {
	wchar_t* filePath_00;
	wchar_t* filePath_01;
	float hp = 100.0f;
	float speed = 150.0f;
	float bodyturn = 0.01f;
	float cameraturn = 0.02f;
	float bulletdamage = 0.0f;
	float defense = 100.0f;
	float bulletSpeed = 800.0f;
	float scale = 1.0f;
	CVector3 BOXLength = CVector3::One();
};