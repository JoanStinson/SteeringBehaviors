#pragma once
#include <vector>
#include "../src/Scene.h"
#include "../src/Agent.h"

class SceneCollisionAvoidance :
	public Scene
{
public:
	SceneCollisionAvoidance();
	~SceneCollisionAvoidance();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	float factor;
	float r;
	float MAX_AHEAD, MAX_AVOID_FORCE;

private:
	std::vector<Agent*> agents;
	Vector2D target;
	Vector2D dist;
	Vector2D test;
	std::vector<Vector2D> obstacles;
	std::vector<Vector2D> distances, subdistances;
	Vector2D avoidForce;
	float dynamicVelocity;

};
