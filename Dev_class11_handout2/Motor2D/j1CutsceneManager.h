#ifndef _CTCUTSCENEMANAGER_H__
#define _CTCUTSCENEMANAGER_H__

#include "p2Point.h"
#include <queue>
#include <list>
#include "j1Module.h"
#include "j1Timer.h"
#include "Entity.h"
#include "j1Gui.h"
#include "SDL/include/SDL.h"

class Entity;

enum EntityType;

enum Cutscene_code
{
	CUTSCENE_1
};


class CutsceneAction
{
public:
	CutsceneAction(uint32 start_time, uint32 end_time) {
		this->start_time = start_time;
		this->end_time = end_time;
	};
	virtual ~CutsceneAction() {};
	virtual bool Execute() { return true; };
	uint32 start_time;
	uint32 end_time;
protected:



};

class MoveX : public CutsceneAction
{
public:
	MoveX(uint32 start_time, uint32 end_time, Entity* actor, uint32 speed) : CutsceneAction(start_time, end_time) {
		this->actor = actor;
		speed = move_speed;
	};
	~MoveX() {};

	bool Execute();
private:
	Entity* actor = nullptr;
	int move_speed;
};

class MoveY : public CutsceneAction
{
public:
	MoveY(uint32 start_time, uint32 end_time, Entity* actor, uint32 speed) : CutsceneAction(start_time, end_time) {
		this->actor = actor;
		speed = move_speed;
	};
	~MoveY() {};

	bool Execute();
private:
	Entity* actor = nullptr;
	int move_speed;
};


class MoveCameraX : public CutsceneAction
{
public:
	MoveCameraX(uint32 start_time, uint32 end_time, Entity* actor, uint32 speed) : CutsceneAction(start_time, end_time) {
		speed = move_speed;
	};
	~MoveCameraX() {};

	bool Execute();
private:
	int move_speed;
};

class MoveCameraY : public CutsceneAction
{
public:
	MoveCameraY(uint32 start_time, uint32 end_time, uint32 speed) : CutsceneAction(start_time, end_time) {
		speed = move_speed;
	};
	~MoveCameraY() {};

	bool Execute();
private:
	int move_speed;
};

class CutsceneDialog : public CutsceneAction
{
public:
	CutsceneDialog(uint32 start_time, uint32 end_time) : CutsceneAction(start_time, end_time) {};
	~CutsceneDialog();

	bool Execute();
private:
	UIElement* Text = nullptr;
	UIElement* Background = nullptr;
	bool first_iteration = true;
};

class j1CutsceneManager : public j1Module
{
public:
	j1CutsceneManager() {};
	~j1CutsceneManager() {};

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	bool ChargeCutscene(Cutscene_code cutscene);
	void ExecuteCutscene();
	j1Timer Cutscene_timer;
	std::list<CutsceneAction*> CutsceneActions;


private:

	bool Executing_Cutscene = false;

};




#endif

