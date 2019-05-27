#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneObstacleAvoidance :
	public Scene
{
public:
	SceneObstacleAvoidance();
	~SceneObstacleAvoidance();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	
private:
	std::vector<Agent*> agents;
	
	Vector2D target;
};

