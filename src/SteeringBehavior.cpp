#include "SteeringBehavior.h"



SteeringBehavior::SteeringBehavior()
{
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desiredV = target - agent->getPosition(); // agafam el vector que resulta de restar posició on volem anar - posició actual. Resultat= velocitat adecuada
	desiredV = desiredV.Normalize();
	desiredV *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredV - agent->getVelocity();
	steeringForce /= agent->getMaxVelocity();
	steeringForce *= agent->getMaxForce();

	return steeringForce; //DONE
}


Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D DesiredVelocity = agent->getPosition() - target;
	DesiredVelocity = DesiredVelocity.Normalize();
	DesiredVelocity *= agent->getMaxVelocity();
	Vector2D SteeringForce = (DesiredVelocity - agent->getVelocity());
	SteeringForce /= agent->getMaxVelocity();
	return SteeringForce * agent->getMaxForce();
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime)
{
	return KinematicFlee(agent, target->position, dtime);
}

/* Add here your own Steering Behavior functions definitions */

Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	return Vector2D(0, 0);
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime)
{
	return Vector2D(0,0);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, float dtime)
{
	return Flee(agent, target->position, dtime);
}
