#include "Mew.h"
#include "j1Textures.h"
#include "j1App.h"
#include "j1Entities.h"
#include "j1Scene.h"



Mew::Mew(int x, int y) : Entity(x, y)
{
	type = MEW;

	walk_up.PushBack({ 31,3,13,25 });
	walk_up.PushBack({ 47,3,13,25 });
	walk_up.speed = 0.15f;

	walk_down.PushBack({ 0,2,13,27 });
	walk_down.PushBack({ 16,2,13,27 });
	walk_down.speed = 0.15f;

	walk_right.PushBack({ 94,0,16,29 });
	walk_right.PushBack({ 110,0,16,29 });
	walk_right.speed = 0.15f;

	walk_left.PushBack({ 62,0,16,29 });
	walk_left.PushBack({ 78,0,16,29 });
	walk_left.speed = 0.15f;

	curr_animation = &walk_right;



}