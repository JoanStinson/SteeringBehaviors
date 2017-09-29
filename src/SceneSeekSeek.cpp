#include "SceneSeekSeek.h"

using namespace std;

SceneSeekSeek::SceneSeekSeek()
{
	Agent *agent = new Agent;
	agent->setTarget(Vector2D(100, 100));
	agent->setMass(0.6f);
	agent->setColor(0,0,255,255);
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent);
	agent = new Agent();
	agent->setPosition(Vector2D(600,50));
	agent->setTarget(Vector2D(900, 650));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(900, 650);
}

SceneSeekSeek::~SceneSeekSeek()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneSeekSeek::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[1]->setTarget(target);
		}
		break;
	default:
		break;
	}

	agents[0]->setTarget(agents[1]->getPosition());
	for (int i = 0; i < (int)agents.size(); i++)
	{
		Vector2D steering_force = agents[i]->Behavior()->Arrive(agents[i], agents[i]->getTarget(), 125, dtime);
		agents[i]->update(steering_force, dtime, event);
	}
}

void SceneSeekSeek::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneSeekSeek::getTitle()
{
	return "SDL Steering Behaviors :: Seek and Seek Demo";
}