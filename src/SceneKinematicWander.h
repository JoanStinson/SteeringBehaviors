#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneKinematicWander :
	public Scene
{
public:
	SceneKinematicWander();
	~SceneKinematicWander();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	float orientation;
	float wanderAngle, wanderMaxAngle, wanderOffset, wanderRadius;
	float randomBinomial() {
		return ((float)rand() / (RAND_MAX)) - ((float)rand() / (RAND_MAX));
	}
};

