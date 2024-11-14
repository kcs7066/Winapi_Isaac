#pragma once


enum class ERenderOrder
{
	BACKGROUND = -1000,
	
	COLMAP = -999,


	DOOR = -500,
	STRUCTURE = -3,
	MONSTER = -2,
	SHADOW = -1,
	PLAYER = 0,
	UI = 10000
};

enum class ECollisionGroup
{
	Player,
	Monster,
	Structure,
	TrapDoor,
	Tear,
	
	MonsterTear,
	Door
};