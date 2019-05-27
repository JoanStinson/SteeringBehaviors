#pragma once
#include "Agent.h"
#include "Vector2D.h"
#include <vector>
class Agent;

class SteeringBehavior
{
public:
	float wanderAngle;
	SteeringBehavior();
	~SteeringBehavior();
	Vector2D KinematicSeek(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicSeek(Agent *agent, Agent *target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Agent *target, float dtime);

	/* Add here your own Steering Behavior functions declarations */
	Vector2D Seek(Agent *agent, Vector2D target, float dtime);
	Vector2D Seek(Agent *agent, Agent *target, float dtime);
	Vector2D Flee(Agent *agent, Vector2D target, float dtime);
	Vector2D Flee(Agent *agent, Agent *target, float dtime);
	Vector2D Pursue(Agent *agent, Agent *target, float dtime);
	Vector2D Evade(Agent *agent, Agent *target, float dtime);
	Vector2D Wander(Agent *agent, float dtime);
	Vector2D Wander(Agent *agent, Vector2D target, float dtime);
	//etc...
	Vector2D SeekPath(Agent *agent, Vector2D target, float dtime);
	Vector2D SeekPath(Agent *agent, Agent *target, float dtime);
	Vector2D Flocking(Agent *agent, Vector2D target, float dtime);
	Vector2D Flocking(Agent *agent, std::vector<Agent*> target, float dtime);
	Vector2D CollisionAvoidance(Agent *agent, std::vector<Agent*> target, float dtime);
	Vector2D CollisionAvoidance(Agent *agent, Agent *target, float dtime);

	Vector2D CollisionRayCast(Agent *agent, std::vector<Agent*> obstacles, float dtime);
	Vector2D CollisionRayCast(Agent *agent, Agent *obstacles, float dtime);


};
