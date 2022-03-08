#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H
#include "Character.h"
#include <iostream>
#include <string>
#include <SDL.h>
#include "Commons.h"

class Texture2D;

class CharacterLuigi : public Character
{

public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e);
};

#endif //_CHARACTERLUIGI_H