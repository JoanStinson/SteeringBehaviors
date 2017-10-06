#pragma once
#include "Agent.h"
#include "Vector2D.h"
#include <vector>
#include "Zombie.h"

class Agent;
class Zombie;
class SteeringBehavior
{
public:
	SteeringBehavior();
	~SteeringBehavior();


	/* Add here your own Steering Behavior functions declarations */
	Vector2D Seek(Agent *agent, Vector2D target, float dtime);
	Vector2D Flee(Agent *agent, Vector2D target, float dtime);
	Vector2D Arrive(Agent *agent, Vector2D target,float r, float factor, float dtime);
	Vector2D Pursue(Agent *agent, Vector2D target, float maxSpeed, float dtime);
	Vector2D Evade(Zombie *agent, Vector2D target, float maxSpeed, float dtime);
	Vector2D Wander(Agent *agent, Vector2D target, float dtime);
	Vector2D CollisionAvoidance(Agent *agent, Vector2D target, Vector2D avoidforce, std::vector<Vector2D> obstacles, std::vector<Vector2D> distances, std::vector<Vector2D> subdistances, float dtime, float MAX_AHEAD, float MAX_AVOID_FORCE, float v);
	


};
