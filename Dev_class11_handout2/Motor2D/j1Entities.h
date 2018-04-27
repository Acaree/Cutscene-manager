#ifndef __j1Entities_H__
#define __j1Entities_H__

#include "j1Module.h"
#include "ctAnimation.h"
#include "Entity.h"
#include "PKMTrainer.h"
#include "ProfessorBirch.h"

#include <vector>
#include <string>
#include <queue>


class PKMTrainer;
class ProfessorBirch;

struct SDL_Texture;


class j1Entities : public j1Module
{
public:

	j1Entities();
	~j1Entities();

	bool Awake(pugi::xml_node& conf);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool CleanUp();

	bool SpawnEntity(int x, int y, EntityType type);


	//getters
	
	Entity* GetActor(int actor_code);

	PKMTrainer* GetTrainer();
	ProfessorBirch* GetBirch();

	std::vector<Entity*> entities;

private:

	SDL_Texture* birch_sprites = nullptr;
	SDL_Texture* trainer_sprites = nullptr;

public:
	///HEROES
	

};

#endif // __ctEnemies_H__


