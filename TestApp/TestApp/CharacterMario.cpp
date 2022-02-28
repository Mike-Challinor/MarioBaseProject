#include "CharacterMario.h"
#include "Texture2D.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position)
{
	m_facing_direction = FACING_RIGHT;
	m_renderer = renderer;
	m_position = start_position;
	m_moving_left = false;
	m_moving_right = false;

	//load texture
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load character texture!" << std::endl;
	}
}

CharacterMario::~CharacterMario()
{
	m_renderer = nullptr;
}

void CharacterMario::Render()
{
	//draw the character
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{

	//deal with jumping first
	if (m_jumping)
	{
		//adjust position
		m_position.y -= m_jump_force * deltaTime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//is jump force 0?
		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;

		}

	}

	AddGravity(deltaTime);

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}

	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	//Get Events
	SDL_PollEvent(&e);

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

}

void CharacterMario::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D CharacterMario::GetPosition()
{
	return m_position;
}

void CharacterMario::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_LEFT;

}

void CharacterMario::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_RIGHT;
}


void CharacterMario::AddGravity(float deltaTime)
{
	if (m_position.y + 64 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
	}

	else
	{
		m_can_jump = true;
	}
}

void CharacterMario::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}