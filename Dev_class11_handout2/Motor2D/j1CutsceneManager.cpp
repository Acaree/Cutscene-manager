#include "j1CutsceneManager.h"
#include "j1App.h"
#include "j1Entities.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Gui.h"



bool MoveX::Execute()
{
	bool ret = false;

	if (App->cutscene_manager->Cutscene_timer.Read() <= end_time) {
		if (move_speed >= 0) {
			actor->curr_animation = &actor->walk_right;
		}

		else {
			actor->curr_animation = &actor->walk_left;
		}

		actor->position.x += move_speed;
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

		if (move_speed >= 0) {
			actor->curr_animation = &actor->walk_down;
		}

		else {
			actor->curr_animation = &actor->walk_up;
		}

		actor->position.y += move_speed;
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
		App->render->camera.x += move_speed;
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
		App->render->camera.y += move_speed;
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
		//Background = App->gui->AddImage({ 0, 100 }, { 570,107,100,100 }, App->gui->GetAtlas(),nullptr,false);
		//Text = App->gui->AddLabel({ 0, 100 }, "adwsqgfqg", { 0,0,0,255 }, App->font->default,nullptr,false,0);
		first_iteration = false;
	}

	if (App->cutscene_manager->Cutscene_timer.Read() > end_time) {
		ret = true;
	}

	return ret;
}

CutsceneDialog::~CutsceneDialog() {

	//App->gui->DeleteUIElement(*Text);
	//App->gui->DeleteUIElement(*Background);
}


bool j1CutsceneManager::Update(float dt)
{

	ExecuteCutscene();

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
		ChargeCutscene(CUTSCENE_1);
		Executing_Cutscene = true;
		Cutscene_timer.Start();
	}

	return true;
}

bool j1CutsceneManager::Start()
{
	return true;
}

bool j1CutsceneManager::CleanUp()
{
	CutsceneActions.clear();
	return true;
}


bool j1CutsceneManager::ChargeCutscene(Cutscene_code cutscene)
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
			CutsceneActions.push_back(new MoveX(cutscene_node.attribute("start_time").as_int(), cutscene_node.attribute("end_time").as_int(), App->entities->GetActor(cutscene_node.attribute("actor").as_int()), cutscene_node.attribute("speed").as_float()));
		}

		if (action == 1) {
			CutsceneActions.push_back(new MoveY(cutscene_node.attribute("start_time").as_int(), cutscene_node.attribute("end_time").as_int(), App->entities->GetActor(cutscene_node.attribute("actor").as_int()), cutscene_node.attribute("speed").as_float()));
		}

		if (action == 2) {
			CutsceneActions.push_back(new CutsceneDialog(cutscene_node.attribute("start_time").as_int(), cutscene_node.attribute("end_time").as_int(), cutscene_node.attribute("text").as_string()));
		}

		if (action == 3) {
			CutsceneActions.push_back(new MoveCameraX(cutscene_node.attribute("start_time").as_int(), cutscene_node.attribute("end_time").as_int(), cutscene_node.attribute("speed").as_float()));
		}

		if (action == 4) {
			CutsceneActions.push_back(new MoveCameraY(cutscene_node.attribute("start_time").as_int(), cutscene_node.attribute("end_time").as_int(), cutscene_node.attribute("speed").as_float()));
		}
		cutscene_node = cutscene_node.next_sibling();
	}

	return true;
}

void j1CutsceneManager::ExecuteCutscene()
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

