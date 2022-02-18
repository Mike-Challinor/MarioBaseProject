#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"

class Texture2D;
class Character;

class GameScreenLevel1 : GameScreen
{

private:
	Texture2D* m_background_texture;
	Character* my_character;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	bool SetUpLevel();
};

#endif //_GAMESCREENLEVEL1_H