#include "j1App.h"
#include "j1Render.h"
#include "j1Entities.h"
#include "j1Textures.h"
#include "j1Window.h"




j1Entities::j1Entities()
{
	name = "entities";
}

// Destructor
j1Entities::~j1Entities()
{
	
	App->tex->UnLoad(trainer_sprites);
	App->tex->UnLoad(birch_sprites);
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
	birch_sprites = App->tex->Load("entities/abedul_professor.png");


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
		case PROFESSOR_BIRCH:
			if (entities.at(i) != nullptr) entities[i]->Draw(birch_sprites);
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

	case PROFESSOR_BIRCH: {
		ProfessorBirch* birch = new ProfessorBirch(x, y);
		entities.push_back(birch);
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
		return GetTrainer();
		break;
	case PROFESSOR_BIRCH:
		return GetBirch();
		break;
	default:
		return nullptr;
		break;
	}

}


PKMTrainer* j1Entities::GetTrainer() {

	for (uint i = 0; i < entities.size(); ++i)
	{
		if (entities.at(i) != nullptr)
		{
			if (entities[i]->type == PKM_TRAINER)
				return (PKMTrainer*)entities[i];
		}
	}

	return nullptr;

}

ProfessorBirch* j1Entities::GetBirch() {

	for (uint i = 0; i < entities.size(); ++i)
	{
		if (entities.at(i) != nullptr)
		{
			if (entities[i]->type == PROFESSOR_BIRCH)
				return (ProfessorBirch*)entities[i];
		}
	}

	return nullptr;

}
