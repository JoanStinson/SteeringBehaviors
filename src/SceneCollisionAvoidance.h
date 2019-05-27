#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneCollisionAvoidance :
	public Scene
{
public:
	SceneCollisionAvoidance();
	~SceneCollisionAvoidance();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	bool inside = false;
	float shortestDist = 250;
	bool colDetec;
	Agent* nearestTarget;
private:
	std::vector<Agent*> agents;
	std::vector<Agent*> obstacles;
	Vector2D target;
};

