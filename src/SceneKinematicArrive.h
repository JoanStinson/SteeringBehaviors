#pragma once
#include <vector>
#include "../src/Scene.h"
#include "../src/Agent.h"

class SceneKinematicArrive :
	public Scene
{
public:
	SceneKinematicArrive();
	~SceneKinematicArrive();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();	

	float r;

private:
	std::vector<Agent*> agents;
	Vector2D target;
	Vector2D dist;
	
};
