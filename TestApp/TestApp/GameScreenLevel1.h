#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "LevelMap.h"
#include <vector>
using namespace std;

class Texture2D;
class Character;
class CharacterMario;
class CharacterLuigi;
class CharacterKoopa;
class PowBlock;

class GameScreenLevel1 : GameScreen
{

private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	Character* my_mario;
	Character* my_luigi;
	CharacterKoopa* my_koopa;
	void SetLevelMap();
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	void DoScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	vector<CharacterKoopa*> m_enemies;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdatePOWBlock();

};

#endif //_GAMESCREENLEVEL1_H