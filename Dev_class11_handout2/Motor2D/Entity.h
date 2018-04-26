#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include "ctAnimation.h"




struct SDL_Texture;

enum EntityType
{
	PKM_TRAINER,
	ABEDUL_PROFESSOR,

	NO_TYPE
};

class Entity
{
protected:

	float gravity = 1.0f;
	float speed_jump = 0;
	float speed = 0;


public:
	fPoint position;
	ctAnimation* curr_animation = nullptr;
	EntityType type;

	bool to_destroy = false;
	
public:
	Entity(int x, int y);
	virtual ~Entity();

	virtual void Move(float dt) {};
	virtual void Draw(SDL_Texture* sprites);
};

#endif // __ENEMY_H__
