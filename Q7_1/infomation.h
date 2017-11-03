#pragma once
#ifndef __INFOMATION_H__
#define __INFOMATION_H__
#define NAME 20
#define MAX_INFO 6
#define XC 80
#define YC 10
#define DICE 6
typedef struct info
{
	int nHp;
	int nDamage;
	int nDef;
	char cName[NAME];
}Info;

typedef enum flag
{
	Attack
}E_FLAG;

typedef enum infomation
{
	PLAYER, ORC, TROLL, OGRE, IMP, DRAGON
}E_INFO;

#endif // !__INFOMATION_H__
