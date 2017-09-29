#pragma once
#include <vector>
#include "../src/Scene.h"
#include "../src/Agent.h"

class SceneKinematicPursue :
	public Scene
{
public:
	SceneKinematicPursue();
	~SceneKinematicPursue();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();

private:
	std::vector<Agent*> agents;
	Vector2D target;
	Vector2D dist;
	Vector2D objective; //distancia entre zombi i persona

};
