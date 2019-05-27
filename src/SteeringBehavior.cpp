#include "SteeringBehavior.h"
#include "SceneWanderBehavior.h"
#include "ScenePathFollowing.h"
#include "SceneFlocking.h"
#include "SceneCollisionAvoidance.h"

SteeringBehavior::SteeringBehavior()
{
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = target - agent->position;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Agent *target, float dtime)
{
	return KinematicSeek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = agent->position - target;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime)
{
	return KinematicFlee(agent, target->position, dtime);
}

/* Add here your own Steering Behavior functions definitions */

Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	//Vector2D steeringForce;
	Vector2D DesiredVelocity = target - agent->position;
	Vector2D steeringForce;
	float minDistance = 5;
	//float borderDistance = 50;

	if (agent->position.x < agent->perimeterBorder)
		DesiredVelocity.x = agent->max_velocity;
	else if (agent->position.x > agent->perimeterWidth - agent->perimeterBorder)
		DesiredVelocity.x = -agent->max_velocity;
	if (agent->position.y < agent->perimeterBorder)
		DesiredVelocity.y = agent->max_velocity;
	else if (agent->position.y > agent->perimeterHeight - agent->perimeterBorder)
		DesiredVelocity.y = -agent->max_velocity;
	if (DesiredVelocity.Length() > 0.0f) {
		steeringForce = DesiredVelocity - agent->velocity;
		steeringForce /= agent->max_velocity;
		steeringForce *= agent->max_force;
	}
	/*else if (DesiredVelocity.Length() <= borderDistance) {
		agent->setVelocity(Vector2D(0));
	}*/

	if (DesiredVelocity.Length() < minDistance) {
		//ScenePathFollowing::targetCount++;
		agent->setVelocity(Vector2D(0));

	}
	if (DesiredVelocity.Length() > 200) {
		DesiredVelocity.Normalize();
		DesiredVelocity *= agent->max_velocity;
		steeringForce = DesiredVelocity - agent->velocity;
		steeringForce /= agent->max_velocity;
		return steeringForce*agent->max_force;
	}
	else {
		float factor = DesiredVelocity.Length() / 200;
		DesiredVelocity.Normalize();
		DesiredVelocity *= (agent->max_velocity * factor);
		steeringForce = DesiredVelocity - (agent->velocity);
		steeringForce /= (agent->max_velocity);
		return steeringForce*agent->max_force;
	}
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D DesiredVelocity = agent->position - target;
	
	//DesiredVelocity.Normalize();
	//DesiredVelocity *= agent->max_velocity;
	Vector2D steeringForce;

	if (agent->position.x < agent->perimeterBorder)
		DesiredVelocity.x = agent->max_velocity;
	else if (agent->position.x > agent->perimeterWidth - agent->perimeterBorder)
		DesiredVelocity.x = -agent->max_velocity;
	if (agent->position.y < agent->perimeterBorder)
		DesiredVelocity.y = agent->max_velocity;
	else if (agent->position.y > agent->perimeterHeight - agent->perimeterBorder)
		DesiredVelocity.y = -agent->max_velocity;
	if (DesiredVelocity.Length() > 0.0f) {
		steeringForce = DesiredVelocity - agent->velocity;
		steeringForce /= agent->max_velocity;
		steeringForce *= agent->max_force;
		
	}
	return steeringForce;
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, float dtime)
{
	return Flee(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Pursue(Agent *agent, Agent *target, float dtime)
{
	Vector2D distance = target->getTarget() - target->getPosition();
	//distance.Normalize();
	float dist = distance.Length();
	Vector2D targetP;
	if (target->velocity.Length() > 0) {
		float T = dist / target->getVelocity().Length();
		targetP = (target->position + target->velocity * T);
	}
	else {
		targetP = target->getTarget();
	}
	return Seek(agent, targetP, dtime);
}

Vector2D SteeringBehavior::Evade(Agent *agent, Agent *target, float dtime)
{
	Vector2D distance = target->getPosition() - target->getTarget();
	//distance.Normalize();
	Vector2D targetP;
	float dist = distance.Length();
	Vector2D uouo = target->getPosition() - agent->getPosition();
	if (uouo.Length() < 300) {
		if (target->velocity.Length() > 0) {
			float T = dist / target->getVelocity().Length();
			targetP = (target->position + target->velocity * T);
		}
		else {
			targetP = target->getTarget();
		}
	}
	return Flee(agent, targetP, dtime);
}

/*Vector2D SteeringBehavior::Wander(Agent *agent, Vector2D target, float dtime)
{
	Vector2D DesiredVelocity = agent->position - target;
	DesiredVelocity.Normalize();
	DesiredVelocity *= agent->max_velocity;
	Vector2D steeringForce = DesiredVelocity - agent->velocity;
	steeringForce /= agent->max_velocity;
	return steeringForce*agent->max_force;
}*/

float RandomBinomial() {
	return ((float)rand() / (RAND_MAX)) - ((float)rand() / (RAND_MAX));
}

Vector2D SteeringBehavior::Wander(Agent *agent, float dtime)
{
	float targetAngle = 0;
	wanderAngle += RandomBinomial() * 20;
	//targetAngle = (rand() / RAND_MAX)*25 + wanderAngle;
	targetAngle = agent->orientation + wanderAngle;
	Vector2D centerC = agent->getPosition() + agent->getVelocity().Normalize() * 750;

	Vector2D targetPos;
	targetPos.x = centerC.x + 250 * cos(targetAngle);
	targetPos.y = centerC.y + 250 * sin(targetAngle);

	draw_circle(TheApp::Instance()->getRenderer(), (int)targetPos.x, (int)targetPos.y, 5, 250, 0, 0, 255);

	return Seek(agent, targetPos, dtime);
}

Vector2D SteeringBehavior::SeekPath(Agent *agent, Vector2D target, float dtime)
{
	//Vector2D steeringForce;
	Vector2D DesiredVelocity = target - agent->position;



	DesiredVelocity.Normalize();
	DesiredVelocity *= agent->max_velocity;
	Vector2D steeringForce = DesiredVelocity - agent->velocity;
	steeringForce /= agent->max_velocity;

	return steeringForce*agent->max_force;
}

Vector2D SteeringBehavior::SeekPath(Agent *agent, Agent *target, float dtime)
{
	return SeekPath(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Flocking(Agent *agent, std::vector<Agent*> target, float dtime)
{
	int neigbourCount = 0;
	Vector2D sepVec;
	Vector2D avaragePos;
	Vector2D avarageVel;
	Vector2D flockingForce;
	const int NEIGHBOUR_RADIUS = 70;
	const float K_MAX_FLOCKING_FORCE = 1;
	const float K_SEPARATION_FORCE = 2;
	const float K_COHESION_FORCE = 0.3;
	const float K_ALIGNMENT_FORCE = 0.2;

	for each (Agent* x in target)
	{
		//Vector2D dist = x->getPosition() - agent->getPosition();
		//int len = dist.Length();

	// PER AFEGIR: SI LA DISTÀNCIA ENTRE UN DELS AGENTS I EL TARGET ES MENOR QUE 'X' SET VELOCITY TO '0' A TOTS

		if (Vector2D().Distance(x->getPosition(), agent->getPosition()) < NEIGHBOUR_RADIUS) {
			sepVec += (agent->getPosition() - x->getPosition());
			avaragePos += x->getPosition();
			avarageVel += x->getVelocity();
			neigbourCount++;
		}
	}
	sepVec /= neigbourCount;
	sepVec.Normalize(1);
	avaragePos /= neigbourCount;
	avaragePos -= agent->getPosition();
	avaragePos.Normalize(1);
	avarageVel /= neigbourCount;
	avarageVel.Normalize(1);

	flockingForce = sepVec*K_SEPARATION_FORCE + avaragePos*K_COHESION_FORCE + avarageVel*K_ALIGNMENT_FORCE;
	//flockingForce *= K_MAX_FLOCKING_FORCE;

	return flockingForce;
}

Vector2D SteeringBehavior::Flocking(Agent *agent, Vector2D target, float dtime)
{
	target.Normalize();
	target *= agent->max_velocity;
	Vector2D steeringForce = target - agent->velocity;
	steeringForce /= agent->max_velocity;
	return steeringForce*agent->max_force;
}

Vector2D SteeringBehavior::CollisionAvoidance(Agent *agent, std::vector<Agent*> target, float dtime) {

	const int avoidanceLookahead = 200;

	Vector2D raycastVector = agent->position;
	raycastVector += agent->velocity.Normalize() * avoidanceLookahead;
	Vector2D intersectionPoint, normalVector;
	bool obstacleAvoidanceCollision = false;

	for each(Agent* object in target)
	{


	} 
	return 0;
}

Vector2D SteeringBehavior::CollisionRayCast(Agent *agent, std::vector<Agent*> target, float dtime) {

	const int avoidanceLookahead = 200;

	Vector2D raycastVector = agent->position;
	raycastVector += agent->velocity.Normalize() * avoidanceLookahead;
	Vector2D intersectionPoint, normalVector,steeringForce;
	bool obstacleAvoidanceCollision = false;

	for each(Agent* object in target)
	{
		obstacleAvoidanceCollision = Vector2DUtils::SegmentSegmentIntersection(object->getPosition(), object->getPosition() + Vector2D(200, 0), agent->getPosition(), raycastVector);
		if (obstacleAvoidanceCollision) break;
	}
	if (obstacleAvoidanceCollision) {
		Vector2D avoidTarget = intersectionPoint;
		avoidTarget += normalVector * 150;
		steeringForce = Seek(agent, avoidTarget, dtime);
	}
	return steeringForce;
}
