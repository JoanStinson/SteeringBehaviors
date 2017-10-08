#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#define SEP_FORCE 100.0f;
class Separation :
	public Scene
{
public:
	Separation();
	~Separation();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	Vector2D dist, separation, cohesion, alignment;
	float r;
	int neighbourCount;
	std::vector <Vector2D>obstacles;


};

