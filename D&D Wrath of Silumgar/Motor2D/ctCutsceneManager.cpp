#include "ctCutsceneManager.h"
#include "ctApp.h"
#include "ctEntities.h"
#include "ctInput.h"



bool Move::Execute()
{
	bool ret = false;

	if (actor->position.x == finalpos.x && actor->position.y == finalpos.y)
	{
		actor->animation = &actor->idle;
		ret = true;
	}
	else {
		if (actor->position.x < finalpos.x)
		{
			actor->animation = &actor->run_forward;
			actor->position.x += 5;
		}

		else if (actor->position.x > finalpos.x)
		{
			actor->animation = &actor->run_forward;
			actor->position.x -= 5;
		}

		if (actor->position.y < finalpos.y)
		{
			actor->animation = &actor->run_forward;
			actor->position.y += 5;
		}

		else if (actor->position.y > finalpos.y)
		{
			actor->animation = &actor->run_forward;
			actor->position.y -= 5;
		}
	}

	return ret;
}



bool ctCutsceneManager::Update(float dt)
{
	TaskOrderer();

	bool ret = false;
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		if (current_CutsceneAction == nullptr && CutsceneQueue.size() != 0)
		{
			current_CutsceneAction = CutsceneQueue.front();
			CutsceneQueue.pop();
		}
	}

	ret = DoTask();

	return ret;
}

bool ctCutsceneManager::Start()
{
	return true;
}

bool ctCutsceneManager::CleanUp()
{
	while (CutsceneQueue.size() != 0)
	{
		CutsceneQueue.pop();
	}
	return true;
}


bool ctCutsceneManager::ChargeCutscene(Cutscene_code cutscene)
{
	/*
	pugi::xml_document	config_file;
	pugi::xml_node* node = &App->LoadEntities(config_file);
	node = &node->child("heroes").child("cleric");

	//todo get the stats

	for (pugi::xml_node animations = node->child("animations").child("animation"); animations && ret; animations = animations.next_sibling("animation"))
	{
		CutsceneQueue.push(task);
	}
	*/
	return true;
}

bool ctCutsceneManager::DoTask()
{
	/*
	if (aux_task != nullptr)
	{
		//TODO 3 If the task is finished, pop the next task until the queue is empty
		if (aux_task->Execute())
		{
			if (TaskQueue.size() != 0)
			{
				aux_task = TaskQueue.front();
				TaskQueue.pop();
			}
			else aux_task = nullptr;

		}
	}
	*/
	return true;
}

bool ctCutsceneManager::TaskOrderer()
{

	return true;
}