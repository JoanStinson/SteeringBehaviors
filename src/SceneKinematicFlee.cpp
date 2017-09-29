#include "SceneKinematicFlee.h"

using namespace std;

SceneKinematicFlee::SceneKinematicFlee()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
}

SceneKinematicFlee::~SceneKinematicFlee()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneKinematicFlee::update(float dtime, SDL_Event *event)
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
	Vector2D steering_force = agents[0]->Behavior()->KinematicFlee(agents[0],agents[0]->getTarget(),dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneKinematicFlee::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
}

const char* SceneKinematicFlee::getTitle()
{
	return "SDL Steering Behaviors :: KinematicFlee Demo";
}