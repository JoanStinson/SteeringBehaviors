#include "SceneFlocking.h"

using namespace std;

SceneFlocking::SceneFlocking()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	//target = Vector2D(640, 360);


	Agent *agent2 = new Agent;
	agent2->setPosition(Vector2D(800, 360));
	agent2->setTarget(Vector2D(640, 360));
	agent2->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent2);
	//target = Vector2D(640, 360);

	Agent *agent3 = new Agent;
	agent3->setPosition(Vector2D(600, 300));
	agent3->setTarget(Vector2D(640, 360));
	agent3->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent3);
	//target = Vector2D(640, 360);

	Agent *agent4 = new Agent;
	agent4->setPosition(Vector2D(500, 550));
	agent4->setTarget(Vector2D(640, 360));
	agent4->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent4);
	//target = Vector2D(640, 360);
}

SceneFlocking::~SceneFlocking()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneFlocking::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			for each (Agent* x in agents)
			{
				x->setTarget(target);
			}
			//agents[0]->setTarget(target);
		}
		break;
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_Z)
		{
			//flee = !flee;
		}
	default:
		break;
	}
	for each (Agent* x in agents)
	{
		Vector2D steering_force = x->Behavior()->Seek(x, target, dtime);
		Vector2D flocking_force = x->Behavior()->Flocking(x,agents,dtime);
		steering_force += flocking_force;
		//uolo
		x->update(steering_force, dtime, event);
	}
	
}

void SceneFlocking::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);

	for each (Agent* x in agents)
	{
		x->draw();
	}
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 0, 255);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 100, 100, 700); //LEFT
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 100, 1200, 100); //TOP
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 1200, 100, 1200, 700); //RIGHT
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 700, 1200, 700); //BOTTOM

}

const char* SceneFlocking::getTitle()
{
	return "SDL Steering Behaviors :: Flocking Demo";
}