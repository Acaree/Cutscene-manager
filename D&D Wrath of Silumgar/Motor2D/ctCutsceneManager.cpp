#include "ctCutsceneManager.h"
#include "ctApp.h"
#include "ctEntities.h"
#include "ctRender.h"
#include "ctInput.h"



bool Move::Execute()
{
	bool ret = false;

	if (uint32 i = App->cutscene_manager->Cutscene_timer.Read() <= end_time) {
		actor->position.x += 5;
	}

	else {
		ret = true;
	}
	return ret;
}



bool ctCutsceneManager::Update(float dt)
{
	
	ExecuteCutscene();
	

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
		Executing_Cutscene = true;
		Cutscene_timer.Start();
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
	pugi::xml_document track_file;
	pugi::xml_parse_result result = track_file.load_file("cutscene.xml");
	pugi::xml_node cutscene_node;
	switch (cutscene) {
	case CUTSCENE_1:
		cutscene_node = track_file.child("cutscenes").child("cutscene1").child("cutscene_action");
		break;
	default:
		break;
	}
	
	while (cutscene_node != nullptr) {
		App->cutscene_manager->CutsceneActions_InProgress.push_back(new Move(cutscene_node.attribute("start_time").as_int(), cutscene_node.attribute("end_time").as_int(), App->entities->GetActor(cutscene_node.attribute("actor").as_int()), cutscene_node.attribute("speed").as_int()));
		cutscene_node = cutscene_node.next_sibling();
	}
	
	return true;
}

void ctCutsceneManager::ExecuteCutscene()
{
	//CutsceneAction* aux_CutScene = nullptr;
	if (Executing_Cutscene == true)
	{
		/*if (CutsceneActions_Queue.front() != nullptr) {
			aux_CutScene = CutsceneActions_Queue.front();
				if (aux_CutScene->start_time <= App->cutscene_manager->Cutscene_timer.Read()) {
					CutsceneActions_InProgress.push_back(aux_CutScene);
					CutsceneActions_Queue.pop();
				}
			}
			
		if (CutsceneActions_InProgress.front() != nullptr) {
			for (std::list<CutsceneAction*>::iterator it = CutsceneActions_InProgress.begin(); it != CutsceneActions_InProgress.end(); it++) {
				if((*it)->Execute() == true) {
					CutsceneActions_InProgress.remove((*it));
				}
			}
		}*/



		if (CutsceneActions_InProgress.front() != nullptr) {
		
			for (std::list<CutsceneAction*>::iterator it = CutsceneActions_InProgress.begin(); it != CutsceneActions_InProgress.end(); it++) {
				
				if ((*it)->start_time <= Cutscene_timer.Read()) {

					if ((*it)->Execute()) {

						CutsceneActions_InProgress.remove((*it));
					}

				}
			
			}
		
		}


	}

}

