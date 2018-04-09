#ifndef _CTCUTSCENEMANAGER_H__
#define _CTCUTSCENEMANAGER_H__

#include "ctPoint.h"
#include <queue>
#include "ctModule.h"
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
	CutsceneAction() {};
	virtual ~CutsceneAction() {};
	virtual bool Execute() { return true; };

private:

};

class ctCutsceneManager : public ctModule
{
public:
	ctCutsceneManager() {};
	~ctCutsceneManager() {};

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	bool TaskOrderer();
	bool ChargeCutscene(Cutscene_code cutscene);
	bool DoTask();

	Entity* Actor = nullptr;



private:
	//TODO 1 Create a queue of tasks
	std::queue<CutsceneAction*> CutsceneQueue;

	CutsceneAction* current_CutsceneAction = nullptr;

public:
	

};


class Move : public CutsceneAction
{
public:
	Move(Entity* actor, iPoint finalpos, int speed) {
		this->actor = actor;
		this->finalpos = finalpos;
		previousSpeed = actor->move_speed;
		actor->move_speed = speed;
		
	};
	~Move() {};

	bool Execute();
private:
	Entity* actor = nullptr;
	iPoint finalpos;
	int previousSpeed;
};

#endif

