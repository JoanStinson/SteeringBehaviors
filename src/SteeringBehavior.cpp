#include "SteeringBehavior.h"
#include "SceneKinematicArrive.h"



SteeringBehavior::SteeringBehavior()
{
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desiredV = target - agent->getPosition(); // agafam el vector que resulta de restar posició on volem anar - posició actual. Resultat= velocitat adecuada
	desiredV = desiredV.Normalize();
	desiredV *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredV - agent->getVelocity();
	steeringForce /= agent->getMaxVelocity();
	steeringForce *= agent->getMaxForce();

	return steeringForce;
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D DesiredVelocity = agent->getPosition() - target;
	DesiredVelocity = DesiredVelocity.Normalize();
	DesiredVelocity *= agent->getMaxVelocity();
	Vector2D SteeringForce = (DesiredVelocity - agent->getVelocity());
	SteeringForce /= agent->getMaxVelocity();
	return SteeringForce * agent->getMaxForce();
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, float r, float factor, float dtime) {
	Vector2D desiredV = target - agent->getPosition(); // agafam el vector que resulta de restar posició on volem anar - posició actual. Resultat= velocitat adecuada
	Vector2D steeringForce = desiredV - agent->getVelocity();

	Vector2D dist = target - agent->getPosition();

	if (dist.Length() >= r) {
		draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 0, 255, 1);
		desiredV = desiredV.Normalize();
		desiredV *= agent->getMaxVelocity();
		steeringForce /= agent->getMaxVelocity();
		steeringForce *= agent->getMaxForce();
	}
	else {
		factor = dist.Length() / r; 
		draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 255, 0, 1);
		desiredV *= factor;
	}



	return steeringForce;
}

Vector2D SteeringBehavior::Pursue(Agent *agent, Vector2D target,float maxSpeed, float dtime)
{

	Vector2D desiredV = target - agent->getPosition(); // agafam el vector que resulta de restar posició on volem anar - posició actual. Resultat= velocitat adecuada
	desiredV = desiredV.Normalize();
	desiredV *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredV - agent->getVelocity();
	steeringForce /= agent->getMaxVelocity();
	steeringForce *= agent->getMaxForce();

	return steeringForce;
}

