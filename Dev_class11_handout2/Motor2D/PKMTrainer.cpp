#include "PKMTrainer.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1Entities.h"
#include "j1Scene.h"



PKMTrainer::PKMTrainer(int x, int y) : Entity(x, y)
{

	idle.PushBack({15,0,14,22 });
	type = PKM_TRAINER;
	curr_animation = &idle;

}