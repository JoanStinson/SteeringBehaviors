#pragma once

#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneCombiningSB :
	public Scene
{
public:
	SceneCombiningSB();
	~SceneCombiningSB();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	std::vector<Zombie*>zombies;
	int a;
};

