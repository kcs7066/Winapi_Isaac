#pragma once


enum class ERenderOrder
{
	BACKGROUND = -1000,
	
	COLMAP = -999,


	DOOR = -500,
	STRUCTURE = -300,
	SHADOW = -200,

	MONSTERBACK = -101,
	MONSTER = -100,
	MONSTERFRONT = -99,

	PICKUP = -75,

	BOMB = -50,

	ITEM = -25,
	
	PLAYER = 0,
	MAPBOARD = 9999,
	UI = 10000,
	ICON = 10001
};

enum class ECollisionGroup
{
	Player,
	Monster,
	Structure,
	TrapDoor,
	Tear,
	Bomb,
	PickUp,
	Item,

	Radius,
	MonsterTear,
	Door
};