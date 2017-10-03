/*#include "SceneKinematicWander.h"

using namespace std;

SceneKinematicWander::SceneKinematicWander()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	wanderRadius = 80;
	wanderMaxAngle = 5;
	wanderAngle = 0;
	targetAngle = 0;
}

SceneKinematicWander::~SceneKinematicWander()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}


}

void SceneKinematicWander::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events
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
Vector2D dist = target - agents[0]->getPosition();
angle = atan2f(agents[0]->getVelocity().x, agents[0]->getVelocity().y) * RAD2DEG;

wanderOffset = dist.Length();
wanderAngle = randomBinomial() * wanderMaxAngle;
targetAngle = angle + wanderAngle;

//AQUI HI HA UN ERROR. SOLUCIONAR AIXÒ I DONE

//centre = agents[0]->getPosition() + agents[0]->getVelocity().Normalize() * wanderOffset;

newTarget.x = target.x + wanderRadius*cos(targetAngle);
newTarget.y = target.y + wanderRadius*sin(targetAngle);
agents[0]->setTarget(newTarget);

Vector2D steering_force = agents[0]->Behavior()->Wander(agents[0], agents[0]->getTarget(), dtime);
agents[0]->update(steering_force, dtime, event);
}

void SceneKinematicWander::draw()
{

	draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, wanderRadius, 150, 0, 150, 1);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), target.x, target.y, newTarget.x, newTarget.y);

	agents[0]->draw();
}

const char* SceneKinematicWander::getTitle()
{
	return "SDL Steering Behaviors :: KinematicWander Demo";
}*/