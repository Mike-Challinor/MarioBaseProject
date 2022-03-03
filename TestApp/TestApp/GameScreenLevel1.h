#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"

class Texture2D;
class Character;
class CharacterMario;
class CharacterLuigi;

class GameScreenLevel1 : GameScreen
{

private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	Character* my_mario;
	Character* my_luigi;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

};

#endif //_GAMESCREENLEVEL1_H