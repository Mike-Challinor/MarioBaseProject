#include "CharacterMario.h"
#include "Texture2D.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map) {}

CharacterMario::~CharacterMario()
{
	m_renderer = nullptr;
}


void CharacterMario::Update(float deltaTime, SDL_Event e)
{

	//Handle the events
	switch (e.type)
		{
		//Click a key for movement
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_moving_left = true;
				break;
			case SDLK_RIGHT:
				m_moving_right = true;
				break;
			case SDLK_UP:
				if (m_can_jump)
				{
					Jump();
				}		
			}
			break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_moving_left = false;
				break;
			case SDLK_RIGHT:
				m_moving_right = false;
				break;
			}
			break;
		}

		Character::Update(deltaTime, e);

}

