#include "ProfessorBirch.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1Entities.h"
#include "j1Scene.h"



ProfessorBirch::ProfessorBirch(int x, int y) : Entity(x, y)
{
	type = PROFESSOR_BIRCH;

	walk_up.PushBack({0,0,16,22});
	walk_up.PushBack({17,0,16,22 });
	walk_up.speed = 0.15f;

	walk_down.PushBack({ 34,0,16,22 });
	walk_down.PushBack({ 51,0,16,22 });
	walk_down.speed = 0.15f;

	walk_right.PushBack({ 68,0,14,22 });
	walk_right.PushBack({ 84,0,15,22 });
	walk_right.speed = 0.15f;

	walk_left.PushBack({ 101,0,14,22 });
	walk_left.PushBack({ 116,0,15,22 });
	walk_right.speed = 0.15f;

	curr_animation = &walk_right;



}