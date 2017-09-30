#pragma once
#include "Agent.h"
#include "Vector2D.h"

class Agent;

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



};
