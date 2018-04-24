#include "ctCutsceneManager.h"
#include "ctApp.h"
#include "ctEntities.h"
#include "ctRender.h"
#include "ctInput.h"
#include "ctGui.h"



bool MoveX::Execute()
{
	bool ret = false;

	if (App->cutscene_manager->Cutscene_timer.Read() <= end_time) {
		actor->position.x += 5;
	}

	else {
		ret = true;
	}
	return ret;
}

bool MoveY::Execute()
{
	bool ret = false;

	if (App->cutscene_manager->Cutscene_timer.Read() <= end_time) {
		actor->position.y += 5;
	}

	else {
		ret = true;
	}
	return ret;
}

bool MoveCameraX::Execute()
{
	bool ret = false;

	if (App->cutscene_manager->Cutscene_timer.Read() <= end_time) {
		App->render->camera.x += 5;
	}

	else {
		ret = true;
	}
	return ret;
}

bool MoveCameraY::Execute()
{
	bool ret = false;

	if (App->cutscene_manager->Cutscene_timer.Read() <= end_time) {
		App->render->camera.y += 5;
	}

	else {
		ret = true;
	}
	return ret;
}

bool CutsceneDialog::Execute()
{
	bool ret = false;

	if (first_iteration) {
		Background = App->gui->AddUIImage(0, 100, { 570,107,100,100 });
		Text = App->gui->AddUITextBox(0, 100, 15, 500, "adwsqgfqg", {0,0,0,255 }, Background, Second_Font);
		first_iteration = false;
	}

	if (App->cutscene_manager->Cutscene_timer.Read() > end_time) {
		ret = true;
	}

	return ret;
}

CutsceneDialog::~CutsceneDialog() {

	App->gui->DeleteUIElement(*Text);
	App->gui->DeleteUIElement(*Background);
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
	CutsceneActions.clear();
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
		int action = cutscene_node.attribute("cutscene_action").as_int();
		
		if (action == 0) {
			App->cutscene_manager->CutsceneActions.push_back(new MoveX(cutscene_node.attribute("start_time").as_int(), cutscene_node.attribute("end_time").as_int(), App->entities->GetActor(cutscene_node.attribute("actor").as_int()), cutscene_node.attribute("speed").as_int()));
		}

		if (action == 1) {
			App->cutscene_manager->CutsceneActions.push_back(new MoveY(cutscene_node.attribute("start_time").as_int(), cutscene_node.attribute("end_time").as_int(), App->entities->GetActor(cutscene_node.attribute("actor").as_int()), cutscene_node.attribute("speed").as_int()));
		}

		if (action == 2) {
			App->cutscene_manager->CutsceneActions.push_back(new CutsceneDialog(cutscene_node.attribute("start_time").as_int(), cutscene_node.attribute("end_time").as_int()));
		}

		if (action == 3) {
			//App->cutscene_manager->CutsceneActions.push_back(new MoveCameraX(cutscene_node.attribute("start_time").as_int(), cutscene_node.attribute("end_time").as_int(), cutscene_node.attribute("speed").as_int()));
		}

		if (action == 4) {
			App->cutscene_manager->CutsceneActions.push_back(new MoveCameraY(cutscene_node.attribute("start_time").as_int(), cutscene_node.attribute("end_time").as_int(), cutscene_node.attribute("speed").as_int()));
		}
		cutscene_node = cutscene_node.next_sibling();
	}
	
	return true;
}

void ctCutsceneManager::ExecuteCutscene()
{
	if (Executing_Cutscene == true)
	{
		if (CutsceneActions.front() != nullptr) {
		
			for (std::list<CutsceneAction*>::iterator it = CutsceneActions.begin(); it != CutsceneActions.end(); it++) {
				
				if ((*it)->start_time <= Cutscene_timer.Read()) {

					if ((*it)->Execute()) {

						CutsceneActions.remove((*it));
						(*it)->~CutsceneAction();
					}
				}
			}
		}
	}
}

