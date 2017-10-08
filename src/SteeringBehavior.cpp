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

Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, float r, float dtime) {
	Vector2D desiredV = target - agent->getPosition(); // agafam el vector que resulta de restar posició on volem anar - posició actual. Resultat= velocitat adecuada
	Vector2D steeringForce = desiredV - agent->getVelocity();
	float factor;
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

Vector2D SteeringBehavior::Pursue(Agent *agent, Vector2D target, float maxSpeed, float dtime)
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

Vector2D SteeringBehavior::CollisionAvoidance(Agent *agent, Vector2D target, std::vector <Vector2D> obstacles,  float dtime, float MAX_AHEAD, float MAX_AVOID_FORCE)
{
	float v = agent->getVelocity().Length() / agent->getMaxVelocity();
	Vector2D ahead = agent->getPosition() + agent->getVelocity()* v; // al deixar de normalitzar sa velocitat ha funcionat
	Vector2D halfahead = agent->getPosition() + agent->getVelocity()*  0.5 *v;
	std::vector <Vector2D> distances, subdistances ,avoidForce;

	for (int i = 0; i < obstacles.size(); i++) {

		Vector2D d = ahead - obstacles[i];
		distances.push_back(d);
		Vector2D subD = halfahead - obstacles[i];
		subdistances.push_back(subD);
		Vector2D af;
		af = ahead - obstacles[i];
		af = af.Normalize()*MAX_AVOID_FORCE;
		avoidForce.push_back(af);


	}
	//MIRAR DISTANCIA I SUBDISTANCIA////
	for (int i = 0; i <avoidForce.size(); i++) {

		draw_circle(TheApp::Instance()->getRenderer(),avoidForce[i].Length(), 50, 10, 255, 255, 255, 255);
		//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 20 * i + 20, distances[i].Length(), 20 * i + 20);
		//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 20 * i + 20, avoidForce[i].Length(), 20 * i + 20);
	}
	

	for (int i = 0; i < obstacles.size(); i++) {

		if (distances[i].Length() <= 50 || subdistances[i].Length() <= 50 || agent->getPosition().Distance(agent->getPosition(), obstacles[i]) <= 50) {//50 = radi de s'esfera

			
			draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), agent->getPosition().x, agent->getPosition().y, avoidForce[i].x, avoidForce[i].y);
			Vector2D desiredV = target - agent->getPosition();
			desiredV = desiredV.Normalize();
			desiredV *= agent->getMaxVelocity();
			Vector2D steeringForce = desiredV - agent->getVelocity();
			steeringForce /= agent->getMaxVelocity();
			steeringForce *= agent->getMaxForce();
			distances.clear();
			subdistances.clear();

			draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);

			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), agent->getPosition().x, agent->getPosition().y, ahead.x, ahead.y);


			return steeringForce + avoidForce[i];

		}
		else {

			Vector2D desiredV = target - agent->getPosition();
			desiredV = desiredV.Normalize();
			desiredV *= agent->getMaxVelocity();
			Vector2D steeringForce = desiredV - agent->getVelocity();
			steeringForce /= agent->getMaxVelocity();
			steeringForce *= agent->getMaxForce();


			draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);

			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), agent->getPosition().x, agent->getPosition().y, ahead.x, ahead.y);



			return steeringForce;

		}
	}

}

