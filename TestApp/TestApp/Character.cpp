#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
{
	m_renderer = renderer;
	m_position = start_position;

	//load texture
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load character texture!" << std::endl;
	}
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	//draw the character
	m_texture->Render(m_position, SDL_FLIP_NONE);
}

void Character::Update(float deltaTime, SDL_Event e)
{

	//Get events
	SDL_PollEvent(&e);

	//Handle the events
	switch (e.type)
	{
	//Click a key for movement
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_position.x -= 1;
			break;
		case SDLK_RIGHT:
			m_position.x += 1;
			break;
		}
	}
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}
