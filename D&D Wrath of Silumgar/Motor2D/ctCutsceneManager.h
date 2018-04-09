#ifndef _CTCUTSCENEMANAGER_H__
#define _CTCUTSCENEMANAGER_H__

#include "ctPoint.h"
#include <queue>
#include <list>
#include "ctModule.h"
#include "ctTimer.h"
#include "Entity.h"
#include "SDL/include/SDL.h"

class Entity;

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

class Move : public CutsceneAction
{
public:
	Move(uint32 start_time, uint32 end_time,Entity* actor, uint32 speed) : CutsceneAction(start_time, end_time) {
		this->actor = actor;
		speed = move_speed;
	};
	~Move() {};

	bool Execute();
private:
	Entity* actor = nullptr;
	int move_speed;
};

class ctCutsceneManager : public ctModule
{
public:
	ctCutsceneManager() {};
	~ctCutsceneManager() {};

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	bool ChargeCutscene(Cutscene_code cutscene);
	void ExecuteCutscene(Cutscene_code cutscene);
	ctTimer Cutscene_timer;


private:
	//TODO 1 Create a queue of tasks
	std::queue<CutsceneAction*> CutsceneActions_Queue;
	std::list<CutsceneAction*> CutsceneActions_InProgress;
	bool Executing_Cutscene = false;
	//ctTimer Cutscene_timer;

public:
	

};




#endif

