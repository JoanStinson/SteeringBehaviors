#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class ScenePathFinding :
	public Scene
{
public:
	ScenePathFinding();
	   ~ScenePathFinding();
	   void update(float dtime, SDL_Event *event);
	   void draw();
	   const char* getTitle();
	   int currentTargetIndex;
private:
	std::vector<Agent*> agents;
	Vector2D target;


};
