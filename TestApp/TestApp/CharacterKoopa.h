#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H
#include "Character.h"

class CharacterKoopa : public Character
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	void FlipRightwayUp();
	FACING m_facing_direction;
	float m_movement_speed;

public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	void Update(float deltaTime, SDL_Event e);
	void Render();
};

#endif //_CHARACTERKOOPA_H