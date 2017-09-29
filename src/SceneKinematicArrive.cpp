#include "../src/SceneKinematicArrive.h"

using namespace std;

SceneKinematicArrive::SceneKinematicArrive()
{
	Agent *agent = new Agent;
	Agent *agent2 = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);

	agents.push_back(agent);
	target = Vector2D(640, 360);
	r = 150;
}

SceneKinematicArrive::~SceneKinematicArrive()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}


void SceneKinematicArrive::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}
	Vector2D desiredV = target - agents[0]->getPosition(); // agafam el vector que resulta de restar posició on volem anar - posició actual. Resultat= velocitat adecuada
	desiredV = desiredV.Normalize();
	desiredV *= agents[0]->getMaxVelocity();
	dist = target - agents[0]->getPosition();
	if (dist.Length() >= r) {
		draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 0, 255, 1);
		desiredV *= agents[0]->getMaxVelocity();
	}
	else {
		factor = dist.Length() / r; //AQUI
		draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 255, 0, 1);
		desiredV *= factor;
	}

	Vector2D steeringForce = desiredV - agents[0]->getVelocity();
	steeringForce *= agents[0]->getMaxForce();

	agents[0]->update(steeringForce, dtime, event);




}

void SceneKinematicArrive::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	
}

const char* SceneKinematicArrive::getTitle()
{
	return "SDL Steering Behaviors :: KinematicArrive Demo";
}
