#pragma once
#include "stdafx.h"

enum TankType
{
	ninzuu,
	pz4,
	tiha,
	Stage1,
	Stage2,
	nonType
};
enum BulletType
{
	HE,
	AP,
	num
};

struct STankBulletInfo {
	float bulletdamage = 0.0f;
	float bulletSpeed = 800.0f;
};

struct STankData {
	wchar_t* filePath_00;
	wchar_t* filePath_01;
	wchar_t* filePath_02;
	float hp = 100.0f;
	float speed = 150.0f;
	float bodyturn = 0.01f;
	float cameraturn = 0.02f;
	float defense = 100.0f;
	float scale = 1.0f;
	CVector3 BOXLength = CVector3::One();
};