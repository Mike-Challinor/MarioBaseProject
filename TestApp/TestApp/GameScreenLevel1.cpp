#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include <iostream>



GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{	
	delete m_background_texture;
	m_background_texture = nullptr;

	delete my_mario;
	my_mario = nullptr;

	delete my_luigi;
	my_luigi = nullptr;
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//draw the character
	my_mario->Render();
	my_luigi->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{

	if (Collisions::Instance()->Circle(my_mario, my_luigi))
	{
		cout << "Circle hit!" << endl;
	}

	if (Collisions::Instance()->Box(my_mario->GetCollisionBox(), my_luigi->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}

	//update character
	my_mario->Update(deltaTime, e);
	my_luigi->Update(deltaTime, e);

}

bool GameScreenLevel1::SetUpLevel()
{

	//set up Mario character
	my_mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(128, 330));
	//set up Luigi character
	my_luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330));

	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	else
	{
		return true;
	}
	
}