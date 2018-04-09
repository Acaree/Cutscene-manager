#include "ctCutsceneManager.h"
#include "ctApp.h"
#include "ctEntities.h"
#include "ctInput.h"



bool Move::Execute()
{
	bool ret = false;

	if (App->cutscene_manager->Cutscene_timer.Read() <= end_time) {
		actor->position.x += move_speed;
	}

	else {
		ret = true;
	}
	return ret;
}



bool ctCutsceneManager::Update(float dt)
{
	CutsceneAction* aux_CutScene = nullptr;
	if (Executing_Cutscene == true)
	{
		if (CutsceneActions_Queue.front != nullptr){
			aux_CutScene = CutsceneActions_Queue.front();
			
			while (aux_CutScene->start_time <= App->cutscene_manager->Cutscene_timer.Read()){
				CutsceneActions_InProgress.push_back(aux_CutScene);
				CutsceneActions_Queue.pop();
				aux_CutScene = CutsceneActions_Queue.front();
			}

			}

		if (CutsceneActions_InProgress.front != nullptr) {
			for (CutsceneAction* it = CutsceneActions_InProgress.begin(); it != CutsceneActions_InProgress.end(); it++) {
				if(it->end_time <= App->cutscene_manager->Cutscene_timer.Read())
				it->Execute();
				else {
					CutsceneActions_InProgress.remove(it);
				}
			}
		}
	}

	return true;
}

bool ctCutsceneManager::Start()
{
	return true;
}

bool ctCutsceneManager::CleanUp()
{
	while (CutsceneActions_Queue.size() != 0)
	{
		CutsceneActions_Queue.pop();
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

void ctCutsceneManager::ExecuteCutscene(Cutscene_code cutscene)
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

}

