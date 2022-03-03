#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H
#include "Character.h"
#include <iostream>
#include <string>
#include <SDL.h>
#include "Commons.h"

class Texture2D;

class CharacterMario : public Character
{

public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e);

};

#endif //_MARIOCHARACTER_H