#include "Collisions.h"
#include "Character.h"

//Initialise instance to nullptr
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions() {}

Collisions::~Collisions()
{
	m_instance = nullptr;
}


Collisions* Collisions::Instance()
{
	if(!m_instance)
	{
		m_instance = new Collisions;
	}

	return m_instance;

}

bool Collisions::Circle(Character* character1, Character* character2)
{
	//Vector calculation between two characters
	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x), (character1->GetPosition().y - character2->GetPosition().y));

	//Calculate length of vector
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	//Collision radius of each character combined
	double combined_distance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());

	//Check if distance is shorter than accumulated distance radii
	return distance < combined_distance;

}

//bool Collisions::Box(Rect2D rect1, Rect2D rect2)
//{
//
//}