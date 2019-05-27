#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneKinematicSeek :
	public Scene
{
public:
	SceneKinematicSeek();
	~SceneKinematicSeek();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	bool pursue = false;
	bool evade = false;
};

