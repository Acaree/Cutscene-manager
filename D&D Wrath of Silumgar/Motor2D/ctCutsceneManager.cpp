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
	
	ExecuteCutscene();
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {

		CutsceneActions_Queue.push(new Move(0, 2000, (Entity*) App->entities->GetCleric(), 5));

	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
		Executing_Cutscene = true;
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

void ctCutsceneManager::ExecuteCutscene()
{
	CutsceneAction* aux_CutScene = nullptr;
	if (Executing_Cutscene == true)
	{
		if (CutsceneActions_Queue.front() != nullptr) {
			aux_CutScene = CutsceneActions_Queue.front();

			//aux_CutScene->start_time <= App->cutscene_manager->Cutscene_timer.Read()

			while (aux_CutScene != nullptr) {
				if (aux_CutScene->start_time <= App->cutscene_manager->Cutscene_timer.Read()) {
					CutsceneActions_InProgress.push_back(aux_CutScene);
					CutsceneActions_Queue.pop();
					aux_CutScene = nullptr;
					if (CutsceneActions_Queue.size() != 0)
						aux_CutScene = CutsceneActions_Queue.front();
				}
			}

		}

		if (CutsceneActions_InProgress.front() != nullptr) {
			for (std::list<CutsceneAction*>::iterator it = CutsceneActions_InProgress.begin(); it != CutsceneActions_InProgress.end(); it++) {
				if ((*it)->end_time <= App->cutscene_manager->Cutscene_timer.Read()) {
					(*it)->Execute();
				}
				else {
					CutsceneActions_InProgress.remove((*it));
				}
			}
		}
	}

}

