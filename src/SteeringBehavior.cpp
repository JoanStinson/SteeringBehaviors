#include "SteeringBehavior.h"
#include <vector>


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
Vector2D SteeringBehavior::Evade(Zombie *agent, Vector2D target, float maxSpeed, float dtime)
{

	Vector2D desiredV = target - agent->getPosition(); // agafam el vector que resulta de restar posició on volem anar - posició actual. Resultat= velocitat adecuada
	desiredV = desiredV.Normalize();
	desiredV *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredV - agent->getVelocity();
	steeringForce /= agent->getMaxVelocity();
	steeringForce *= agent->getMaxForce();

	return steeringForce;
}
Vector2D SteeringBehavior::Wander(Agent *agent, Vector2D target, float dtime)
{

	Vector2D desiredV = target - agent->getPosition(); 
	desiredV = desiredV.Normalize();
	desiredV *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredV - agent->getVelocity();
	steeringForce /= agent->getMaxVelocity();
	steeringForce *= agent->getMaxForce();

	return steeringForce;
}

Vector2D SteeringBehavior::CollisionAvoidance(Agent *agent, Vector2D target,Vector2D avoidForce, std::vector<Vector2D> obstacles, std::vector<Vector2D> distances, std::vector<Vector2D> subdistances, float dtime, float MAX_AHEAD, float MAX_AVOID_FORCE, float v)
{
	v = agent->getVelocity().Length() / agent->getMaxVelocity();
	Vector2D ahead = agent->getPosition() + agent->getVelocity().Normalize() * v; // aixo va a mitjes. Ahead es un vector que va de 0 a 1. Per lo que només hi veu a un pixel de distancia
	Vector2D halfahead = agent->getPosition() + agent->getVelocity().Normalize() * v * 0.5;
	
	for (int i = 0; i < obstacles.size(); i++) {
		Vector2D d = obstacles[i] - ahead;
		distances.push_back(d);
		Vector2D subD = obstacles[i] - halfahead;
		subdistances.push_back(subD);
	};

	if (distances.size() != 0) {

		for (int i = 0; i < distances.size(); i++) {
			if (distances[i].Length() <= 50 || subdistances[i].Length()<= 50 ) {//50 = radi de s'esfera

				avoidForce = ahead - obstacles[i];
				avoidForce = avoidForce.Normalize()*MAX_AVOID_FORCE;
			}
			else
				avoidForce = Vector2D(0, 0);
		}
	}
	Vector2D desiredV = target - agent->getPosition();
	desiredV = desiredV.Normalize();
	desiredV *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredV - agent->getVelocity();
	steeringForce /= agent->getMaxVelocity();
	steeringForce *= agent->getMaxForce();
	distances.clear();
	subdistances.clear();

	draw_circle(TheApp::Instance()->getRenderer(),50,50, v, 255,255, 255, 255);

	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), agent->getPosition().x, agent->getPosition().y, ahead.x, ahead.y);


	return steeringForce + avoidForce;
}

