#include "SceneKinematicWander.h"

using namespace std;

SceneKinematicWander::SceneKinematicWander()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	wanderRadius = 45;
	wanderMaxAngle = 60;
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
	Vector2D dist = target - agents[0]->getPosition();
	wanderOffset = dist.Length();
	wanderAngle = randomBinomial() * wanderMaxAngle;


	Vector2D steering_force = agents[0]->Behavior()->Wander(agents[0], agents[0]->getTarget(), wanderRadius, wanderMaxAngle, wanderOffset, dtime);
	agents[0]->update(steering_force, dtime, event);

}

void SceneKinematicWander::draw()
{

	draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, wanderRadius, 150, 0, 150, 1);
	//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), target.x, target.y, target.x + 45, target.y);
	
	agents[0]->draw();
}

const char* SceneKinematicWander::getTitle()
{
	return "SDL Steering Behaviors :: KinematicWander Demo";
}