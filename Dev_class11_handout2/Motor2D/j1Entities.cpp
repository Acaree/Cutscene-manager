#include "j1App.h"
#include "j1Render.h"
#include "j1Entities.h"
#include "j1Textures.h"
#include "Entity.h"
#include "j1Window.h"

#include "PKMTrainer.h"

/*
#include "Cleric.h"
#include "Dwarf.h"
#include "Elf.h"
#include "Warrior.h"

#include "Kobold.h"
#include "Owlbear.h"
#include "Gnoll.h"
#include "GnollArcher.h"

#include "MiniHeroes.h"
*/

j1Entities::j1Entities()
{
	name = "entities";
}

// Destructor
j1Entities::~j1Entities()
{
	
	App->tex->UnLoad(trainer_sprites);
	App->tex->UnLoad(abedul_sprites);
}

bool j1Entities::Awake(pugi::xml_node& config)
{
	
	bool ret = true;

	return ret;
}

bool j1Entities::Start()
{
	bool ret = true;

	
	trainer_sprites = App->tex->Load("entities/pkm_trainer.png");
	abedul_sprites = App->tex->Load("entities/abedul_professor.png");


	return ret;
}

bool j1Entities::PreUpdate()
{
	
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->to_destroy) {
			delete(entities[i]);
			entities[i] = nullptr;
			entities.erase(entities.cbegin() + i);
			entities.shrink_to_fit();
		}
	}
	
	return true;
}

// Called before render is available
bool j1Entities::Update(float dt)
{

	for (int i = 0; i < entities.size(); i++) {
		switch (entities.at(i)->type)
		{
		case PKM_TRAINER:
			if (entities.at(i) != nullptr) entities[i]->Draw(trainer_sprites);
			break;
		case ABEDUL_PROFESSOR:
			if (entities.at(i) != nullptr) entities[i]->Draw(abedul_sprites);
			break;
		default:
			break;
		}
	}
	
	return true;

}

// Called before quitting
bool j1Entities::CleanUp()
{
	
	//App->tex->UnLoad(miniheroes_spritesheet);
	
	for (uint i = 0; i < entities.size(); ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
			entities.erase(entities.cbegin() + i);
			entities.shrink_to_fit();
		}
	}

	entities.clear();

	
	return true;
}


bool j1Entities::SpawnEntity(int x, int y, EntityType type)
{
	// find room for the new entity
	bool ret = false;

	switch (type)
	{
	case PKM_TRAINER: {
		PKMTrainer* trainer = new PKMTrainer(x, y);
		entities.push_back(trainer);
		ret = true;
		break;
	}

	default:
		break;
	}

	
	
	return ret;
}




Entity* j1Entities::GetActor(int actor_code) {

	switch (actor_code) {
	case PKM_TRAINER:
		//return GetCleric();
		break;
	case ABEDUL_PROFESSOR:
		//return GetWarrior();
		break;
	default:
		return nullptr;
		break;
	}

}
