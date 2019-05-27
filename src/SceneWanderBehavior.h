#pragma once

#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneWanderBehavior :
	public Scene
{
public:
	SceneWanderBehavior();
	~SceneWanderBehavior();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();

	int wanderRadius = 100;
	float wanderOffset = 250;
	float wanderAngle = 0;
	float wanderMax = 90;

private:
	std::vector<Agent*> agents;
	Vector2D target;

	
};

