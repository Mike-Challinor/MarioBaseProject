#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "PowBlock.h"
#include <iostream>



GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{	
	delete m_background_texture;
	m_background_texture = nullptr;

	delete my_mario;
	my_mario = nullptr;

	delete my_luigi;
	my_luigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//draw the characters
	my_mario->Render();
	my_luigi->Render();

	//Draw the pow blocks
	m_pow_block->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{

	//do screenshake if required
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

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

	//update POW Blocks
	UpdatePOWBlock();

}

bool GameScreenLevel1::SetUpLevel()
{

	//Set up levelmap
	SetLevelMap();

	//set up Mario character
	my_mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(128, 330), m_level_map);
	//set up Luigi character
	my_luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);
	//set up POW block
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	m_screenshake = false;
	m_background_yPos = 0.0f;

	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	else
	{
		return true;
	}
	
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
									   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);
	
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(my_mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->isAvailable())
		{
			//collided while jumping
			if (my_mario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				my_mario->CancelJump();
			}
		}
	}

	else if (Collisions::Instance()->Box(my_luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->isAvailable())
		{
			//collided while jumping
			if (my_luigi->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				my_luigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}